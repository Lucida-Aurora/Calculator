// CStClacDlg.cpp: 实现文件
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "CStClacDlg.h"
#include "CStandardCalculator.h"
#include "CHisDlg.h"
using namespace std;


//历史记录
stack<CCalculatorInfo> g_history;
//记忆
stack<double> g_memory;

//表达式
CString g_expression;

//存入输入的操作数 CString类型
CString g_input = L"0";

//构造计算器
CStandardCalculator calculator;
HWND g_hWnd;
CStatic g_Expression;
CStatic g_Input;




// CStClacDlg 对话框

IMPLEMENT_DYNAMIC(CStClacDlg, CDialogEx)

CStClacDlg::CStClacDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ST_CALC, pParent) {

}

CStClacDlg::~CStClacDlg() {
}

void CStClacDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_HIS, m_HisTabCtrl);
	DDX_Control(pDX, IDC_STATIC_EXP, g_Expression);
	DDX_Control(pDX, IDC_STATIC_INPUT, g_Input);
}

BOOL CStClacDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	m_HisTabCtrl.InsertItem(0, _T("历史记录"));
	m_HisTabCtrl.InsertItem(1, _T("记忆"));
	m_HisDlg.Create(IDD_DIALOG_HISTORY, &m_HisTabCtrl);
	m_MemDlg.Create(IDD_DIALOG_MEMORY, &m_HisTabCtrl);
	CRect rect;
	m_HisTabCtrl.GetClientRect(&rect);
	rect.top += 20;


	m_HisDlg.MoveWindow(&rect);
	m_MemDlg.MoveWindow(&rect);

	m_pDialog[0] = &m_HisDlg;
	m_pDialog[1] = &m_MemDlg;



	m_HisDlg.ShowWindow(SW_SHOW);
	m_MemDlg.ShowWindow(SW_HIDE);

	m_nCurSelTab = 0;
	CFont font;
	font.CreatePointFont(200, _T("Arial"));
	g_Expression.SetFont(&font);
	g_Input.SetFont(&font);
	g_Expression.SetWindowText(g_expression);
	g_Input.SetWindowText(g_input);
	return TRUE;
}


BEGIN_MESSAGE_MAP(CStClacDlg, CDialogEx)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_HIS, &CStClacDlg::OnTcnSelchangeTabHis)
	ON_BN_CLICKED(IDC_BUTTON_ONE, &CStClacDlg::OnBnClickedButtonOne)
	ON_BN_CLICKED(IDC_BUTTON_TWO, &CStClacDlg::OnBnClickedButtonTwo)
	ON_BN_CLICKED(IDC_BUTTON_THREE, &CStClacDlg::OnBnClickedButtonThree)
	ON_BN_CLICKED(IDC_BUTTON_FOUR, &CStClacDlg::OnBnClickedButtonFour)
	ON_BN_CLICKED(IDC_BUTTON_FIVE, &CStClacDlg::OnBnClickedButtonFive)
	ON_BN_CLICKED(IDC_BUTTON_SIX, &CStClacDlg::OnBnClickedButtonSix)
	ON_BN_CLICKED(IDC_BUTTON_SEVEN, &CStClacDlg::OnBnClickedButtonSeven)
	ON_BN_CLICKED(IDC_BUTTON_EIGHT, &CStClacDlg::OnBnClickedButtonEight)
	ON_BN_CLICKED(IDC_BUTTON_NINE, &CStClacDlg::OnBnClickedButtonNine)
	ON_BN_CLICKED(IDC_BUTTON_ZERO, &CStClacDlg::OnBnClickedButtonZero)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CStClacDlg::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_POSITIVEORNEGATIVE, &CStClacDlg::OnBnClickedButtonPositiveornegative)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CStClacDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUBTRACT, &CStClacDlg::OnBnClickedButtonSubtract)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CStClacDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CStClacDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_EQUAL, &CStClacDlg::OnBnClickedButtonEqual)
	ON_BN_CLICKED(IDC_BUTTON_SQUARE, &CStClacDlg::OnBnClickedButtonSquare)
	ON_BN_CLICKED(IDC_BUTTON_BACKSPACE, &CStClacDlg::OnBnClickedButtonBackspace)
	ON_BN_CLICKED(IDC_BUTTON_CE, &CStClacDlg::OnBnClickedButtonCe)
	ON_BN_CLICKED(IDC_BUTTON_C, &CStClacDlg::OnBnClickedButtonC)
	ON_BN_CLICKED(IDC_BUTTON_PRESCRIPTIOPN, &CStClacDlg::OnBnClickedButtonPrescriptiopn)
	ON_BN_CLICKED(IDC_BUTTON_COUNTDOWN, &CStClacDlg::OnBnClickedButtonCountdown)
	ON_BN_CLICKED(IDC_BUTTON_MS, &CStClacDlg::OnBnClickedButtonMs)
	ON_BN_CLICKED(IDC_BUTTON_MC, &CStClacDlg::OnBnClickedButtonMc)
	ON_BN_CLICKED(IDC_BUTTON_MR, &CStClacDlg::OnBnClickedButtonMr)
	ON_BN_CLICKED(IDC_BUTTON_M_ADD, &CStClacDlg::OnBnClickedButtonMAdd)
	ON_BN_CLICKED(IDC_BUTTON_M_SUB, &CStClacDlg::OnBnClickedButtonMSub)
	ON_MESSAGE(WM_LIST_TO_CUR, &CStClacDlg::OnListToCur)
	ON_BN_CLICKED(IDC_BUTTON_PER, &CStClacDlg::OnBnClickedButtonPer)
