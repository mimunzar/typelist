#pragma once

#include "Typelist.hpp"

namespace tl {

/** Returns index of the first occurence */
template<typename T, typename S>
struct IndexOf;
template<typename S>
struct IndexOf<NullType, S> {
    enum { value = -1 };
};
template<typename T, typename U>
struct IndexOf<Typelist<T, U>, T> {
    enum { value = 0 };
};
template<typename T, typename U, typename S>
struct IndexOf<Typelist<T, U>, S> {
private:
    enum { tmp = IndexOf<U, S>::value };
public:
    enum { value = tmp == -1 ? -1 : tmp + 1 };
};

/** Appends a type */
template<typename T, typename A>
struct Append;
template<typename A>
struct Append<NullType, A> {
    typedef Typelist<A, NullType> type;
};
template<typename T, typename U, typename A>
struct Append<Typelist<T, U>, A> {
    typedef Typelist<T, typename Append<U, A>::type> type;
};
template<typename T, typename U>
struct Append<Typelist<T, U>, NullType> {
    typedef Typelist<T, U> type;
};
template<>
struct Append<NullType, NullType> {
    typedef NullType type;
};

/** Erases all occurences of type */
template<typename T, typename E>
struct EraseAll;
template<typename T>
struct EraseAll<NullType, T> {
    typedef NullType type;
};
template<typename T, typename U, typename E>
struct EraseAll<Typelist<T, U>, E>{
    typedef Typelist<T, typename EraseAll<U, E>::type> type;
};
template<typename T, typename U>
struct EraseAll<Typelist<T, U>, T> {
    typedef typename EraseAll<U,T>::type type;
};

/** Erases only the first occurence of type */
template<typename T, typename U>
struct Erase;
template<typename E>
struct Erase<NullType, E> {
    typedef NullType type;
};
template<typename T, typename U, typename E>
struct Erase<Typelist<T, U>, E> {
    typedef Typelist<T, typename Erase<U, E>::type> type;
};
template<typename T, typename U>
struct Erase<Typelist<T, U>, T> {
    typedef U type;
};

/** Removes duplicates */
template<typename T>
struct NoDuplicates;
template<>
struct NoDuplicates<NullType>{
    typedef NullType type;
};
template<typename T, typename U>
struct NoDuplicates<Typelist<T, U>> {
private:
    typedef typename EraseAll<U, T>::type tmp;
public:
    typedef Typelist<T, typename NoDuplicates<tmp>::type> type;
};

/** Replaces all occurences of a type */
template<typename T, typename A, typename B>
struct ReplaceAll;
template<typename A, typename B>
struct ReplaceAll<NullType, A, B> {
    typedef NullType type;
};
template<typename T, typename U, typename B>
struct ReplaceAll<Typelist<T, U>, T,  B> {
    typedef Typelist<B, typename ReplaceAll<U, T, B>::type> type;
};
template<typename T, typename U, typename A, typename B>
struct ReplaceAll<Typelist<T, U>, A,  B> {
    typedef Typelist<T, typename ReplaceAll<U, A, B>::type> type;
};

/** Replaces only the first occurence of type */
template<typename T, typename A, typename B>
struct Replace;
template<typename A, typename B>
struct Replace<NullType, A, B> {
    typedef NullType type;
};
template<typename T, typename U, typename B>
struct Replace<Typelist<T, U>, T,  B> {
    typedef Typelist<B, U> type;
};
template<typename T, typename U, typename A, typename B>
struct Replace<Typelist<T, U>, A,  B> {
    typedef Typelist<T, typename Replace<U, A, B>::type> type;
};

}

