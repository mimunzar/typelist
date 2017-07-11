#include "Cpp11/Typelist.hpp"
#include "Cpp11/TypelistAlgs.hpp"

using namespace Cpp11;

/** Type displayer for algorithms validation */
template<typename T>
struct TD;

int main() {
    //using T = TYPELIST_4(int, int, char, int);
    using T = Typelist<int, int, double*, char, int>;
    TD<Replace<T, int, char>::type> t;
    return 0;
}

