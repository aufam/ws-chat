module;

#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <coroutine>
#include <fstream>


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreserved-module-identifier"

export module std;

#pragma GCC diagnostic pop


export namespace std {
    using ::std::cerr;
    using ::std::cout;
    using ::std::endl;

    using ::std::enable_shared_from_this;
    using ::std::forward;
    using ::std::ifstream;
    using ::std::ignore;
    using ::std::make_shared;
    using ::std::move;
    using ::std::set;
    using ::std::shared_ptr;
    using ::std::string;

    using ::std::coroutine_handle;
    using ::std::coroutine_traits;
    using ::std::noop_coroutine;
    using ::std::suspend_always;
    using ::std::suspend_never;
} // namespace std
