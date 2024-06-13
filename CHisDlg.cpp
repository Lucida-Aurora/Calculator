// CHisDlg.cpp: 实现文件
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "CHisDlg.h"
#include <stack>
using namespace std;

extern stack<CCalculatorInfo> g_history;
extern CString g_expression;
extern CString g_input;

extern CStatic g_Expression;
extern CStatic g_Input;
extern HWND g_hWnd;

// CHisDlg 对话框

IMPLEMENT_DYNAMIC(CHisDlg, CDialogEx)

CHisDlg::CHisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HISTORY, pParent) {

}

CHisDlg::~CHisDlg() {
}

void CHisDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HIS, m_HisListCtrl);

}

BOOL CHisDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_HisListCtrl.InsertColumn(0, _T("运算历史记录"), LVCFMT_CENTER, 227);

	return TRUE;
}



BEGIN_MESSAGE_MAP(CHisDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CHisDlg::OnBnClickedButtonClear)
	ON_NOTIFY(NM_CLICK, IDC_LIST_HIS, &CHisDlg::OnNMClickListCtrl)
END_MESSAGE_MAP()


// CHisDlg 消息处理程序
void CHisDlg::OnNMClickListCtrl(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = pNMItemActivate->iItem;

	if (nItem != -1) {
		vector<CCalculatorInfo> temp;
		stack<CCalculatorInfo> tempStack(g_history);
		while (!tempStack.empty()) {
			temp.push_back(tempStack.top());
			tempStack.pop();
		}
		CCalculatorInfo info = temp[nItem];

		CString expression = L"";
		int j = 0;
		for (; j < info.m_operator.size(); j++) {
			CString temp;
			temp.Format(_T("%f"), info.m_operands[j]);
			expression += temp;
			expression += info.m_operator[j];
		}
		CString tempStr;
		tempStr.Format(_T("%f"), info.m_operands[j]);
		//expression += tempStr;
		g_expression = expression;
		//tempStr.Format(_T("%f"), info.m_result);
		g_input = tempStr;
		g_Expression.SetWindowText(g_expression);
		g_Input.SetWindowText(g_input);
		CCalculatorInfo* p = new CCalculatorInfo;
		p->m_operands = info.m_operands;
		p->m_operator = info.m_operator;
		p->m_result = info.m_result;
		//发送消息
		::SendMessage(g_hWnd, WM_LIST_TO_CUR, (WPARAM)p, 0);
	}

	*pResult = 0;
}

void CHisDlg::OnBnClickedButtonClear() {
	// TODO: 在此添加控件通知处理程序代码
	if (g_history.empty()) {
		return;
	}
	g_history = stack<CCalculatorInfo>();
	m_HisListCtrl.DeleteAllItems();

}