END_MESSAGE_MAP()

LRESULT CStClacDlg::OnListToCur(WPARAM wParam, LPARAM lParam) {
	CCalculatorInfo* p = reinterpret_cast<CCalculatorInfo*>(wParam);
	if (p != NULL) {
		calculator.m_calculatorInfo.m_operands.clear();
		calculator.m_calculatorInfo.m_operator.clear();
		for (int i = 0; i < p->m_operands.size() - 1; i++)
			calculator.m_calculatorInfo.m_operands.push_back(p->m_operands[i]);
		for (int i = 0; i < p->m_operator.size(); i++)
			calculator.m_calculatorInfo.m_operator.push_back(p->m_operator[i]);
		calculator.m_calculatorInfo.m_result = p->m_result;
		delete p;

	}
	return 0;
}

// CStClacDlg 消息处理程序


void CStClacDlg::OnTcnSelchangeTabHis(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: 在此添加控件通知处理程序代码
	m_pDialog[m_nCurSelTab]->ShowWindow(SW_HIDE);
	m_nCurSelTab = m_HisTabCtrl.GetCurSel();
	m_pDialog[m_nCurSelTab]->ShowWindow(SW_SHOW);

	*pResult = 0;
}


void Handle(CStatic& inp, char c) {
	if (calculator.m_isEnd) {
		g_input = "";
		calculator.m_isEnd = false;
		g_input += c;
		inp.SetWindowText(g_input);
		calculator.m_isOperator = false;
		return;
	}
	g_input += c;
	inp.SetWindowText(g_input);
}
void CStClacDlg::OnBnClickedButtonOne() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '1');
}



void CStClacDlg::OnBnClickedButtonTwo() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '2');
}


void CStClacDlg::OnBnClickedButtonThree() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '3');
}


void CStClacDlg::OnBnClickedButtonFour() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '4');
}


void CStClacDlg::OnBnClickedButtonFive() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '5');
}


void CStClacDlg::OnBnClickedButtonSix() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '6');
}


void CStClacDlg::OnBnClickedButtonSeven() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '7');
}


void CStClacDlg::OnBnClickedButtonEight() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '8');
}


void CStClacDlg::OnBnClickedButtonNine() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '9');
}


void CStClacDlg::OnBnClickedButtonZero() {
	// TODO: 在此添加控件通知处理程序代码
	Handle(g_Input, '0');
}


void CStClacDlg::OnBnClickedButtonPoint() {
	// TODO: 在此添加控件通知处理程序代码
	if (g_input.Find('.') != -1)
		return;
	if (calculator.m_isDot)
		return;
	if (calculator.m_isEnd) {
		calculator.m_isEnd = false;
		g_input += ".";
		g_Input.SetWindowText(g_input);
		calculator.m_isDot = true;
		return;
	}
	g_input += ".";
	g_Input.SetWindowText(g_input);
	calculator.m_isDot = true;
}


void CStClacDlg::OnBnClickedButtonPositiveornegative() {
	// TODO: 在此添加控件通知处理程序代码
	if (g_input[0] == '-') {
		//删除负号
		g_input = g_input.Right(g_input.GetLength() - 1);
		g_Input.SetWindowText(g_input);
	}
	else {
		g_input = L"-" + g_input;
		g_Input.SetWindowText(g_input);
	}
}

