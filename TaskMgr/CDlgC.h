﻿#pragma once
// CDlgC 对话框
#include <afxdialogex.h>
#include "resource.h"
class CDlgC : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgC)

public:
	CDlgC(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgC();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
