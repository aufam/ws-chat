export module ws_chat;
import :std;
import :asio;
import :tcp;
import :beast;

export namespace ws_chat {
    class Session;
    class SharedState;
} // namespace ws_chat

module :private;

namespace http = beast::http;
namespace ws   = beast::websocket;

class ws_chat::SharedState {
public:
    void join(const std::shared_ptr<Session> &s) {
        sessions_.insert(s);
    }

    void leave(const std::shared_ptr<Session> &s) {
        sessions_.erase(s);
    }

    void broadcast(const std::string &msg);

private:
    std::set<std::shared_ptr<Session>> sessions_;
};

class ws_chat::Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, SharedState &state)
        : socket_(std::move(socket))
        , state_(state) {}

    asio::awaitable<void> run() {
        auto self = shared_from_this();

        try {
            beast::flat_buffer buffer;
            http::request      req;

            co_await http::async_read(self->socket_, buffer, req, asio::use_awaitable);

            if (ws::is_upgrade(req)) {
                co_await self->handle_websocket(std::move(req));
            } else {
                co_await self->handle_http(req);
            }
        } catch (std::exception const &e) {
            std::cerr << "session error: " << e.what() << '\n';
        }
    }

    asio::any_io_executor get_executor() {
        return socket_.get_executor();
    }

    asio::awaitable<void> send(std::string msg) {
        auto self = shared_from_this();

        if (self->ws_)
            try {
                co_await ws_->async_write(asio::buffer(msg), asio::use_awaitable);
            } catch (std::exception &e) {
                std::ignore = e;
            }
    }

private:
    tcp::socket  socket_;
    SharedState &state_;

    std::unique_ptr<ws::stream<tcp::socket>> ws_ = nullptr;

    asio::awaitable<void> handle_websocket(beast::http::request req) {
        auto self = shared_from_this();

        self->ws_ = std::make_unique<ws::stream<tcp::socket>>(std::move(this->socket_));
        auto &ws  = *self->ws_;

        co_await ws.async_accept(req, asio::use_awaitable);

        state_.join(self);
        try {
            beast::flat_buffer buffer;

            while (true) {
                co_await ws.async_read(buffer, asio::use_awaitable);

                std::string msg = beast::buffers_to_string(buffer.data());
                buffer.consume(buffer.size());

                state_.broadcast(msg);
                std::cout << msg << std::endl;
            }
        } catch (std::exception &e) {
            std::ignore = e;
        }

        state_.leave(self);
    }

    asio::awaitable<void> handle_http(const beast::http::request &req) {
        auto self = shared_from_this();

        http::response res;
        res.version(req.version());
        res.set(http::field::server, "beast");

        const std::string path = req.target() == "/" ? "./index.html" : "." + std::string(req.target());
        std::ifstream     file(path, std::ios::binary);
        if (!file) {
            res.result(http::status::not_found);
            res.set(http::field::content_type, "text/plain");
            res.body() = "404 Not Found";
        } else {
            std::string body((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

            if (path.ends_with(".html")) {
                res.set(http::field::content_type, "text/html");
            } else if (path.ends_with(".js")) {
                res.set(http::field::content_type, "application/javascript");
            } else if (path.ends_with(".css")) {
                res.set(http::field::content_type, "text/css");
            }

            res.body() = std::move(body);
            res.result(http::status::ok);
        }

        res.prepare_payload();
        co_await http::async_write(self->socket_, res, asio::use_awaitable);
    }
};

void ws_chat::SharedState::broadcast(const std::string &msg) {
    for (auto &session : sessions_) {
        asio::co_spawn(session->get_executor(), session->send(msg), asio::detached);
    }
}
