#pragma once


// CTreadDlg 对话框

class CTreadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTreadDlg)

public:
	CTreadDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTreadDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DWORD m_pid;
	CString m_title;
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ThreadList;
	virtual BOOL OnInitDialog();
	void setMessage(DWORD pid, const CString& title);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
