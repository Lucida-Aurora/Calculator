// CPrCalcDlg.cpp: 实现文件
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "CPrCalcDlg.h"
#include <stack>
#include <vector>
using namespace std;

extern stack<double> g_memory;
// CPrCalcDlg 对话框

IMPLEMENT_DYNAMIC(CPrCalcDlg, CDialogEx)

CPrCalcDlg::CPrCalcDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PR_CALC, pParent) {

}

BOOL CPrCalcDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	m_MemListCtrl.InsertColumn(0, _T("内存历史记录"), LVCFMT_CENTER, 227);
	m_KBTabCtrl.InsertItem(0, _T("全键盘"));
	m_KBTabCtrl.InsertItem(1, _T("位键盘"));
	m_allKBDlg.Create(IDD_DIALOG_PR_ALLKB, this);
	m_bitKBDlg.Create(IDD_DIALOG_PR_BITKB, this);
	CRect rect;
	m_KBTabCtrl.GetClientRect(&rect);
	rect.top += 335;
	rect.bottom += 312;
	rect.left += 13;
	rect.right += 8;
	m_allKBDlg.MoveWindow(&rect);
	m_bitKBDlg.MoveWindow(&rect);
	m_pDialog[0] = &m_allKBDlg;
	m_pDialog[1] = &m_bitKBDlg;
	m_allKBDlg.ShowWindow(SW_SHOW);
	m_bitKBDlg.ShowWindow(SW_HIDE);
	m_nCurSelTab = 0;

	UpdateMem();


	return TRUE;
}

CPrCalcDlg::~CPrCalcDlg() {
}

void CPrCalcDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_KB, m_KBTabCtrl);

	DDX_Control(pDX, IDC_LIST_PR_MEM, m_MemListCtrl);
}


BEGIN_MESSAGE_MAP(CPrCalcDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_KB, &CPrCalcDlg::OnTcnSelchangeTabKb)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CPrCalcDlg::OnBnClickedButtonClear)
END_MESSAGE_MAP()


// CPrCalcDlg 消息处理程序


void CPrCalcDlg::OnTcnSelchangeTabKb(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: 在此添加控件通知处理程序代码
	m_pDialog[m_nCurSelTab]->ShowWindow(SW_HIDE);
	m_nCurSelTab = m_KBTabCtrl.GetCurSel();
	m_pDialog[m_nCurSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
}

void CPrCalcDlg::UpdateMem() {
	m_MemListCtrl.DeleteAllItems();
	vector<unsigned int> temp;
	stack<double> tempStack(g_memory);
	while (!tempStack.empty()) {
		temp.push_back((unsigned)tempStack.top());
		tempStack.pop();
	}
	for (int i = 0; i < temp.size(); i++) {
		CString str;
		str.Format(L"%d", temp[i]);
		m_MemListCtrl.InsertItem(i, str);
	}
}



void CPrCalcDlg::OnBnClickedButtonClear() {
	// TODO: 在此添加控件通知处理程序代码
	if (g_memory.empty()) {
		return;
	}
	g_memory = stack<double>();
	m_MemListCtrl.DeleteAllItems();
}
