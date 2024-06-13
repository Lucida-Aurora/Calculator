#include "pch.h"
#include "CStandardCalculator.h"

#include <stack>
using namespace std;

// 优先级函数
int precedence(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

// 进行计算的函数
double applyOp(double a, double b, char op) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/':
		//if (b == 0) throw runtime_error("Division by zero");
		return a / b;
		//default: throw runtime_error("Invalid operator");
	default: return 0;

	}
}

// 计算中缀表达式的值
double evaluate(const vector<double>& operands, const vector<char>& operators) {
	stack<double> values;  // 值栈
	stack<char> ops;       // 操作符栈

	size_t operandIndex = 0;
	size_t operatorIndex = 0;

	// 第一个操作数一定会入栈
	if (!operands.empty()) {
		values.push(operands[operandIndex++]);
	}

	while (operandIndex < operands.size() || operatorIndex < operators.size()) {
		if (operatorIndex < operators.size()) {
			char currentOp = operators[operatorIndex];

			while (!ops.empty() && precedence(ops.top()) >= precedence(currentOp)) {
				double val2 = values.top(); values.pop();
				double val1 = values.top(); values.pop();
				char op = ops.top(); ops.pop();
				values.push(applyOp(val1, val2, op));
			}

			ops.push(currentOp);
			operatorIndex++;
		}

		if (operandIndex < operands.size()) {
			values.push(operands[operandIndex++]);
		}
	}

	while (!ops.empty()) {
		double val2 = values.top(); values.pop();
		double val1 = values.top(); values.pop();
		char op = ops.top(); ops.pop();
		values.push(applyOp(val1, val2, op));
	}

	return values.top();
}

void CStandardCalculator::CalculateExpression() {

	m_calculatorInfo.m_result = evaluate(m_calculatorInfo.m_operands, m_calculatorInfo.m_operator);

}

void CStandardCalculator::CollectOperands(double operand) {
	m_calculatorInfo.m_operands.push_back(operand);
}


void CStandardCalculator::CollectOperators(char op) {
	m_calculatorInfo.m_operator.push_back(op);
}

void CStandardCalculator::DeleteOperand() {
	m_calculatorInfo.m_operands.pop_back();
}

void CStandardCalculator::DeleteOperator() {
	m_calculatorInfo.m_operator.pop_back();
}




