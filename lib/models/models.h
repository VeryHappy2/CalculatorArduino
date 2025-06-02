#include "optVector.h"

enum EnumOperation
{
	PLUS,
	MINUS,
	MULT,
	DIV
};

struct Operation
{
	EnumOperation operation;
	double value1;
	double value2;
};

struct Result
{
	char index;
	double result;
};

struct Expression
{
	bool success;
	optVector<Operation> operations;
	optVector<Result> results;
};