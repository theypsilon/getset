/*
 *  GETSET - Expose getter and setter methods as public interface
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

    namespace intern { 
        //forward declaration, no need for this helper in c++14
        template <typename T, typename U>
        struct is_private_base_of;
    }

    // Expose Setter & Getter public interface with this artifact:
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
            !intern::is_private_base_of<U, getset<T>>::value, void>::type>
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

    // Expose just getter as public interface, but Friend can access setter
    template <typename T, typename Friend = void>
    class getter : private getset<T> {

        template <typename U>
        /* constexpr c++14 */ void operator()(U&& v)
        noexcept(noexcept(getset<T>::operator()(std::forward<U>(v))))
        {
            getset<T>::operator()(std::forward<U>(v));
        }

        friend Friend;

    public:
        using private_base = getset<T>;
        using getset<T>::getset;
        using getset<T>::operator();
    };

    // Expose just setter as public interface, but Friend can access getter
    template <typename T, typename Friend>
    class setter : private getset<T> {
        constexpr const T& operator()() const noexcept
        {
            return getset<T>::operator()();
        }

        friend Friend;

    public:
        using private_base = getset<T>;
        using getset<T>::getset;
        using getset<T>::operator();
    };

    namespace intern {

        template <typename T>
        struct has_private_base {
            typedef char yes;
            typedef char (&no)[2];
            template <typename U>
            static yes test( typename U::private_base* p );
            template <typename U>
            static no test( ... );

            static const bool value = sizeof( test<T>(0) ) == sizeof(yes);
        };

        template <typename T, typename D = void>
        struct get_private_base {
            using type = T;
        };

        template <typename T>
        struct get_private_base<T, typename
            std::enable_if<has_private_base<T>::value, void>::type> {
            using type = typename T::private_base;
        };

        template <typename T, typename U>
        constexpr bool is_private_base_of_impl() {
            using decay        = typename std::decay<T>::type;
            using private_base = typename get_private_base<decay>::type;
            return std::is_same<private_base, U>::value;
        }

        template<typename T, typename U>
        struct is_private_base_of : std::integral_constant<bool,
            is_private_base_of_impl<T, U>()>{};
    }


}

#endif
