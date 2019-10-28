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

    auto c_1 = mf::constant(17.0, "c:0");
    auto c_2 = mf::constant(3.0, "c:1");
    auto v_1 = mf::variable("v", 12.00);

    auto add_1 = mf::add(c_1, v_1, "add:0");
    auto add_2 = mf::add(add_1, c_2, "add:1");

    auto res = mf::engine()->eval(add_2);
    double res_double = res->data(0);
    std::cout << res_double << "\n";

    mf::finalize();    
    return 0;
}
