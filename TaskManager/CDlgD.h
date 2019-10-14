#pragma once


// CDlgD 对话框
#include <vector>
class CDlgD : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgD)

public:
	CDlgD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgD();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CTreeCtrl m_WinTree;
	std::vector<DWORD> vOldHwnd;
	virtual BOOL OnInitDialog();

	void UpdataWindow();
	

	afx_msg void OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
protected:
public:
	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
};
