export module ws_chat;
import :std;
import :asio;
import :tcp;
import :beast;

export namespace ws_chat {
    class Session;
    class Room;
} // namespace ws_chat


namespace http = beast::http;
namespace ws   = beast::websocket;


class ws_chat::Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket, Room &room);

    asio::awaitable<void> run();

    asio::any_io_executor get_executor();

    asio::awaitable<void> send(std::string msg);

private:
    tcp::socket socket_;
    Room       &room_;

    std::unique_ptr<ws::stream<tcp::socket>> ws_ = nullptr;

    asio::awaitable<void> handle_websocket(beast::http::request req);

    asio::awaitable<void> handle_http(const beast::http::request &req);
};


class ws_chat::Room {
public:
    void join(const std::shared_ptr<Session> &s);

    void leave(const std::shared_ptr<Session> &s);

    void broadcast(const std::string &msg);

private:
    std::set<std::shared_ptr<Session>> sessions_;
};
