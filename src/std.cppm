module;

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <fstream>

export module ws_chat:std;

export namespace std {
    using ::std::cerr;
    using ::std::cout;
    using ::std::enable_shared_from_this;
    using ::std::endl;
    using ::std::exception;
    using ::std::flush;
    using ::std::forward;
    using ::std::fstream;
    using ::std::ifstream;
    using ::std::ignore;
    using ::std::ios;
    using ::std::iostream;
    using ::std::istream;
    using ::std::istreambuf_iterator;
    using ::std::make_shared;
    using ::std::make_unique;
    using ::std::move;
    using ::std::ostream;
    using ::std::runtime_error;
    using ::std::set;
    using ::std::shared_ptr;
    using ::std::string;
    using ::std::unique_ptr;

    using ::std::operator<<;
    using ::std::operator>>;
    using ::std::operator+;
    using ::std::operator==;
} // namespace std
