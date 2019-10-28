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

    DataBlock<double> get_variable_value(const std::string& name) const
			{
        return m_variables.at(name);
			}

    void put_variable(const std::string& name, DataBlock<double> val)
			{
        m_variables.insert({name, val});
			}

		void push(){};
		void pop(){};

	
		void set(const std::string& name, DataBlock<double> val)
			{
				m_variables.insert({name, val});
			}
    
    
	private:
    
    std::unordered_map<std::string, DataBlock<double>> m_variables;
	};

}
