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
 
    explicit DataBuffer_Base(Shape a_shape) : m_shape(a_shape)
    {};

    DataBuffer_Base(DataBuffer_Base&& ) = delete;
    DataBuffer_Base& operator=(DataBuffer_Base&&) = delete;
    DataBuffer_Base(const DataBuffer_Base&) = default;
    DataBuffer_Base& operator=(const DataBuffer_Base&) = default;
    virtual ~DataBuffer_Base(){};

    virtual void init() = 0;
    virtual void* data() = 0;
    virtual void destroy() = 0;

    template<typename T>
    T* at(size_t index)
    {
        auto ptr = (static_cast<T*>(this->data()) + index);
        return ptr;
    }

    const Shape shape() const {return m_shape;}

  public:
    static const bool is_static = false;
    Shape m_shape;
    DataTypes m_type;
  private:
};


template<size_t N, typename T>
class StaticDataBuffer : public DataBuffer_Base
{
  public:
    StaticDataBuffer(Shape a_shape) : DataBuffer_Base(a_shape) {};
    ~StaticDataBuffer(){};
    
    void init() override {};
    void destroy() override {};
    void* data() override {return m_data.data();}
    
  public:
    static const bool is_static = false;
  private:
    std::array<T, N> m_data;
};


class DynamicDataBuffer : public DataBuffer_Base
{
  public:
    DynamicDataBuffer(Shape a_shape, size_t n) : DataBuffer_Base(a_shape), m_size(n) {};
    ~DynamicDataBuffer(){};

    void init() override { m_data = malloc(m_size * sizeof(void*)); };
    void destroy() override { free(m_data); };
    void* data() override {return m_data;}

  public:
    static const bool is_static = false;
  private:
    void* m_data;
    size_t m_size;
};


struct DataBlockFact
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
            auto b = new DynamicDataBuffer(Shape(N...), SIZE);
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
            DynamicDataBuffer b(Shape(N...), SIZE);
            b.init();
            return b;
        }
    }

    template<typename Type, typename...T>
    static auto get_block_stack(T...dims)
    {
        constexpr size_t SIZE = (dims * ...);
        DynamicDataBuffer b(Shape(dims...), SIZE);
        b.init();
        return b;
    }


  public:
    
    template<typename T, size_t...N>
    inline static auto get(const T* values)
    {
        auto blk = DataBlockFact::get_block_stack<T, N...>();
        return blk;
}


    template<typename T>
    inline static auto get(T value)
    {
        auto blk = DataBlockFact::get_block_stack<T, 1>();
        auto ptr = blk.template at<T>(0);
        *ptr = value;
        return blk;
    }


    template<typename ... T>
    inline static auto get(T ... values)
    {
        using c_t = std::common_type_t<T...>;
        constexpr size_t s = sizeof...(values);
        auto blk = DataBlockFact::get_block_stack<c_t, s>();
        
        size_t index = 0;

        ((*blk.template at<c_t>(index++) = values), ...);
        
        return blk;
    }
    
};




template<typename... Args>
auto value(Args&&... args)
{
    return DataBlockFact::get(std::forward<Args>(args)...);
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
        return DataBlockFact::get<T, LETTERS_S_##dim>(s);       \
    }

VALUE_FUN(0) // one-dim array
VALUE_FUN(1) // two-dim array
VALUE_FUN(2) // three-dim array
VALUE_FUN(3) // four-dim array
VALUE_FUN(4) // five-dim array
VALUE_FUN(5) // six-dim array

}
