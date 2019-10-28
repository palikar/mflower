#include "./engine.hpp"


namespace mf
{

template<typename...TensType>
EvaluationContext::EvaluationContext(MFEngine& t_engine, TensType... t_tensors) : m_engine(std::ref(t_engine))
{
    (m_args.push_back(static_cast<TensorPtr>(t_tensors)), ...);
}

EvaluationContext::EvaluationContext(MFEngine& t_engine, std::vector<TensorPtr> t_tensors) : m_engine(std::ref(t_engine)),
                                                                                             m_args(std::move(t_tensors))
{			
}


void EvaluationContext::update_variable(const std::string& name, TensorPtr value)
{
    m_engine.get().scope().set(name, value->block());
};


template<size_t i>
TensorPtr EvaluationContext::get_argument()
{
    return m_args.at(i);
}

void EvaluationContext::push_scope(){}

Scope& EvaluationContext::scope()
{
    return m_engine.get().scope();
};



MFEngine* default_engine;

void init()
{
    default_engine = new MFEngine();
}

void finalize()
{
    delete default_engine;
}

MFEngine* engine()
{
    return default_engine; 
}

TensorPtr variable(std::string name, double value)
{
    auto var = std::make_shared<Variable>(name);
    var->init_data(std::vector{value});
    default_engine->add_variable(var);
    return var;
}

TensorPtr constant(double value)
{
    auto cons = std::make_shared<Constant>(value);
    default_engine->add_tensor(cons);
    return cons;
}


}
