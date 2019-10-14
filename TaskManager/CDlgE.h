#pragma once


// CDlgE 对话框
class CDlgE : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgE)

public:
	CDlgE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_FileTree;
	CListCtrl m_FileList;
	CString m_curPath;
	CMenu m_menu;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL CDlgE::EnumFile(CString path);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuClick();
};