void HandleOperator(CStatic& exp, char c) {
	if (calculator.m_isOperator) {
		//删除操作符
		g_expression = g_expression.Left(g_expression.GetLength() - 1);
		calculator.DeleteOperator();
		calculator.CollectOperators(c);
		g_expression += c;
		exp.SetWindowText(g_expression);
		return;
	}
	calculator.CollectOperands(_wtof(g_input));
	calculator.CollectOperators(c);
	g_expression += g_input;
	g_expression += c;
	exp.SetWindowText(g_expression);
	calculator.m_isEnd = true;
	calculator.m_isDot = false;
	calculator.m_isOperator = true;

}


void CStClacDlg::OnBnClickedButtonAdd() {
	// TODO: 在此添加控件通知处理程序代码
	HandleOperator(g_Expression, '+');
}


void CStClacDlg::OnBnClickedButtonSubtract() {
	// TODO: 在此添加控件通知处理程序代码
	HandleOperator(g_Expression, '-');
}


void CStClacDlg::OnBnClickedButtonMultiply() {
	// TODO: 在此添加控件通知处理程序代码
	HandleOperator(g_Expression, '*');
}


void CStClacDlg::OnBnClickedButtonDivide() {
	// TODO: 在此添加控件通知处理程序代码
	HandleOperator(g_Expression, '/');
}




void CStClacDlg::m_showExpRes() {
	g_Expression.SetWindowText(g_expression);
	g_Input.SetWindowText(g_input);
}

void CStClacDlg::updateHistory() {
	m_HisDlg.m_HisListCtrl.DeleteAllItems();
	stack<CCalculatorInfo> temp(g_history);
	int i = 0;
	while (!temp.empty()) {
		CCalculatorInfo info = temp.top();
		temp.pop();
		CString g_expression = L"";
		int j = 0;
		for (; j < info.m_operator.size(); j++) {
			CString temp;
			temp.Format(_T("%f"), info.m_operands[j]);
			g_expression += temp;
			g_expression += info.m_operator[j];
		}

		CString temp;
		temp.Format(_T("%f"), info.m_operands[j]);
		g_expression += temp;
		g_expression += L"=";
		temp.Format(_T("%f"), info.m_result);
		g_expression += temp;

		// 获取新插入项的文本宽度
		CClientDC dc(&m_HisDlg.m_HisListCtrl);
		CFont* pOldFont = dc.SelectObject(m_HisDlg.m_HisListCtrl.GetFont());
		CSize size = dc.GetTextExtent(g_expression);
		dc.SelectObject(pOldFont);
		//插入数据
		m_HisDlg.m_HisListCtrl.InsertItem(i, g_expression);
		int currentWidth = m_HisDlg.m_HisListCtrl.GetColumnWidth(0);
		int newWidth = max(currentWidth, size.cx + 10); // 添加一些额外的宽度以防止截断
		m_HisDlg.m_HisListCtrl.SetColumnWidth(0, newWidth);
		i++;
	}
}

void CStClacDlg::updateMemory() {
	m_MemDlg.m_MemListCtrl.DeleteAllItems();
	stack<double> temp(g_memory);
	int i = 0;
	while (!temp.empty()) {
		double info = temp.top();
		temp.pop();
		CString input = L"";
		input.Format(L"%f", info);

		// 获取新插入项的文本宽度
		CClientDC dc(&m_MemDlg.m_MemListCtrl);
		CFont* pOldFont = dc.SelectObject(m_MemDlg.m_MemListCtrl.GetFont());
		CSize size = dc.GetTextExtent(input);
		dc.SelectObject(pOldFont);
		//插入数据
		m_MemDlg.m_MemListCtrl.InsertItem(i, input);
		int currentWidth = m_MemDlg.m_MemListCtrl.GetColumnWidth(0);
		int newWidth = max(currentWidth, size.cx + 10); // 添加一些额外的宽度以防止截断
		m_MemDlg.m_MemListCtrl.SetColumnWidth(0, newWidth);
		i++;
	}
}
void CStClacDlg::OnBnClickedButtonEqual() {
	g_hWnd = this->m_hWnd;
	// TODO: 在此添加控件通知处理程序代码
	calculator.CollectOperands(_wtof(g_input));
	calculator.CalculateExpression();
	g_expression += g_input;
	//将calculator.m_calculatorInfo.m_result转换为CString类型
	g_input = L"";
	g_input.Format(L"%f", calculator.m_calculatorInfo.m_result);
	g_Expression.SetWindowText(L"");
	g_Input.SetWindowText(g_input);
	g_history.push(calculator.m_calculatorInfo);
	updateHistory();
	calculator.m_isEnd = true;
	calculator.m_isDot = false;
	g_expression = L"";
	//清空vector
	calculator.m_calculatorInfo.m_operands.clear();
	calculator.m_calculatorInfo.m_operator.clear();

}


