module;

#include <boost/asio/ip/tcp.hpp>

export module ws_chat:tcp;

export namespace asio {
    using ::boost::asio::basic_socket;
} // namespace asio

export using tcp = boost::asio::ip::tcp;
