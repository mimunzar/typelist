#pragma once

#include "TypelistModern.hpp"

namespace tl_modern {

/** Returns index of the first occurence */
template<typename T, typename S>
struct IndexOf;
template<typename S>
struct IndexOf<Typelist<>, S> {
    static constexpr size_t value = -1;
};
template<typename T, typename... Args>
struct IndexOf<Typelist<T, Args...>, T> {
    static constexpr size_t value = 0;
};
template<typename T, typename S, typename... Args>
struct IndexOf<Typelist<T, Args...>, S> {
private:
    static constexpr size_t tmp = IndexOf<Typelist<Args...>, S>::value;
public:
    static constexpr size_t value = tmp == -1 ? -1 : tmp + 1;
};

/** Appends a type */
template<typename T, typename A>
struct Append;
template<typename A, typename... Args>
struct Append<Typelist<Args...>, A> {
    using type = Typelist<Args..., A>;
};

/** Prepends a type */
template<typename T, typename P>
struct Prepend;
template<typename P, typename... Args>
struct Prepend<Typelist<Args...>, P> {
    using type = Typelist<P, Args...>;
};

/** Erases all occurences of type */
template<typename T, typename E>
struct EraseAll;
template<typename E, typename... Args>
struct EraseAll<Typelist<E, Args...>, E> {
    using type = typename EraseAll<Typelist<Args...>, E>::type;
};
template<typename T, typename E, typename... Args>
struct EraseAll<Typelist<T, Args...>, E> {
    using type = typename Prepend<typename EraseAll<Typelist<Args...>, E>::type, T>::type;
};
template<typename E>
struct EraseAll<Typelist<>, E> {
    using type = Typelist<>;
};

/** Erases only the first occurence of type */
template<typename T, typename E>
struct Erase;
template<typename E, typename... Args>
struct Erase<Typelist<E, Args...>, E> {
    using type = Typelist<Args...>;
};
template<typename T, typename E, typename... Args>
struct Erase<Typelist<T, Args...>, E> {
    using type = typename Prepend<typename Erase<Typelist<Args...>, E>::type, T>::type;
};
template<typename E>
struct Erase<Typelist<>, E> {
    using type = Typelist<>;
};

/** Removes duplicates */
template<typename T>
struct NoDuplicates;
template<typename T, typename... Args>
struct NoDuplicates<Typelist<T, Args...>> {
private:
    using tmp = typename EraseAll<Typelist<Args...>, T>::type;
public:
    using type = typename Prepend<typename NoDuplicates<tmp>::type, T>::type;
};
template<>
struct NoDuplicates<Typelist<>> {
    using type = Typelist<>;
};

/** Replaces all occurences of a type */
template<typename T, typename A, typename B>
struct ReplaceAll;
template<typename T, typename T2, typename... Args>
struct ReplaceAll<Typelist<T, Args...>, T, T2> {
    using type = typename Prepend<
        typename ReplaceAll<Typelist<Args...>, T, T2>::type, T2>::type;
};
template<typename H, typename T, typename T2, typename... Args>
struct ReplaceAll<Typelist<H, Args...>, T, T2> {
    using type = typename Prepend<
        typename ReplaceAll<Typelist<Args...>, T, T2>::type, H>::type;
};
template<typename T, typename T2>
struct ReplaceAll<Typelist<>, T, T2> {
    using type = Typelist<>;
};

/** Replaces only the first occurence of type */
template<typename T, typename A, typename B>
struct Replace;
template<typename T, typename T2, typename... Args>
struct Replace<Typelist<T, Args...>, T, T2> {
    using type = Typelist<T2, Args...>;
};
template<typename H, typename T, typename T2, typename... Args>
struct Replace<Typelist<H, Args...>, T, T2> {
    using type = typename Prepend<
        typename Replace<Typelist<Args...>, T, T2>::type, H>::type;
};
template<typename T, typename T2>
struct Replace<Typelist<>, T, T2> {
    using type = Typelist<>;
};

} // namespace tl_modern

