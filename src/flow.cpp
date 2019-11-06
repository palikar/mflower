#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

#include "data.hpp"
#include "tensor.hpp"
#include "engine.hpp"
#include "tensor_definitions.hpp"


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
    
    auto c_1 = mf::constant(mf::value(17.0), "c:0");
    auto c_2 = mf::constant(mf::value(3.0), "c:1");
    auto v_1 = mf::variable("v");

    auto res = mf::engine()->eval(v_1);
    
    
    double res_double = res->block()->operator()(0);
    std::cout << res_double << "\n";
    


    // auto b_1 = mf::value(1.0, 2.0, 3.0);
    // std::cout << b_1.shape() << "\n";
    // std::cout << b_1(0) << "\n";
    // auto t_1 = mf::Constant{mf::value(41.0), "c_1"};
    


    
    
    mf::finalize();    
    return 0;
}
