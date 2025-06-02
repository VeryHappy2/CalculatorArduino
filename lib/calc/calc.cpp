#include "calc.h"
struct NullableDouble {
	bool hasValue = false;
	double value;

	void set(double val) {
		value = val;
		hasValue = true;
	}
};

double calcOp(Operation op, NullableDouble resultOut, optVector<Result>& results, char index, char& indexResult, char len) {
	double result = 0;
	switch (op.operation)
	{
	case MINUS: {
		if (!results.empty()) {
			if (index + 1 == results[indexResult].index) {
				result = op.value1 - results[indexResult].result;
				indexResult++;
				return result;
			}

			if (results[0].index == 0 && index == 0) {
				if (len == 1 && !results.empty()) {
					result = results[0].result + op.value1;
					result += result + results[1].result;
					return result;
				}
				result = results[indexResult].result + op.value1;
				indexResult++;
				return result;
			}
		}
		if (resultOut.hasValue) return resultOut.value - op.value2;
		return result = op.value1 - op.value2;
		break;
	}
	case PLUS: {
		if (!results.empty()) {
			if (index + 1 == results[indexResult].index) {
				result = op.value1 + results[indexResult].result;
				indexResult++;
				return result;
			}

			if (results[0].index == 0 && index == 0) {
				if (len == 1 && !results.empty()) {
					result = results[0].result + op.value1;
					result += result + results[1].result;
					return result;
				}
				result =  results[indexResult].result + op.value1;
				indexResult++;
				results[0].index = 120;
				return result;
			}
		}
		if (resultOut.hasValue)
			return result = resultOut.value + op.value2;
		return result = op.value1 + op.value2;
	}
	default:
		break;
	}
	return result;
}

Result checkDivMul(char& index, Result result, optVector<Operation>& ops, char len) {
	index++;
	while (index < len) { // it needs if the next op is mult or div
		switch (ops[index].operation)
		{
		case MULT:
			result.result = result.result * ops[index].value2;
			ops.del(index);
			len--;
			break;
		case DIV:
			result.result = result.result / ops[index].value2;
			ops.del(index);
			len--;
			break;
		default:
			return result;
		}
		index++;
	}
	return result;
}

double calc(optString& expr) {
	Expression respExpr = parse(expr);
	if (!respExpr.success) return 0.0f;
	char len = respExpr.operations.len();
	optVector<Operation>& ops = respExpr.operations;
	optVector<Result>& results = respExpr.results;
	bool containMinOrPlus = false;
	for (char i = 0; i < len;) {
		switch (respExpr.operations[i].operation)
		{
		case MULT:
		{
			Operation op = ops[i];
			Result resultObj;
			resultObj.result = op.value1 * op.value2;
			resultObj.index = i;
			resultObj = checkDivMul(i, resultObj, ops, len);
			results.push(resultObj);
			ops.del(resultObj.index);
			continue;
		}
		case DIV:
		{
			Operation op = ops[i];
			Result resultObj;
			resultObj.result = op.value1 / op.value2;
			resultObj.index = i;
			resultObj = checkDivMul(i, resultObj, ops, len);
			results.push(resultObj);
			ops.del(resultObj.index);

			continue;
		}
		default:
			containMinOrPlus = true;
			break;
		}
		i++;
	}

	if (!results.empty() && containMinOrPlus == false)
		return results[0].result;

	char indexResult = 0;
	len = respExpr.operations.len();
	NullableDouble result;
	result.value = 0;
	for (char i = 0; i < len; i++)
	{
		Operation op = respExpr.operations[i];
		result.set(calcOp(op, result, results, i, indexResult, len));
	}

	return result.value;
}