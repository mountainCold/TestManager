// CTreadDlg.cpp: 实现文件
//

#include "pch.h"
#include "TaskManager.h"
#include "CTreadDlg.h"
#include "afxdialogex.h"
#include "Methon.h"


// CTreadDlg 对话框

IMPLEMENT_DYNAMIC(CTreadDlg, CDialogEx)

CTreadDlg::CTreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{

}

CTreadDlg::~CTreadDlg()
{
}

void CTreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ThreadList);
}


BEGIN_MESSAGE_MAP(CTreadDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTreadDlg 消息处理程序


BOOL CTreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ThreadList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	ThreadList.InsertColumn(0, L"线程ID", 0, 120);
	ThreadList.InsertColumn(1, L"线程大小", 0, 120);
	ThreadList.InsertColumn(2, L"线程优先级", 0, 120);
	std::vector<THREADENTRY32> threadList;
	EnumThreadForProcess(m_pid, &threadList);
	// 插入到列表控件
	int index = 0;
	CString buffer;
	for (auto& i : threadList) {

		buffer.Format(L"%08X", i.th32ThreadID);
		ThreadList.SetItemText(index, 0, buffer);

		buffer.Format(L"%08X", i.dwSize);
		ThreadList.SetItemText(index, 1, buffer);

		buffer.Format(L"%08X", i.tpBasePri);
		ThreadList.SetItemText(index, 2, buffer);
		++index;
	}
	SetWindowText(m_title);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CTreadDlg::setMessage(DWORD pid, const CString& title)
{
	m_pid = pid;
	m_title = title;
}


void CTreadDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (ThreadList.m_hWnd)
	{
		ThreadList.MoveWindow(0, 0, cx, cy);
	}
}
