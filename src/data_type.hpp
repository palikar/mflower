

#include "./utils/std_headers.hpp"


namespace mf
{

enum class DataType
{
    t_unknown,
    t_int8,
    t_int16,
    t_int32,
    t_int64,
    t_float32,
    t_float64,
    t_uint8,
    t_uint16,
    t_uint32,
    t_uint64
};


namespace detail
{

template<typename T>
struct bare_type
{
    using type = typename std::remove_cv<typename std::remove_pointer<typename std::remove_reference<T>::type>::type>::type;
};

template<typename T>
using bare_type_t = typename bare_type<T>::type;

} // namespace detail

namespace detail
{

constexpr const char* data_type_name(const DataType& t) noexcept
{
    
    switch(t)
    {
      case DataType::t_int8: return "t_int8";
      case DataType::t_int16: return "t_int16";
      case DataType::t_int32: return "t_int32";
      case DataType::t_int64: return "t_int64";
      case DataType::t_uint8: return "t_uint8";
      case DataType::t_uint16: return "t_uint16";
      case DataType::t_uint32: return "t_uint32";
      case DataType::t_uint64: return "t_uint64";
      case DataType::t_float32: return "t_float32";
      case DataType::t_float64: return "t_float64";
      default: return "t_unknown";
    }
    
}

constexpr DataType get_data_type(size_t size, bool is_signed)
{
    if(size == 1) { return is_signed ? DataType::t_int8 : DataType::t_uint8; }
    if(size == 2) { return is_signed ? DataType::t_int16 : DataType::t_uint16; }
    if(size == 4) { return is_signed ? DataType::t_int32 : DataType::t_uint32; }
    if(size == 8) { return is_signed ? DataType::t_int64 : DataType::t_uint64; }
    return  DataType::t_unknown;
}

template<typename T>
constexpr DataType get_data_type() noexcept
{

    if (typeid(T) == typeid(int)) {
        return get_data_type(sizeof(int), true);
    } else if (typeid(T) == typeid(double)) {
        return DataType::t_float64;
    } else if (typeid(T) == typeid(float)) {
        return DataType::t_float32;
    } else if (typeid(T) == typeid(long double)) {
        return DataType::t_float64;
    } else if (typeid(T) == typeid(char)) {
        return get_data_type(sizeof(char), std::is_signed_v<char>);
    } else if (typeid(T) == typeid(long)) {
        return get_data_type(sizeof(long), true);
    } else if (typeid(T) == typeid(unsigned int)) {
        return get_data_type(sizeof(unsigned int), false);
    }
    return DataType::t_unknown;
}

}


class DataTypeInfo
{
  public:

    constexpr DataTypeInfo(const std::type_info *t_ti, DataType t_dt, bool is_floating) :
        m_type_info(t_ti), m_data_type(t_dt), m_is_floating(is_floating)
    {}

    constexpr DataTypeInfo() noexcept = default;

    constexpr bool operator==(const std::type_info &ti) const noexcept
    {
        return ti == *m_type_info;
    }

    constexpr bool operator==(const DataTypeInfo &ti) const noexcept
    {
        return ti.m_data_type == m_data_type;
    }

    constexpr bool operator!=(const DataTypeInfo &ti) const noexcept
    {
        return !(operator==(ti));
    }

    constexpr bool operator!=(const std::type_info &ti) const noexcept
    {
        return !(operator==(ti));
    }

    constexpr bool is_floating() const noexcept
    {
        return m_is_floating;
    }

    const char * type_name() const noexcept
    { 
        return m_type_info->name();
    }

    const char * data_name() const noexcept
    {
        return detail::data_type_name(m_data_type);
    }

    DataType dtype() const { return m_data_type; }
    

  private:
    struct Unknown_Type {};

    const std::type_info *m_type_info = &typeid(Unknown_Type);
    DataType m_data_type = DataType::t_unknown;
    bool m_is_floating = false;
};


namespace detail
{
template<typename T>
struct GetDataType
{
    
    constexpr static DataTypeInfo get() noexcept
    {
        return DataTypeInfo(&typeid(detail::bare_type_t<T>),
                            detail::get_data_type<T>(),
                            std::is_floating_point_v<T>);
    }
};

}



template<typename T>
constexpr DataTypeInfo data_type() noexcept
{
    return detail::GetDataType<T>::get();
}

template<typename T>
constexpr DataTypeInfo data_type(const T &) noexcept
{
    return detail::GetDataType<T>::get();
}



} // namespace mf

