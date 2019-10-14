// CDlgA.cpp: 实现文件
//

#include "pch.h"
#include "TaskManager.h"
#include "CDlgA.h"
#include "afxdialogex.h"



// CDlgA 对话框
CRITICAL_SECTION g_critical_section;
IMPLEMENT_DYNAMIC(CDlgA, CDialogEx)

CDlgA::CDlgA(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	InitializeCriticalSection(&g_critical_section);
}

CDlgA::~CDlgA()
{
}

void CDlgA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, ProcessList);
}



BEGIN_MESSAGE_MAP(CDlgA, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CDlgA::OnRclickList2)
	ON_COMMAND(ID_KILLPROCESS, &CDlgA::OnIdrMenu2)
	ON_COMMAND(ID_32783, &CDlgA::OnEnumThread)
	ON_COMMAND(ID_32784, &CDlgA::OnEnumModule)
END_MESSAGE_MAP()


// CDlgA 消息处理程序

int IndexOfProcessList(std::vector<PROCESSINFO>& proclist, DWORD pid)
{
	DWORD size = proclist.size();
	for (int i = 0; i < size; ++i) {
		if (proclist[i].th32ProcessID == pid) {
			return i;
		}
	}
	return -1;
}
BOOL CDlgA::OnInitDialog()
{
	CDialogEx::OnInitDialog();	
	m_menu.LoadMenu(IDR_MENU2);
	ProcessList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	const TCHAR* title[] = { L"进程",L"PID",L"CPU" ,L"内存使用率" };

	int index = 0;
	for (auto&i:title)
	{
		ProcessList.InsertColumn(index++, i, 0, 120);
	}
	UpdateProcessList();
	SetTimer(0, 1000, NULL);//定时器id 时间间隔 回调函数NULL 会发送WM_TIMER消息
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void CDlgA::UpdateProcessList()
{
	std::vector<PROCESSINFO> newList;
	if (!EnumProcess(&newList))
	{
		return;
	}
	EnterCriticalSection(&g_critical_section);
	if (m_OldList.size()==0)
	{
		int index = 0;
		CString Buffer;
		for (auto&i:newList)
		{

			ProcessList.InsertItem(index, L"");
			Buffer.Format(L"%d", i.th32ProcessID);
			ProcessList.SetItemText(index, 0, i.szExeFile);
			ProcessList.SetItemText(index, 1, Buffer);
			ProcessList.SetItemText(index, 2, L"");
			Buffer.Format(_T("%12dKb"), (double)i.dwMemoryUsage);
			ProcessList.SetItemText(index, 3, Buffer);
			++index;
		}
		m_OldList.swap(newList);
	}
	else
	{
		//遍历删除已经结束的进程
		int index = 0;
		for (auto itr =m_OldList.begin();itr!=m_OldList.end();)
		{
			if (-1 ==IndexOfProcessList(newList,itr->th32ProcessID) )
			{
				itr = m_OldList.erase(itr);
				ProcessList.DeleteItem(index);
				continue;
			}
			// 刷新内存使用率
			CString buffer;
			DWORD memUsage = getProcessMemoryUsage(itr->th32ProcessID);
			if (itr->dwMemoryUsage != memUsage)
			{
				buffer.Format(_T("%12dKb"), memUsage);
				ProcessList.SetItemText(index, 3, buffer);
				itr->dwMemoryUsage = memUsage;
			}

			// 刷新CPU使用率
			double cpuUsage = getProcessCpuUsage(itr->th32ProcessID);

			if (abs(itr->dCpuUsage - cpuUsage) >= 0.001)
			{
				buffer.Format(_T("%.1lf%%"), cpuUsage);
				ProcessList.SetItemText(index, 2, buffer);
				itr->dCpuUsage = cpuUsage;
			}
			++index;
			++itr;
		}
		//增加新启动的进程
		for (auto&i:newList)
		{
			if (-1==IndexOfProcessList(m_OldList,i.th32ProcessID))
			{
				m_OldList.push_back(i);
				CString buffer;
				ProcessList.InsertItem(index, L"");
				buffer.Format(_T("%d"), i.th32ProcessID);
				ProcessList.SetItemText(index, 0, i.szExeFile);
				ProcessList.SetItemText(index, 1, buffer);
				ProcessList.SetItemText(index, 2, L"");
				buffer.Format(_T("%12dKb"), (double)i.dwMemoryUsage);
				ProcessList.SetItemText(index, 3, buffer);
			}
		}
	}
	// 离开临界区
	LeaveCriticalSection(&g_critical_section);
}


void CDlgA::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	UpdateProcessList();
}


void CDlgA::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (ProcessList.m_hWnd)
	{
		ProcessList.SetWindowPos(0, 0, 0, cx, cy, SWP_NOZORDER);
	}
}


void CDlgA::OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CMenu* pSubMenu = m_menu.GetSubMenu(0);
	CPoint pos;
	GetCursorPos(&pos);
	pSubMenu->TrackPopupMenu(0, pos.x, pos.y, this);
}


void CDlgA::OnIdrMenu2()
{
	int sel = (int)ProcessList.GetFirstSelectedItemPosition();
	if (sel==0)
	{
		return;
	}
	sel -= 1;
	CString sPid = ProcessList.GetItemText(sel, 1);
	DWORD dPid = _wtoi(sPid);
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dPid);
	if (hProcess==0)
	{
		CString error;
		error.Format(L"获取进程句柄失败：%d", GetLastError());
		MessageBox(error);
	}
	else
	{
		TerminateProcess(hProcess, 0);
		CloseHandle(hProcess);
	}
	UpdateProcessList();
}


void CDlgA::OnEnumThread()
{
	int sel = (int)ProcessList.GetFirstSelectedItemPosition();
	if (sel == 0)
	{
		return;
	}
	sel -= 1;
	CString sPid = ProcessList.GetItemText(sel, 1);
	CString stitle = ProcessList.GetItemText(sel, 0);
	DWORD dPid = _wtoi(sPid);
	m_thDlg.setMessage(dPid,stitle);
	m_thDlg.Create(IDD_DIALOG6);
	m_thDlg.ShowWindow(SW_SHOW);
}


void CDlgA::OnEnumModule()
{
	int sel = (int)ProcessList.GetFirstSelectedItemPosition();
	if (sel == 0)
	{
		return;
	}
	sel -= 1;
	CString sPid = ProcessList.GetItemText(sel, 1);
	CString stitle = ProcessList.GetItemText(sel, 0);
	DWORD dPid = _wtoi(sPid);
	m_cDlgB.setProcessId(dPid);
	m_cDlgB.setTitle(stitle);
	m_cDlgB.Create(IDD_DIALOG2);
	m_cDlgB.ShowWindow(SW_SHOW);
}
