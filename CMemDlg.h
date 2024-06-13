#pragma once
#include "afxdialogex.h"


// CMemDlg 对话框

class CMemDlg : public CDialogEx {
	DECLARE_DYNAMIC(CMemDlg)

public:
	CMemDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMemDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MEMORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_MemListCtrl;
	afx_msg void OnNMClickListCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	void OnBnClickedButtonClear();
};
