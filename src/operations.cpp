#include "operations.hpp"


double Add::evaluate(const Scope& scope)
{
	return lhs->evaluate(scope) + rhs->evaluate(scope);
}


double Sub::evaluate(const Scope& scope)
{
	return  rhs->evaluate(scope) - lhs->evaluate(scope);
}


double Multiply::evaluate(const Scope& scope)
{
	return lhs->evaluate(scope) * rhs->evaluate(scope);
}


double Devide::evaluate(const Scope& scope)
{
	return rhs->evaluate(scope) / lhs->evaluate(scope);
}
