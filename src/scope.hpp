#pragma once

#include <string>
#include <unordered_map>

#include "tensor.hpp"


namespace mf
{

// class Variable;
// template<typename T>
// class DataBlock;


class Scope
{
  public:
    Scope()
    {};

    ~Scope()
    {};
    
    DataBuffer_Base* get_variable_value(const std::string& name) const
    {
        return m_variables.at(name);
    }
        
    void put_variable(const std::string& name, DataBuffer_Base* val)
    {
        m_variables.insert({name, val});
    }

    void push(){};
    void pop(){};

	
    void set(const std::string& name, DataBuffer_Base* val)
    {
        m_variables.insert({name, val});
    }
    
    
  private:
    
    std::unordered_map<std::string, DataBuffer_Base*> m_variables;
};

}
