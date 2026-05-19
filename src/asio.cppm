module;

#define BOOST_ASIO_NO_SSL
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/ssl.hpp>

export module asio;

export namespace asio {
    using ::boost::asio::any_io_executor;
    using ::boost::asio::awaitable;
    using ::boost::asio::basic_socket;
    using ::boost::asio::buffer;
    using ::boost::asio::co_spawn;
    using ::boost::asio::detached;
    using ::boost::asio::io_context;
    using ::boost::asio::use_awaitable;
} // namespace asio

export namespace asio::detail {
    using ::boost::asio::detail::awaitable_frame;
} // namespace asio::detail

export namespace asio::this_coro {
    using ::boost::asio::this_coro::executor;
} // namespace asio::this_coro

export namespace asio::ip {
    using ::boost::asio::ip::tcp;
} // namespace asio::ip

export namespace asio::ssl {
    using ::boost::asio::ssl::stream;
} // namespace asio::ssl
