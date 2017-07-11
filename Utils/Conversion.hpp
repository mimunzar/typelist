#pragma once

#include <cstddef>

namespace Utils {

/** Converts array of Ts to T* */
template<typename T>
struct DecayArray {
    typedef T type;
};
template<typename T>
struct DecayArray<T[]> {
    typedef T* type;
};
template<typename T, std::size_t N>
struct DecayArray<T[N]> {
    typedef T* type;
};

/** Returns true if type T is convertible to U. */
template<typename T, typename U>
class IsConvertible {
    static char ReturnType(U);
    static double ReturnType(...);
    static typename DecayArray<T>::type MakeT();
public:
    enum { value = sizeof(ReturnType(MakeT())) == sizeof(char) };
};

/** Returns true if types T, U are the same. */
template<typename T, typename U>
struct IsSame {
    enum { value = false };
};
template<typename T>
struct IsSame<T, T> {
    enum { value = true };
};

/** Returns true if T is the base class of U */
template<typename T, typename U>
struct IsBaseOf {
    enum { value = !IsSame<T, U>::value && IsConvertible<U, T>::value };
};

}

