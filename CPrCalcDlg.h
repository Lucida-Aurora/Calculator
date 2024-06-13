#pragma once
#include "afxdialogex.h"
#include "CPrAllKBDlg.h"
#include "CPrBitKBDlg.h"



// CPrCalcDlg 对话框

class CPrCalcDlg : public CDialogEx {
	DECLARE_DYNAMIC(CPrCalcDlg)

public:
	CPrCalcDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPrCalcDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PR_CALC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_KBTabCtrl;

	CPrAllKBDlg m_allKBDlg;
	CPrBitKBDlg m_bitKBDlg;
	int m_nCurSelTab;
	CDialogEx* m_pDialog[2];
	afx_msg void OnTcnSelchangeTabKb(NMHDR* pNMHDR, LRESULT* pResult);

	void UpdateMem();

	afx_msg void OnBnClickedButtonClear();
	CListCtrl m_MemListCtrl;
};
