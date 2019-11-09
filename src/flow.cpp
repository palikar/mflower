#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>

#include "data.hpp"
#include "tensor.hpp"
#include "engine.hpp"
#include "tensor_definitions.hpp"
// #include "data_type.hpp"


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

    // auto c_1 = mf::constant(mf::value(17.0), "c:0");
    // auto c_2 = mf::constant(mf::value(3.0), "c:1");
    // auto v_1 = mf::variable("v");

    // auto res = mf::engine()->eval(v_1);

    // double res_double = res->block()->operator()(0);
    // std::cout << res_double << "\n";

    // int a = 5;
    // auto a_t = mf::data_type(a);

    // std::cout << std::boolalpha;
    // std::cout << "a_t_1 : " << a_t.type_name() << "\n";
    // std::cout << "a_t_1 : " << a_t.is_floating() << "\n";
    // std::cout << "a_t_1 : " << a_t.data_name() << "\n";


    auto b_1 = mf::value(1.0f, 42.2f, 3.0f);

    std::cout << b_1.shape() << "\n";
    std::cout << b_1.type_info().data_name() << "\n";

    // std::cout << b_1(0) << "\n";
    std::cout << b_1.get_as<double>(0) << "\n";
    std::cout << b_1.get_as<float>(0) << "\n";
    std::cout << b_1.get_as<int>(0) << "\n";
    std::cout << "-----------" << "\n";
    std::cout << b_1.get_as<double>(1) << "\n";
    std::cout << b_1.get_as<float>(1) << "\n";
    std::cout << b_1.get_as<int>(1) << "\n";
    std::cout << "-----------" << "\n";
    std::cout << b_1.get_as<double>(2) << "\n";
    std::cout << b_1.get_as<float>(2) << "\n";
    std::cout << b_1.get_as<int>(2) << "\n";
    std::cout << "-----------" << "\n";



    mf::finalize();
    return 0;
}
