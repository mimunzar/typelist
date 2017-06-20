#include <iostream>

#include "Typelist.hpp"
#include "TypelistAlgs.hpp"
#include "TypelistModern.hpp"
#include "TypelistAlgsModern.hpp"

using namespace tl_modern;

/** Type displayer for the algorithm validation */
template<typename T>
struct TD;

int main() {
    //using T = TYPELIST_4(int, int, char, int);
    using T = Typelist<int, int, double*, char, int>;
    TD<Replace<T, int, char>::type> t;
    return 0;
}

