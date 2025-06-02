#include "parser.h"

double convertStringToNum(char& index, optString str) {
	const char len = str.len();
	if (len == 0) return 0.0f;

	char newIndex = 0;
	optString numberStr = optString(len);
	numberStr[newIndex] = str[index];
	while (index < len && isdigit(str[index])) {
		numberStr[newIndex] = str[index];
		newIndex++;
		index++;
	}
	char* end;
	const double result = strtod(numberStr.convertChar(), &end);
	index--;
	return result;
}

void addValuesOperation(Operation& op, char& index, optString expr) {
	char beforeNum = index;
	beforeNum--;
	while (beforeNum != 0 && isdigit(expr[beforeNum - 1])) {
		beforeNum--;
	}
	op.value1 = convertStringToNum(beforeNum, expr);
	index++;
	op.value2 = convertStringToNum(index, expr);
}

void parseOp(optString& expr, Expression* expression) {
	const char len = expr.len();
	for (char i = 0; i < len; i++) {
		switch (expr[i]) {
		case '+': {
			Operation op;
			op.operation = PLUS;
			addValuesOperation(op, i, expr);

			expression->operations.push(op);
			break;
		}
		case '-': {
			Operation op;
			op.operation = MINUS;
			addValuesOperation(op, i, expr);

			expression->operations.push(op);
			break;
		}
		case '*': {
			Operation op;
			op.operation = MULT;

			addValuesOperation(op, i, expr);

			expression->operations.push(op);
			break;
		}
		case '/': {
			Operation op;
			op.operation = DIV;
			addValuesOperation(op, i, expr);

			expression->operations.push(op);
			break;
		}
		default:
			break;
		}
	}
	expression->success = true;
}


Expression parse(optString& expr) {
	Expression expression;
	//bool brackets = false;
	//char lastIndexOfBracket = 0;
	//for (char i = 0; i < expr.size(); i++) {
	//	if (expr[i] == '(') {
	//		brackets = true;
	//		char firstIndex = i - 1;
	//		const char firstChIndex = firstIndex;
	//		char firstCh = expr[firstIndex];
	//		bool checkForOp = firstCh == '*' || firstCh == '+' || firstCh == '-' || firstCh == '/';

	//		if (!checkForOp) {
	//			if (firstCh != '(') {
	//				expression.success = false;
	//				return expression;
	//			}
	//		}

	//		lastIndexOfBracket = firstIndex + 2;
	//		while (expr[lastIndexOfBracket] != ')') {
	//			if (expr[lastIndexOfBracket] == '\0' || expr[lastIndexOfBracket] == '(') {
	//				expression.success = false;
	//				return expression;
	//			}
	//			lastIndexOfBracket++;
	//		}

	//		if (lastIndexOfBracket <= 1) {
	//			expression.success = false;
	//			return expression;
	//		}
	//		if (!checkForOp)
	//			firstIndex += 1;
	//		else
	//			firstIndex += 2; // it skips operation and (. For example from 2 |* (2 + 2) to 2 * ( |2 + 2)
	//		for (char i = 0; i < expr.size(); i++)
	//		{
	//			if (expr[firstIndex] != ')')
	//				replaceIndex(expr, i, firstIndex);
	//			else
	//			{
	//				replaceIndex(expr, i, firstCh);
	//				break;
	//			}
	//			firstIndex++;
	//		}

	//		if (checkForOp)
	//			expr.erase(expr.begin() + firstChIndex + 1);
	//	}
	//}

	parseOp(expr, &expression);
	return expression;
}



// void swap(optString array, char index1, char index2) {
// 	char tempi1 = array[index1];
// 	array[index1] = index2;
// 	array[index2] = tempi1;
// }

// void replaceIndex(optString& array, char index1, char index2) {
// 	if (index1 < array.len() && index2 < array.len()) {
// 		swap(array, index1, index2);
// 	}
// }