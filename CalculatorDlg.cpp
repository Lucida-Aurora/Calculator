
// CalculatorDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculatorDlg 对话框



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CALC, m_TabCtrlCalc);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CALC, &CCalculatorDlg::OnTcnSelchangeTabCalc)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_TabCtrlCalc.InsertItem(0, _T("标准计算器"));
	m_TabCtrlCalc.InsertItem(1, _T("程序员计算器"));
	m_StCalcDlg.Create(IDD_DIALOG_ST_CALC, &m_TabCtrlCalc);
	m_PrCalcDlg.Create(IDD_DIALOG_PR_CALC, &m_TabCtrlCalc);
	CRect rect;
	m_TabCtrlCalc.GetClientRect(&rect);
	rect.top += 20;

	m_StCalcDlg.MoveWindow(&rect);
	m_PrCalcDlg.MoveWindow(&rect);

	m_pDialog[0] = &m_StCalcDlg;
	m_pDialog[1] = &m_PrCalcDlg;
	m_StCalcDlg.ShowWindow(SW_SHOW);
	m_PrCalcDlg.ShowWindow(SW_HIDE);
	m_nCurSelTab = 0;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint() {
	if (IsIconic()) {
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnTcnSelchangeTabCalc(NMHDR* pNMHDR, LRESULT* pResult) {
	// TODO: 在此添加控件通知处理程序代码
	m_pDialog[m_nCurSelTab]->ShowWindow(SW_HIDE);
	m_nCurSelTab = m_TabCtrlCalc.GetCurSel();
	m_pDialog[m_nCurSelTab]->ShowWindow(SW_SHOW);
	m_PrCalcDlg.UpdateMem();
	m_StCalcDlg.updateMemory();
	*pResult = 0;
}
