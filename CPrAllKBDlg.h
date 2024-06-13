#pragma once
#include "afxdialogex.h"


// CPrAllKBDlg 对话框

class CPrAllKBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPrAllKBDlg)

public:
	CPrAllKBDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPrAllKBDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PR_ALLKB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
