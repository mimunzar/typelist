#pragma once

#include <cstddef>

namespace Cpp11 {

/** Typelist */
template<typename... Args>
struct Typelist {
    static constexpr std::size_t size = sizeof...(Args);
};

/** Length */
template<typename T>
struct Length;
template<typename T, typename... Args>
struct Length<Typelist<T, Args...>> {
    static constexpr std::size_t value = Length<Typelist<Args...>>::value + 1;
};
template<>
struct Length<Typelist<>> {
    static constexpr std::size_t value = 0;
};

/** Random access */
template<typename T, std::size_t index>
struct TypeAt;
template<typename T, typename... Args>
struct TypeAt<Typelist<T, Args...>, 0> {
    using result = T;
};
template<typename T, typename... Args, std::size_t index>
struct TypeAt<Typelist<T, Args...>, index> {
    using result = typename TypeAt<Typelist<Args...>, index - 1>::result;
};

}

