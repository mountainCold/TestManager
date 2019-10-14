// CDlgD.cpp: 实现文件
//

#include "pch.h"
#include "TaskManager.h"
#include "CDlgD.h"
#include "afxdialogex.h"
#include <vector>
#include "Methon.h"


// CDlgD 对话框

IMPLEMENT_DYNAMIC(CDlgD, CDialogEx)

CDlgD::CDlgD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

CDlgD::~CDlgD()
{
}

void CDlgD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_WinTree);
}


BEGIN_MESSAGE_MAP(CDlgD, CDialogEx)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CDlgD::OnClickTree1)
	ON_WM_TIMER()
	ON_WM_UPDATEUISTATE()
END_MESSAGE_MAP()


// CDlgD 消息处理程序


void CDlgD::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (m_WinTree.m_hWnd)
	{
		m_WinTree.SetWindowPos(0, 0, 0, cx, cy, SWP_NOZORDER);
	}
}


BOOL CDlgD::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdataWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDlgD::UpdataWindow()
{
	m_WinTree.DeleteAllItems();
	std::vector<DWORD> vHwnd;
	EnumWindows(EnumWindowProcM, (LPARAM)& vHwnd);
	//EnumChildWindows(hFindWnd, EnumProc, NULL)
	for (int i = 0; i < vHwnd.size(); ++i)
	{
		HWND hWnd = (HWND)vHwnd[i];
		TCHAR buff[300];
		TCHAR buff1[200];
		TCHAR buff2[200];
		::GetClassName(hWnd, buff2, 200);
		::GetWindowText(hWnd, buff1, 200);
		_stprintf_s(buff, 300, L"%s %08x \"%s\" %s", L"窗口", (int)hWnd, buff1, buff2);
		HTREEITEM hItem = m_WinTree.InsertItem(buff);
		m_WinTree.SetItemData(hItem, (DWORD_PTR)hWnd);
	}
	vOldHwnd.swap(vHwnd);
	
}


void CDlgD::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult)
{

	CPoint pos;
	GetCursorPos(&pos);
	m_WinTree.ScreenToClient(&pos);
	HTREEITEM hItem = m_WinTree.HitTest(pos);
	HTREEITEM hChild = m_WinTree.GetNextItem(hItem, TVGN_CHILD);
	if (hChild != NULL) return;
	HWND hwnd2 =(HWND)m_WinTree.GetItemData(hItem);
	std::vector<DWORD> vHwnd;
	EnumChildWindows(hwnd2, EnumWindowProcM, (LPARAM)&vHwnd);
	for (int i=0;i<vHwnd.size();++i)
	{
		HWND hWnd = (HWND)vHwnd[i];
		TCHAR buff[300];
		TCHAR buff1[200];
		::GetWindowText(hWnd, buff1, 200);
		_stprintf_s(buff, 300, L"%s %d %s", L"窗口", (int)hWnd, buff1);
		HTREEITEM hItem2 = m_WinTree.InsertItem(buff,hItem);
		m_WinTree.SetItemData(hItem2, (DWORD_PTR)hWnd);
	}
	vOldHwnd.swap(vHwnd);
}


void CDlgD::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
}



void CDlgD::OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/)
{
	UpdataWindow();
}
