module ws_chat;
import :std;
import :asio;
import :beast;

using asio::ip::tcp;

asio::awaitable<void> listener(ws_chat::SharedState &state) {
    auto executor = co_await asio::this_coro::executor;
    auto acceptor = tcp::acceptor(executor, {tcp::v4(), 3000});

    while (true) {
        tcp::socket socket  = co_await acceptor.async_accept(asio::use_awaitable);
        auto        session = std::make_shared<ws_chat::Session>(std::move(socket), state);

        asio::co_spawn(executor, session->run(), asio::detached);
    }
}

extern "C++" int main() {
    ws_chat::SharedState state;

    try {
        asio::io_context ioc;
        asio::co_spawn(ioc, listener(state), asio::detached);

        std::cout << "Server: " << "http://localhost:3000\n";
        ioc.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
