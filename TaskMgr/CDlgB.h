#pragma once
// CDlgB 对话框
#include <afxdialogex.h>
#include "resource.h"
class CDlgB : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgB)

public:
	CDlgB(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgB();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
