#pragma once

// CDlgA 对话框
#include "Methon.h"
#include "CDlgB.h"
#include "CTreadDlg.h"
class CDlgA : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgA)

public:
	CDlgA(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgA();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CMenu m_menu;
	CDlgB m_cDlgB;
	CTreadDlg m_thDlg;
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ProcessList;
	std::vector<PROCESSINFO> m_OldList;
	virtual BOOL OnInitDialog();
	void UpdateProcessList();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnIdrMenu2();
	afx_msg void OnEnumThread();
	afx_msg void OnEnumModule();
};