void CStClacDlg::OnBnClickedButtonSquare() {
	// TODO: 在此添加控件通知处理程序代码
	//计算平方
	double input = _wtof(g_input) * _wtof(g_input);
	g_input = L"";
	g_input.Format(L"%f", input);
	g_Input.SetWindowText(g_input);
}


void CStClacDlg::OnBnClickedButtonBackspace() {
	// TODO: 在此添加控件通知处理程序代码
	if (calculator.m_isEnd)
		return;
	if (g_input.GetLength() == 1) {
		g_input = L"0";
		g_Input.SetWindowText(g_input);
		return;
	}
	g_input = g_input.Left(g_input.GetLength() - 1);
	g_Input.SetWindowText(g_input);
}


void CStClacDlg::OnBnClickedButtonCe() {
	// TODO: 在此添加控件通知处理程序代码
	g_input = L"0";
	g_Input.SetWindowText(g_input);
	calculator.m_isEnd = true;
	calculator.m_isDot = false;
	calculator.m_isOperator = false;

}


void CStClacDlg::OnBnClickedButtonC() {
	// TODO: 在此添加控件通知处理程序代码
	g_input = L"0";
	g_expression = L"";
	g_Input.SetWindowText(g_input);
	g_Expression.SetWindowText(g_expression);
	calculator.m_isEnd = true;
	calculator.m_isDot = false;
	calculator.m_isOperator = false;
	//清空vector
	calculator.m_calculatorInfo.m_operands.clear();
	calculator.m_calculatorInfo.m_operator.clear();
}


void CStClacDlg::OnBnClickedButtonPrescriptiopn() {
	// TODO: 在此添加控件通知处理程序代码
	//计算开方
	double input = sqrt(_wtof(g_input));
	g_input = L"";
	g_input.Format(L"%f", input);
	g_Input.SetWindowText(g_input);
}


void CStClacDlg::OnBnClickedButtonCountdown() {
	// TODO: 在此添加控件通知处理程序代码
	//计算倒数
	double input = 1 / _wtof(g_input);
	g_input = L"";
	g_input.Format(L"%f", input);
	g_Input.SetWindowText(g_input);
}


void CStClacDlg::OnBnClickedButtonMs() {
	// TODO: 在此添加控件通知处理程序代码
	//存入记忆
	//将g_input转换为double类型
	g_memory.push(_wtof(g_input));
	updateMemory();
	calculator.m_isEnd = true;
}


void CStClacDlg::OnBnClickedButtonMc() {
	// TODO: 在此添加控件通知处理程序代码
	//清空记忆
	while (!g_memory.empty()) {
		g_memory.pop();
	}
	updateMemory();
}


void CStClacDlg::OnBnClickedButtonMr() {
	// TODO: 在此添加控件通知处理程序代码
	//读取记忆
	if (g_memory.empty())
		return;
	g_input = L"";
	g_input.Format(L"%f", g_memory.top());
	g_Input.SetWindowText(g_input);
}


void CStClacDlg::OnBnClickedButtonMAdd() {
	// TODO: 在此添加控件通知处理程序代码
	if (g_memory.empty()) {
		g_memory.push(_wtof(g_input));
		calculator.m_isEnd = true;
		return;
	}
	double add = g_memory.top();
	g_memory.pop();
	g_memory.push(add + _wtof(g_input));
}


void CStClacDlg::OnBnClickedButtonMSub() {
	// TODO: 在此添加控件通知处理程序代码
	if (g_memory.empty()) {
		g_memory.push(_wtof(g_input));
		calculator.m_isEnd = true;
		return;
	}
	double sub = g_memory.top();
	g_memory.pop();
	g_memory.push(sub - _wtof(g_input));
}


void CStClacDlg::OnBnClickedButtonPer() {
	// TODO: 在此添加控件通知处理程序代码
	//计算百分数
	double input;
	if (calculator.m_calculatorInfo.m_operands.empty()) {
		input = 0;
	}
	else {
		input = calculator.m_calculatorInfo.m_operands[calculator.m_calculatorInfo.m_operands.size() - 1];
	}
	input = input * (_wtof(g_input) / 100);
	g_input = L"";
	g_input.Format(L"%f", input);
	g_Input.SetWindowText(g_input);

}
