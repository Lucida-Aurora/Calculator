
// CalculatorDlg.h: 头文件
//

#pragma once
#include "CStClacDlg.h"
#include "CPrCalcDlg.h"


// CCalculatorDlg 对话框
class CCalculatorDlg : public CDialogEx
{
// 构造
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CTabCtrl m_TabCtrlCalc;
	CStClacDlg m_StCalcDlg;
	CPrCalcDlg m_PrCalcDlg;
	int m_nCurSelTab;
	CDialogEx* m_pDialog[2];
public:
	afx_msg void OnTcnSelchangeTabCalc(NMHDR* pNMHDR, LRESULT* pResult);
};
