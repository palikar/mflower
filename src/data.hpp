#pragma once

#include "./utils/std_headers.hpp"
#include "./shape.hpp"


namespace mf
{

enum class DataTypes
{
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

class DataBuffer_Base
{
  public:
    
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    
 
    explicit DataBuffer_Base(Shape a_shape) : m_shape(a_shape)
    {};

    DataBuffer_Base(DataBuffer_Base&& ) = delete;
    DataBuffer_Base& operator=(DataBuffer_Base&&) = delete;
    DataBuffer_Base(const DataBuffer_Base&) = default;
    DataBuffer_Base& operator=(const DataBuffer_Base&) = default;
    virtual ~DataBuffer_Base(){};

    virtual void init() = 0;
    virtual void destroy() = 0;
    virtual void* data() = 0;
    virtual size_t size() const = 0;

    template<typename T>
    T* at(size_t index)
    {
        auto ptr = (static_cast<T*>(this->data()) + index);
        return ptr;
    }

    template<typename ... T>
    double& operator()(T... index)
    {
        const size_t offeset = m_shape.get_offset(static_cast<size_t>(index)...);
        return *this->at<double>(offeset);
    }

    const std::vector<Dimension>& dims() const { return m_shape.get_dims(); }
    const Shape& shape() const {return m_shape;}    

  public:
    static const bool is_static = false;
  protected:
    Shape m_shape;
    DataTypes m_type;
  private:
};

template<size_t N, typename T>
class StaticDataBuffer : public DataBuffer_Base
{
  public:
    typedef T                                     value_type;
    typedef value_type&                           reference;
    typedef const value_type&                     const_reference;
    typedef value_type*                           pointer;
    typedef const value_type*                     const_pointer;

    
    StaticDataBuffer(Shape a_shape) : DataBuffer_Base(a_shape) {};
    ~StaticDataBuffer(){};
    
    void init() override {};
    void destroy() override {};
    void* data() override {return m_data;}
    size_t size() const override{return N;};
    
  public:
    static const bool is_static = true;
  private:
    T m_data[N];
};

template <typename T>
class DynamicDataBuffer : public DataBuffer_Base
{
  public:
    
    typedef T                                     value_type;
    typedef value_type&                           reference;
    typedef const value_type&                     const_reference;
    typedef value_type*                           pointer;
    typedef const value_type*                     const_pointer;

    
    DynamicDataBuffer(Shape a_shape, size_t n) : DataBuffer_Base(a_shape), m_size(n) {};
    ~DynamicDataBuffer(){};

    void init() override { m_data = malloc(m_size * sizeof(T)); };
    void destroy() override { free(m_data); };
    void* data() override {return m_data;}
    size_t size() const override {return m_size;};

  public:
    static const bool is_static = false;
  private:
    void* m_data;
    size_t m_size;
    const size_t m_el_size = sizeof(T);
};


struct DataBlockHelper
{
  private:

    template<typename T, size_t... N>
    static auto get_block_heap()
    {
        constexpr size_t SIZE = (N * ...);

        if constexpr (SIZE < 25)
        {
            auto b = new StaticDataBuffer<SIZE, T>(Shape(N...));
            b->init();
            return b;
        }
        else
        {
            auto b = new DynamicDataBuffer<T>(Shape(N...), SIZE);
            b->init();
            return b;
        }
    }

    template<typename T, size_t... N>
    static auto get_block_stack()
    {
        constexpr size_t SIZE = (N * ...);

        if constexpr (SIZE < 10)
        {
            StaticDataBuffer<SIZE, T> b(Shape(N...));
            b.init();
            return b;
        }
        else
        {
            DynamicDataBuffer<T> b(Shape(N...), SIZE);
            b.init();
            return b;
        }
    }

    template<typename Type, typename...T>
    static auto get_block_stack(T...dims)
    {
        const size_t SIZE = (dims * ...);
        DynamicDataBuffer<Type> b(Shape(dims...), SIZE);
        b.init();
        return b;
    }


