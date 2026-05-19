module;

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/core/buffers_to_string.hpp>

export module ws_chat:beast;

export namespace beast {
    using ::boost::beast::async_teardown;
    using ::boost::beast::beast_close_socket;
    using ::boost::beast::buffers_to_string;
    using ::boost::beast::flat_buffer;
    using ::boost::beast::tcp_stream;
} // namespace beast

export namespace beast::websocket {
    using ::boost::beast::websocket::is_upgrade;
    using ::boost::beast::websocket::stream;
} // namespace beast::websocket

export namespace beast::http {
    using ::boost::beast::http::async_read;
    using ::boost::beast::http::async_write;
    using ::boost::beast::http::field;
    using ::boost::beast::http::fields;
    using ::boost::beast::http::status;

    using request  = ::boost::beast::http::request<boost::beast::http::string_body>;
    using response = ::boost::beast::http::response<boost::beast::http::string_body>;
} // namespace beast::http
