

#include "shape.hpp"

namespace mf
{

BroadcastedShape broadcast(const Shape& s1, const Shape& s2)
{

	const int dims_1 = s1.get_dims().size();
	const int dims_2 = s2.get_dims().size();

	BroadcastedShape new_shape(&s1, &s2);
	int i = dims_1 - 1;
	int j = dims_2 - 1;

	do
	{
		const bool extend = s1.get_dims()[i].size != 1 && s2.get_dims()[j].size != 1;
		if(s1.get_dims()[i].size != s2.get_dims()[j].size && extend)
		{
			throw new std::length_error("The shapes are not boradastable");
		}

		if (!extend)
		{
			if (s1.get_dims().at(i).size == 1) new_shape.extend_dimension_shape_1(i);
			if (s2.get_dims().at(j).size == 1) new_shape.extend_dimension_shape_2(j);
		}
		--i;
		--j;

	} while (i >= 0 && j >= 0);

	if (i != -1)
	{
		for (; i >= 0; --i) {
			new_shape.extend_dimension_shape_2(i);
		}
	}
	else if (j != -1)
	{
		for (; j >= 0; --j) {
			new_shape.extend_dimension_shape_1(j);

		}
	}

	return new_shape;
}

bool is_broadcastable(const Shape& s1, const Shape& s2) noexcept
{
	const int dims_1 = s1.get_dims().size();
	const int dims_2 = s2.get_dims().size();
	int i = dims_1 - 1;
	int j = dims_2 - 1;
	do
	{
		const bool extend = s1.get_dims()[i].size != 1 && s2.get_dims()[j].size != 1;
		if(s1.get_dims()[i].size != s2.get_dims()[j].size && extend)
		{
			return false;
		}
	} while (i-- >= 0 && j-- >= 0);
	return true;
}

}
