// CMyTab.cpp: 实现文件
//
#include "CMyTab.h"


// CMyTab

IMPLEMENT_DYNAMIC(CMyTab, CTabCtrl)

CMyTab::CMyTab()
{
	m_dlgA.Create(IDD_DIALOG2, this);
	m_dlgB.Create(IDD_DIALOG2, this);
	m_dlgC.Create(IDD_DIALOG2, this);
}

CMyTab::~CMyTab()
{
}

BEGIN_MESSAGE_MAP(CMyTab, CTabCtrl)
END_MESSAGE_MAP()

// CMyTab 消息处理程序

void CMyTab::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	InsertItem(0, L"窗口");
	InsertItem(1, L"进程");
	InsertItem(2, L"线程");
// 	InsertItem(3, L"模块");
// 	InsertItem(4, L"文件");
	CTabCtrl::PreSubclassWindow();
}
