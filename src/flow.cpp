#include <iostream>
#include <vector>
#include <algorithm>

#include "tensor.hpp"
#include "engine.hpp"


template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    if ( !v.empty() ) {
        out << '[';
        std::copy (v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b]";
    }
    return out;
}

int main(int, char**)
{
    mf::init();


    auto c_1 = mf::constant(5.5);
    auto c_2 = mf::constant(10.5);


    auto v_1 = mf::variable("v", 10.5);

    mf::engine()->eval(c_1);


    mf::finalize();    
    return 0;
}
