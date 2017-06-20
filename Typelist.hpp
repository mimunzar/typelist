#pragma once

#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4)>

namespace tl {

/** Typelist */
template<typename T, typename U>
struct Typelist {
    typedef T Head;
    typedef U Tail;
};

/** Typelist terminator */
struct NullType {};

/** Length */
template<typename T>
struct Length;
template<typename T, typename U>
struct Length<Typelist<T, U>> {
    enum { value = Length<U>::value + 1 };
};
template<>
struct Length<NullType> {
    enum { value = 0 };
};

/** Random access */
template<typename T, size_t i>
struct TypeAt;
template<typename T, typename U, size_t i>
struct TypeAt<Typelist<T, U>, i> {
    typedef typename TypeAt<U, i - 1>::type type;
};
template<typename T, typename U>
struct TypeAt<Typelist<T, U>, 0> {
    typedef T type;
};

} // namespace tl

