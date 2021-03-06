#pragma once

#include <ranges.hpp>
#include <cstdint>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <stdexcept>
#include <utility>




namespace mf
{
namespace ut = ranges;

struct Dimension
{
    Dimension(size_t i) : size(i) {};
	int32_t size;
};

class Shape
{
  public:

	explicit Shape(size_t x_axis)
    {
        dims.push_back(Dimension(x_axis));
        this->elements_cnt = x_axis;
        generate_strides();

    };

	Shape(size_t x_axis, size_t y_axis)
    {
        dims.push_back(Dimension(x_axis));
        dims.push_back(Dimension(y_axis));
        this->elements_cnt = x_axis*y_axis;
        generate_strides();
    };

	Shape(size_t x_axis, size_t y_axis, size_t z_axis)
    {
        dims.push_back(Dimension(x_axis));
        dims.push_back(Dimension(y_axis));
        dims.push_back(Dimension(z_axis));
        this->elements_cnt = x_axis*y_axis*z_axis;
        generate_strides();
    };

	template<typename T>
	explicit Shape(T dimensions)
    {
        this->elements_cnt = 1;
        std::for_each(std::begin(dimensions), std::end(dimensions),
                      [this](const int d){
                          this->elements_cnt *= d;
                          this->dims.push_back(Dimension(d));});

        generate_strides();
    };

	~Shape() = default;


	size_t get_offset(size_t i)
    {
        return strides[0]*i;
    };

	size_t get_offset(size_t i, int j)
    {
        return strides[0]*i + strides[1]*j;

    }

	size_t get_offset(size_t i, size_t j, size_t k)
    {
        return strides[0]*i + strides[1]*j + strides[2]*k;
    }

	template<typename T, class Container = std::initializer_list<T>>
	size_t get_offset(Container index) const
    {
        return get_offset(index);
    }

	template<typename T>
	size_t get_offset(T index) const
    {
        if (dims.size() < std::size(index))
        {
            std::cout << "baaad!" << "\n";
        }

        int offset = 0;
        for (size_t i = 0; i < strides.size(); ++i)
        {
            offset += strides[i] * (*(std::begin(index) + i));
        }

        return offset;
    }

    bool operator==(const Shape &other) const
    {
        for (auto i : ut::indices(other.dims))
            if (this->dims[i].size != other.dims[i].size) return false;
        return true;
    }

	const std::vector<Dimension>&  get_dims() const
    {
        return this->dims;
    }

    size_t size() const
    {
        return static_cast<size_t>(elements_cnt);
	};

  private:
	void generate_strides()
    {
        strides.clear();
        int s = 1;
        strides.push_back(1);
        for(size_t i = dims.size() - 1; i > 0; --i)
        {
            s *= dims[i].size;
            strides.push_back(s);
        }
        std::reverse(std::begin(strides), std::end(strides));

    };

	const std::vector<int>&  get_strides() const
    {
        return this->strides;
    }

	

  private:
	std::vector<Dimension> dims;
	std::vector<int> strides;
	int elements_cnt;

};

class BroadcastedShape
{

  public:

	BroadcastedShape(const Shape* s1, const Shape* s2):
		shape_1(s1),
		shape_2(s2)
    {

    }

	void extend_dimension_shape_1(int dim)
    {
        s1_extended.push_back(dim);
    };

	void extend_dimension_shape_2(int dim)
    {
        s2_extended.push_back(dim);
    };

	~BroadcastedShape() = default;

	size_t get_offset_1(std::initializer_list<int> index)
    {
        std::vector<int> index_vec;

        const size_t dims = std::max(shape_1->get_dims().size(), shape_2->get_dims().size());
        for (size_t i = 0; i < dims; ++i)
        {
            if (std::find(s1_extended.begin(), s1_extended.end(), (int)i) == s1_extended.end())
                index_vec.push_back((*(index.begin()+1)));
            else if ((index.size() - i - 1) < shape_1->get_dims().size())
                index_vec.push_back(0);
        }

        return shape_1->get_offset(index_vec);
    }

	size_t get_offset_2(std::initializer_list<int> index)
    {
        std::vector<int> index_vec;
        const size_t dims = std::max(shape_1->get_dims().size(), shape_2->get_dims().size());
        for (size_t i = 0; i < dims; ++i)
        {

            if (std::find(s2_extended.begin(), s2_extended.end(), (int)i) == s2_extended.end())
                index_vec.push_back((*(index.begin()+i)));
            else if ((index.size() - i - 1) < shape_2->get_dims().size())
                index_vec.push_back(0);
        }
        return shape_2->get_offset(index_vec);
    }

	Shape to_shape() const
    {
        
        std::vector<int> new_dims;
        int i = shape_1->get_dims().size()-1;
        int j = shape_2->get_dims().size()-1;

        const auto& dims1 = shape_1->get_dims();
        const auto& dims2 = shape_2->get_dims();
        do
        {
            new_dims.insert(new_dims.begin(), std::max(dims1[i].size, dims2[j].size));
            --i;
            --j;
        }while (i >= 0 && j >= 0);

        if (i != -1)
        {
            for (; i >= 0; --i) {
                new_dims.insert(new_dims.begin(), dims1[i].size);
            }
        }        
        else if (j != -1)
        {
            for (; j >= 0; --j) {
                new_dims.insert(new_dims.begin(), dims2[j].size);
            }
        }
		
        return Shape(std::move(new_dims));
    };


  private:
	const Shape* shape_1;
	const Shape* shape_2;

	std::vector<int> s1_extended;
	std::vector<int> s2_extended;


};

BroadcastedShape broadcast(const Shape& s1, const Shape& s2);
bool is_broadcastable(const Shape& s1, const Shape& s2) noexcept;

}


std::ostream& operator<< (std::ostream& out, const mf::Shape& v);
