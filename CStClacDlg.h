#pragma once
#include "afxdialogex.h"
#include "CMemDlg.h"
#include "CHisDlg.h"
#define WM_LIST_TO_CUR (WM_USER + 101)

// CStClacDlg 对话框

class CStClacDlg : public CDialogEx {
	DECLARE_DYNAMIC(CStClacDlg)

public:
	CStClacDlg(CWnd* pParent = nullptr);  // 标准构造函数
	virtual ~CStClacDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ST_CALC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnListToCur(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_HisTabCtrl;
	int m_nCurSelTab;
	CHisDlg m_HisDlg;
	CMemDlg m_MemDlg;
	CDialogEx* m_pDialog[2];
	static void m_showExpRes();
	void updateHistory();
	void updateMemory();
	afx_msg void OnTcnSelchangeTabHis(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonOne();
	afx_msg void OnBnClickedButtonTwo();
	afx_msg void OnBnClickedButtonThree();
	afx_msg void OnBnClickedButtonFour();
	afx_msg void OnBnClickedButtonFive();
	afx_msg void OnBnClickedButtonSix();
	afx_msg void OnBnClickedButtonSeven();
	afx_msg void OnBnClickedButtonEight();
	afx_msg void OnBnClickedButtonNine();
	afx_msg void OnBnClickedButtonZero();
	afx_msg void OnBnClickedButtonPoint();
	afx_msg void OnBnClickedButtonPositiveornegative();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSubtract();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonDivide();

	void OnBnClickedButtonEqual();
	afx_msg void OnBnClickedButtonSquare();

	afx_msg void OnBnClickedButtonBackspace();
	afx_msg void OnBnClickedButtonCe();
	afx_msg void OnBnClickedButtonC();
	afx_msg void OnBnClickedButtonPrescriptiopn();
	afx_msg void OnBnClickedButtonCountdown();
	afx_msg void OnBnClickedButtonMs();
	afx_msg void OnBnClickedButtonMc();
	afx_msg void OnBnClickedButtonMr();
	afx_msg void OnBnClickedButtonMAdd();
	afx_msg void OnBnClickedButtonMSub();

	afx_msg void OnBnClickedButtonPer();
};
