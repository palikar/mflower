

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

    const Shape shape() const {return m_shape;}
    
  public:
    static const bool is_static = false;
    Shape m_shape;
    DataTypes m_type;
  private:
};


template<size_t N>
class StaticDataBuffer : public DataBuffer_Base
{
  public:
    StaticDataBuffer(Shape a_shape) : DataBuffer_Base(a_shape)
    {};
    ~StaticDataBuffer(){};
    void init() override {};
    void destroy() override {};
    void* data() override {return m_data.data();}

  public:
    static const bool is_static = false;
  private:
    std::array<void*, N> m_data;
};


class DynamicDataBuffer : public DataBuffer_Base
{
  public:
    DynamicDataBuffer(Shape a_shape, size_t n) : DataBuffer_Base(a_shape), m_size(n)
    {};
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


struct DataBufferFactory
{
    template<size_t... N>
    static auto get()
    {
        constexpr size_t SIZE = (N * ...);
        
        if constexpr (SIZE < 25)
        {
            auto b = new StaticDataBuffer<SIZE>(Shape(N...));
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

    template<size_t... N>
    static auto get_block_stack()
    {
        constexpr size_t SIZE = (N * ...);
        
        if constexpr (SIZE < 10)
        {
            StaticDataBuffer<SIZE> b(Shape(N...));
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

    template<typename...T>
    static auto get_block_stack(T...dims)
    {
        constexpr size_t SIZE = (dims * ...);
        DynamicDataBuffer b(Shape(dims...), SIZE);
        b.init();
        return b;
    }
};

struct DataBlockFact
{

    template<typename T, size_t N>
    inline static auto get(T(&values)[N])
    {
        auto blk = DataBufferFactory::get_block_stack<N>();
        return blk;
    }

    
    template<typename T, size_t N, size_t M>
    inline static auto get(T(&values)[N][M])
    {
        auto blk = DataBufferFactory::get_block_stack<N,M>();
        return blk;
    }


    template<typename T>
    static auto get(const std::initializer_list<T> values)
    {
        const size_t s = values.size();
        std::cout << s << "\n";
        auto blk = DataBufferFactory::get_block_stack<s>();
        return blk;
    }
    
    template<typename T>
    inline static auto get(T value)
    {
        auto blk = DataBufferFactory::get_block_stack<1>();
        return blk;
    }    

    
    template<typename ... T>
    inline static auto get(T ... values)
    {
        constexpr size_t s = sizeof...(values);
        auto blk = DataBufferFactory::get_block_stack<s>();
        return blk;
    }
};



// template<typename T, size_t N>
// inline static auto value(const T(&values)[N])
// {
//     return DataBlockFact::get(values);
// }

template<typename... Args>
auto value(Args&&... args)
{
    return DataBlockFact::get(std::forward<Args>(args)...);
}

template<typename T>
auto value(const std::initializer_list<T>&& args)
{
    return DataBlockFact::get(std::forward<decltype(args)>(args));
}


}

