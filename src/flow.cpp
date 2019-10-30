#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

// #include "tensor.hpp"
// #include "engine.hpp"
#include "data.hpp"


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
    // mf::init();

    // auto c_1 = mf::constant(17.0, "c:0");
    // auto c_2 = mf::constant(3.0, "c:1");
    // auto v_1 = mf::variable("v", 12.00);
    // auto add_1 = mf::add(c_1, v_1, "add:0");
    // auto add_2 = mf::add(add_1, c_2, "add:1");
    // auto res = mf::engine()->eval(add_2);
    // double res_double = res->data(0);
    // std::cout << res_double << "\n";


    std::vector vec{1.0, 2.0, 3.0};
    auto b_1 = mf::value(vec);
    
    std::cout << b_1.shape() << "\n";

    b_1(0) = 10;
        
    std::cout << b_1(0) << "\n";
    std::cout << b_1(1) << "\n";
    std::cout << b_1(2) << "\n";
    
    
    // auto b_2 = mf::value(1.0);
    // auto b_3 = mf::value(1.0, 2.0, 3.0, 4.0);

    // std::cout << "b_2: "  << b_2.shape()  << "\n";
    // std::cout << "b_3: " << b_3.shape()  << "\n";
    

    // mf::finalize();    
    return 0;
}
