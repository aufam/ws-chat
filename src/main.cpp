module ws_chat;
import :std;
import :asio;
import :tcp;


asio::awaitable<void> listener(ws_chat::Room &room) {
    auto executor = co_await asio::this_coro::executor;
    auto acceptor = tcp::acceptor(executor, {tcp::v4(), 3000});

    while (true) {
        tcp::socket socket  = co_await acceptor.async_accept(asio::use_awaitable);
        auto        session = std::make_shared<ws_chat::Session>(std::move(socket), room);

        asio::co_spawn(executor, session->run(), asio::detached);
    }
}

extern "C++" int main() {
    ws_chat::Room room;

    try {
        asio::io_context ioc(1);
        asio::co_spawn(ioc, listener(room), asio::detached);

        std::cout << "Server: " << "http://localhost:3000\n";
        ioc.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
