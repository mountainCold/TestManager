// CDlgB.cpp: 实现文件
//

#include "pch.h"
#include "TaskManager.h"
#include "CDlgB.h"
#include "afxdialogex.h"
#include <vector>
#include <TlHelp32.h>
#include "Methon.h"


// CDlgB 对话框

IMPLEMENT_DYNAMIC(CDlgB, CDialogEx)

CDlgB::CDlgB(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CDlgB::~CDlgB()
{
}

void CDlgB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ModulList);
}


BEGIN_MESSAGE_MAP(CDlgB, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CDlgB 消息处理程序


BOOL CDlgB::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ModulList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ModulList.InsertColumn(0, L"模块名", 0, 160);
	m_ModulList.InsertColumn(1, L"加载基址", 0, 120);
	m_ModulList.InsertColumn(2, L"大小", 0, 120);
	m_ModulList.InsertColumn(3, L"路径", 0, 480);
	std::vector<MODULEENTRY32> moduleList;
	EnumProcessModul(m_pid, &moduleList);
	// 插入到列表控件
	int index = 0;
	CString buffer;
	for (auto& i : moduleList) {
		m_ModulList.InsertItem(index, i.szModule);

		buffer.Format(L"%08X", i.modBaseAddr);
		m_ModulList.SetItemText(index, 1, buffer);

		buffer.Format(L"%08X", i.modBaseSize);
		m_ModulList.SetItemText(index, 2, buffer);

		m_ModulList.SetItemText(index, 3, i.szExePath);
		++index;
	}
	SetWindowText(m_title);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgB::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_ModulList.m_hWnd)
	{
		m_ModulList.MoveWindow(0, 0, cx, cy);
	}
	
}

void CDlgB::setProcessId(DWORD dwPid)
{
	m_pid = dwPid;
}

void CDlgB::setTitle(const CString& title)
{
	m_title = title;
}