  public:

    template<typename T>
    inline static auto get(const std::vector<T>& vec)
    {
        auto blk = DataBlockHelper::get_block_stack<T>(vec.size());
        for (size_t i = 0; i < std::size(vec); ++i)
            *blk.template at<T>(i) = vec.at(i);
        
        return blk;
    }
    
    inline static auto get(const Shape& t_shape)
    {
        DynamicDataBuffer<float> blk(t_shape, t_shape.size());
        blk.init();
        return blk;
    }

    // handles array constructions
    template<typename T, size_t...N>
    inline static auto get(const T* values)
    {
        constexpr size_t SIZE = (N * ... );
        auto blk = DataBlockHelper::get_block_stack<T, N...>();

        for (size_t i = 0; i < SIZE; ++i)
            *blk.template at<T>(i) = *(values + i);
        
        return blk;
    }

    // handles value(1.3, 1.4, 1.6,...) constructions
    template<typename ... T>
    inline static auto get(T ... values)
    {
        using c_t = std::common_type_t<T...>;
        constexpr size_t s = sizeof...(values);
        auto blk = DataBlockHelper::get_block_stack<c_t, s>();
        size_t index = 0;
        ((*blk.template at<c_t>(index++) = values), ...);
        return blk;
    }
    
};




template<typename... Args>
auto value(Args&&... args)
{
    return DataBlockHelper::get(std::forward<Args>(args)...);
}



/////////////////////////////////////////////////////////////////////////////////
//  __  __       _ _   _     _ _                _                              //
// |  \/  |_   _| | |_(_) __| (_)_ __ ___      / \   _ __ _ __ __ _ _   _ ___  //
// | |\/| | | | | | __| |/ _` | | '_ ` _ \    / _ \ | '__| '__/ _` | | | / __| //
// | |  | | |_| | | |_| | (_| | | | | | | |  / ___ \| |  | | | (_| | |_| \__ \ //
// |_|  |_|\__,_|_|\__|_|\__,_|_|_| |_| |_| /_/   \_\_|  |_|  \__,_|\__, |___/ //
//                                                                  |___/      //
/////////////////////////////////////////////////////////////////////////////////

#define SIZE_T_S_0 size_t N
#define SIZE_T_S_1 SIZE_T_S_0 , size_t M
#define SIZE_T_S_2 SIZE_T_S_1 , size_t L
#define SIZE_T_S_3 SIZE_T_S_2 , size_t K
#define SIZE_T_S_4 SIZE_T_S_3 , size_t J
#define SIZE_T_S_5 SIZE_T_S_4 , size_t I

#define BRACKETS_S_0 [N]
#define BRACKETS_S_1 BRACKETS_S_0[M]
#define BRACKETS_S_2 BRACKETS_S_1[L]
#define BRACKETS_S_3 BRACKETS_S_2[K]
#define BRACKETS_S_4 BRACKETS_S_3[J]
#define BRACKETS_S_5 BRACKETS_S_4[I]

#define LETTERS_S_0 N
#define LETTERS_S_1 LETTERS_S_0, M
#define LETTERS_S_2 LETTERS_S_1, L
#define LETTERS_S_3 LETTERS_S_2, K
#define LETTERS_S_4 LETTERS_S_3, J
#define LETTERS_S_5 LETTERS_S_4, I


#define VALUE_FUN(dim) template<typename T, SIZE_T_S_##dim>     \
    inline static auto value(const T(&values) BRACKETS_S_##dim) \
    {                                                           \
        const T* s = reinterpret_cast<const T*>(&values);       \
        return DataBlockHelper::get<T, LETTERS_S_##dim>(s);     \
    }


VALUE_FUN(0) // one-dim array
VALUE_FUN(1) // two-dim array
VALUE_FUN(2) // three-dim array
VALUE_FUN(3) // four-dim array
VALUE_FUN(4) // five-dim array
VALUE_FUN(5) // six-dim array

}
