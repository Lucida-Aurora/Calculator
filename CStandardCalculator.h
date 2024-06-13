#pragma once
#include <stack>
#include <vector>
#include <afxext.h>
using namespace std;
struct CCalculatorInfo {
	//操作数
	vector<double> m_operands;
	//操作符
	vector<char> m_operator;
	//计算结果
	double m_result = 0;
};



class CStandardCalculator {

public:
	//计算信息
	CCalculatorInfo m_calculatorInfo;

	//输入数字是否结束
	bool m_isEnd = TRUE;
	//是否输入了小数点
	bool m_isDot = FALSE;
	//是否输入了操作符
	bool m_isOperator = FALSE;
	//计算表达式
	void CalculateExpression();
	//收集操作数
	void CollectOperands(double operand);
	//收集操作符
	void CollectOperators(char op);
	//删除操作数
	void DeleteOperand();
	//删除操作符
	void DeleteOperator();



};

