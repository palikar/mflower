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
    auto v_1 = mf::variable("v", 12.43);

    auto res = mf::engine()->eval(v_1);

    double res_double = res->data(0);
    std::cout << res_double << "\n";

    mf::finalize();    
    return 0;
}
