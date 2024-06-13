#pragma once
#include "afxdialogex.h"
#include "Calculator.h"
#include <stack>
#include "CStandardCalculator.h"
#define WM_LIST_TO_CUR (WM_USER + 101)
using namespace std;

// CHisDlg 对话框



class CHisDlg : public CDialogEx {
	DECLARE_DYNAMIC(CHisDlg)

public:
	CHisDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHisDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HISTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_HisListCtrl;
	afx_msg void OnNMClickListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	void OnBnClickedButtonClear();
};
