/*
 *  GETSET
 *  Version: 2014-08-17
 *  ----------------------------------------------------------
 *  Copyright (c) 2014 José Manuel Barroso Galindo. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef THEYPSILON_GETSET
#define THEYPSILON_GETSET

#include <utility>

namespace accessor {

    template <typename T>
    class getset {

        T value;

        static constexpr bool nothrow_move =
            std::is_nothrow_move_constructible<T>::value;
        static constexpr bool nothrow_copy =
            std::is_nothrow_copy_constructible<T>::value;
    public:
        getset()                = default;
        getset(const getset& v) = default;
        getset(getset&& v)      = default;
        ~getset()               = default;

        getset& operator=(const getset&) = delete;
        getset& operator=(getset&&)      = delete;

        template <typename U, typename = typename std::enable_if<
            !std::is_same<typename std::decay<U>::type, getset<T>>::value,
            void>::type>
        constexpr getset(U&& v)
        noexcept((std::is_lvalue_reference<U&&>::value && nothrow_copy) ||
                 (std::is_rvalue_reference<U&&>::value && nothrow_move))
        : value{std::forward<U>(v)} {}

        template <typename U>
        /* constexpr c++14 */ void operator()(U&& v)
        noexcept((std::is_lvalue_reference<U&&>::value && nothrow_copy) ||
                 (std::is_rvalue_reference<U&&>::value && nothrow_move))
        {
            value = std::forward<U>(v); 
        }

        constexpr const T& operator()() const noexcept
        {
            return value;
        }
    };
}

#endif
