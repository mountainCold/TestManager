// CMyTab.cpp: 实现文件
//

#include "pch.h"
#include "TaskManager.h"
#include "CMyTab.h"
#include "Methon.h"


// CMyTab

IMPLEMENT_DYNAMIC(CMyTab, CTabCtrl)

CMyTab::CMyTab()
{

}

CMyTab::~CMyTab()
{
}


BEGIN_MESSAGE_MAP(CMyTab, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CMyTab::OnTcnSelchange)
END_MESSAGE_MAP()



// CMyTab 消息处理程序

void CMyTab::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	InsertItem(0,L"进程");
	//InsertItem(1,L"模块");
	InsertItem(1,L"堆");
	InsertItem(2,L"窗口");
	InsertItem(3,L"文件");
	CTabCtrl::PreSubclassWindow();
}

void CMyTab::InsertTabWnd(int count, ...)
{
	va_list VaList = nullptr;
	va_start(VaList, count);

	for (int i = 0; i < count; ++i)
	{
		// 获取到窗口对象指针和窗口的ID
		CDialogEx* Dialog = va_arg(VaList, CDialogEx*);
		int id = va_arg(VaList, int);

		// 创建窗口并添加到容器中
		Dialog->Create(id, this);
		m_WndVec.push_back(Dialog);
	}

	// 应该以选项卡为父窗口计算出新的位置并且移动所有的窗口
		// 以选项卡为准，重新设置窗口的位置
	CRect Rect = { };
	this->GetClientRect(&Rect);
	Rect.DeflateRect(0, 23, 0,0);
	for (int i = 0; i < m_WndVec.size(); ++i)
		m_WndVec[i]->MoveWindow(&Rect);

	va_end(VaList);

	ShowTabWnd(0);
}


void CMyTab::ShowTabWnd(int index)
{
	for (int i = 0; i < m_WndVec.size(); ++i)
	{
		m_WndVec[i]->ShowWindow(i == index ? SW_SHOWNORMAL : SW_HIDE);
		if (i ==2)
		{
			m_WndVec[i]->SendMessage(WM_UPDATEUISTATE);
		}
	}
}

void CMyTab::OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult)
{	
	ShowTabWnd(this->GetCurSel());
}

