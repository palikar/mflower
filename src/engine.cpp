#include "./engine.hpp"


namespace mf
{


template<typename...TensType>
EvaluationContext::EvaluationContext(MFEngine& t_engine, TensType... t_tensors) : m_engine(std::ref(t_engine))
{
    (m_args.push_back(static_cast<TensorPtr>(t_tensors)), ...);
}

EvaluationContext::EvaluationContext(MFEngine& t_engine, std::vector<TensorPtr> t_tensors)  : m_engine(std::ref(t_engine)), m_args(std::move(t_tensors))
{};

void EvaluationContext::update_variable(const std::string& name, TensorPtr value)
{
    m_engine.get().scope().set(name, value->block());
}

void EvaluationContext::push_scope()
{};

Scope& EvaluationContext::scope()
{
    return m_engine.get().scope();
};

ReturnHandler::ReturnHandler(MFEngine& t_engine, TensorPtr t_result_location) : m_engine(t_engine),
                                                                                m_result_location(t_result_location)
{}

void ReturnHandler::result(const DataBuffer_Base* blk)
{
    
    *m_result_location.get()->block() = *blk;
}

void ReturnHandler::operator=(const DataBuffer_Base* blk)
{
    result(blk);
}


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


TensorPtr variable(std::string name)
{
    auto var = std::make_shared<Variable>(name);
    engine()->add_variable(var);
    return var;
}

// TensorPtr add(TensorPtr lhs, TensorPtr rhs, std::string name)
// {
//     auto add = std::make_shared<AddOp>(name);
//     default_engine->add_tensor(add, {lhs, rhs});
//     return add;
// }

}
