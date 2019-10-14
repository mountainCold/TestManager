#pragma once


// CDlgB 对话框

class CDlgB : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgB)

public:
	CDlgB(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgB();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ModulList;
	DWORD m_pid;
	CString m_title;

	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void setProcessId(DWORD dwPid);
	void setTitle(const CString& title);
};
