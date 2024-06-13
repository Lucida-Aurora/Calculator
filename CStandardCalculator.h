#pragma once
#include <stack>
#include <vector>
#include <afxext.h>
using namespace std;
struct CCalculatorInfo {
	//������
	vector<double> m_operands;
	//������
	vector<char> m_operator;
	//������
	double m_result = 0;
};



class CStandardCalculator {

public:
	//������Ϣ
	CCalculatorInfo m_calculatorInfo;

	//���������Ƿ����
	bool m_isEnd = TRUE;
	//�Ƿ�������С����
	bool m_isDot = FALSE;
	//�Ƿ������˲�����
	bool m_isOperator = FALSE;
	//������ʽ
	void CalculateExpression();
	//�ռ�������
	void CollectOperands(double operand);
	//�ռ�������
	void CollectOperators(char op);
	//ɾ��������
	void DeleteOperand();
	//ɾ��������
	void DeleteOperator();



};

