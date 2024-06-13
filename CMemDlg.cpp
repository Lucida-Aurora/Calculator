// CMemDlg.cpp: 实现文件
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "CMemDlg.h"
#include <stack>
#include <vector>
using namespace std;

extern stack<double> g_memory;
extern CString g_expression;
extern CString g_input;

extern CStatic g_Expression;
extern CStatic g_Input;
// CMemDlg 对话框

IMPLEMENT_DYNAMIC(CMemDlg, CDialogEx)

CMemDlg::CMemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MEMORY, pParent) {

}

CMemDlg::~CMemDlg() {
}

void CMemDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEM, m_MemListCtrl);
}

BOOL CMemDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	m_MemListCtrl.InsertColumn(0, _T("内存历史记录"), LVCFMT_CENTER, 227);
	return 0;
}


BEGIN_MESSAGE_MAP(CMemDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MEM, &CMemDlg::OnNMClickListCtrl)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CMemDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CHisDlg 消息处理程序
void CMemDlg::OnNMClickListCtrl(NMHDR* pNMHDR, LRESULT* pResult) {
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int nItem = pNMItemActivate->iItem;

	if (nItem != -1) {
		vector<double> temp;
		stack<double> tempStack(g_memory);
		while (!tempStack.empty()) {
			temp.push_back(tempStack.top());
			tempStack.pop();
		}
		double info = temp[nItem];

		CString expression = L"";
		g_input = L"";

		g_input.Format(L"%f", info);
		g_Expression.SetWindowText(g_expression);
		g_Input.SetWindowText(g_input);

	}

	*pResult = 0;
}

// CMemDlg 消息处理程序


void CMemDlg::OnBnClickedButtonClear() {
	// TODO: 在此添加控件通知处理程序代码
	if (g_memory.empty()) {
		return;
	}
	g_memory = stack<double>();
	m_MemListCtrl.DeleteAllItems();
}
