module ws_chat;
import :std;
import :asio;


void ws_chat::Room::join(const std::shared_ptr<Session> &s) {
    sessions_.insert(s);
}

void ws_chat::Room::leave(const std::shared_ptr<Session> &s) {
    sessions_.erase(s);
}

void ws_chat::Room::broadcast(const std::string &msg) {
    for (auto &session : sessions_) {
        asio::co_spawn(session->get_executor(), session->send(msg), asio::detached);
    }
}
