// CDlgE.cpp: 实现文件
//

#include "pch.h"
#include "TaskManager.h"
#include "CDlgE.h"
#include "afxdialogex.h"
#include <vector>
#include "Resource.h"


// CDlgE 对话框

IMPLEMENT_DYNAMIC(CDlgE, CDialogEx)

CDlgE::CDlgE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

CDlgE::~CDlgE()
{
}

void CDlgE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_FileTree);
	DDX_Control(pDX, IDC_LIST1, m_FileList);
}



BEGIN_MESSAGE_MAP(CDlgE, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CDlgE::OnClickTree1)
	ON_WM_SIZE()
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CDlgE::OnRclickTree1)
	ON_COMMAND(ID_32789, &CDlgE::OnMenuClick)
END_MESSAGE_MAP()


// CDlgE 消息处理程序

BOOL CDlgE::EnumFile(CString path)
{
	WIN32_FIND_DATA fileData = { 0 };
	HANDLE hFind =
		FindFirstFile(path + L"\\*", &fileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		return FALSE;
	}
	DWORD dwFileCount = 0;
	HTREEITEM hItem = 0;
	do
	{
		if (wcscmp(fileData.cFileName, L".") == 0 || wcscmp(fileData.cFileName, L"..") == 0)continue;
		if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			hItem =m_FileTree.InsertItem(fileData.cFileName, hItem);
			wchar_t* pPath = new wchar_t[266];

			swprintf_s(pPath, 266, L"%s\\%s", (LPCWSTR)path, fileData.cFileName);
			m_FileTree.SetItemData(hItem, (DWORD_PTR)pPath);
		}
		else
		{
			m_FileList.InsertItem(dwFileCount, fileData.cFileName);
			ULONG64 size =(fileData.nFileSizeHigh<<32)| fileData.nFileSizeLow;
			CString buffer;
			buffer.Format(L"%lldKb", size / 1024);
			m_FileList.SetItemText(dwFileCount, 1, buffer);
			FileTimeToLocalFileTime(&fileData.ftCreationTime, &fileData.ftCreationTime);
			SYSTEMTIME sysTime = { 0 };
			FileTimeToSystemTime(&fileData.ftCreationTime, &sysTime);
			buffer.Format(L"%04d/%02d/%02d %02d:%02d:%02d",
				sysTime.wYear,
				sysTime.wMonth,
				sysTime.wDay,
				sysTime.wHour,
				sysTime.wMinute,
				sysTime.wSecond);
			m_FileList.SetItemText(dwFileCount, 2, buffer);

			++dwFileCount;
		}


	} while (FindNextFile(hFind, &fileData));
	return 0;
}
BOOL CDlgE::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//m_menu.LoadMenu(ID_32789);
	m_menu.LoadMenu(IDR_MENU3);
	TCHAR buffer[100];
	GetLogicalDriveStrings(100, buffer);
	TCHAR* p = buffer;
	while (*p!=0)
	{
		TCHAR volName[50];
		TCHAR fileSystemName[50];
		GetVolumeInformation(p, volName, sizeof(volName), NULL, NULL, NULL,
			fileSystemName, sizeof(fileSystemName));
		CString buff;
		buff.Format(L"%s[%s]%s", volName, p, fileSystemName);
		HTREEITEM hItem = m_FileTree.InsertItem(buff);
		wchar_t* pBuff = _wcsdup(p);
		m_FileTree.SetItemData(hItem, (DWORD_PTR)pBuff);
		p += 4;
	}
	m_FileList.SetExtendedStyle(LVS_EX_FULLROWSELECT );
	m_FileList.InsertColumn(0, L"文件名", 0, 300);
	m_FileList.InsertColumn(1, L"文件类型", 0, 200);
	m_FileList.InsertColumn(2, L"文件大小", 0, 100);
	m_FileList.InsertColumn(3, L"创建日期", 0, 200);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgE::OnClickTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
	CPoint pos;
	GetCursorPos(&pos);
	m_FileTree.ScreenToClient(&pos);
	HTREEITEM hItem = m_FileTree.HitTest(pos);
	CString path = (wchar_t*)m_FileTree.GetItemData(hItem);
	HTREEITEM hChild = m_FileTree.GetNextItem(hItem, TVGN_CHILD);
	if (hChild != NULL) return;
	WIN32_FIND_DATA fileData = { 0 };
	HANDLE hFind =
		FindFirstFile(path + L"\\*", &fileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		return;
	}

	// 删除所有的节点.
	m_FileList.DeleteAllItems();

	DWORD dwFileCount = 0;
	HTREEITEM hItem2 = 0;
	do {
		if (wcscmp(fileData.cFileName, L".") == 0
			|| wcscmp(fileData.cFileName, L"..") == 0)
		{
			continue;
		}


		// 如果不是个目录, 就添加
		m_FileList.InsertItem(dwFileCount,
			fileData.cFileName);

		if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			hItem2 = m_FileTree.InsertItem(fileData.cFileName, hItem);
			wchar_t* pPath = new wchar_t[266];
			m_FileList.SetItemText(dwFileCount, 1, L"文件夹");
			m_FileList.SetItemText(dwFileCount, 2, NULL);
			swprintf_s(pPath, 266, L"%s\\%s", (LPCWSTR)path, fileData.cFileName);
			m_FileTree.SetItemData(hItem2, (DWORD_PTR)pPath);
		}
		else
		{
			TCHAR att[4] = { 0 };
			TCHAR name[260];
			swprintf_s(name,260,L"%s", fileData.cFileName);
			int a = -1;
			for (int i=0;i<260;++i)
			{
				if (name[i] == '.')a = 0;
				if (a >= 0 && a <= 3)
				{
					att[a] = name[i+1];
					++a;
				}

			}
			m_FileList.SetItemText(dwFileCount, 1, att);
			ULONG64 size = (fileData.nFileSizeHigh << 32) | fileData.nFileSizeLow;
			CString buffer;
			buffer.Format(L"%8dKb",
				size / 1024);
			m_FileList.SetItemText(dwFileCount, 2, buffer);
		}
		//{

			CString buffer;
			FileTimeToLocalFileTime(&fileData.ftCreationTime, &fileData.ftCreationTime);
			SYSTEMTIME sysTime = { 0 };
			FileTimeToSystemTime(&fileData.ftCreationTime, &sysTime);
			buffer.Format(L"%04d/%02d/%02d %02d:%02d:%02d",
				sysTime.wYear,
				sysTime.wMonth,
				sysTime.wDay,
				sysTime.wHour,
				sysTime.wMinute,
				sysTime.wSecond);
			m_FileList.SetItemText(dwFileCount, 3, buffer);

			++dwFileCount;
		//}

	} while (FindNextFile(hFind, &fileData));
	
}

void GetVSFiles(const CString& dir,
	std::vector<CString>* filePaths)
{

	WIN32_FIND_DATA fileData = { 0 };
	HANDLE hFind =
		FindFirstFile(dir + L"\\*", &fileData);
	if (hFind == INVALID_HANDLE_VALUE) {
		return;
	}


	DWORD dwFileCount = 0;
	HTREEITEM hItem2 = 0;
	do {
		if (wcscmp(fileData.cFileName, L".") == 0
			|| wcscmp(fileData.cFileName, L"..") == 0)
		{
			continue;
		}


		// 如果不是个目录, 就添加
		if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			GetVSFiles(dir + L"\\" + fileData.cFileName, filePaths);
		}
		else
		{
			// 判断是否是vs垃圾文件的后缀
			const TCHAR* extName[] = { L".ilk",L".pdb",L".obj",L".log",L".pch",L".tlog",L".lastbuildstate",L".sdf",L".idb",L".ipch",L".res",L".o",L".lst",L".knl",L".img",L".bin",L".db" };

			for (auto& i : extName) {
				TCHAR* pExtName = fileData.cFileName + wcslen(fileData.cFileName);
				while (pExtName != fileData.cFileName && *pExtName != '.')
					--pExtName;

				if (_wcsicmp(i, pExtName) == 0)
				{
					filePaths->push_back(dir + L"\\" + fileData.cFileName);
				}
			}

		}

	} while (FindNextFile(hFind, &fileData));
}

void CDlgE::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_FileTree.m_hWnd)
	{
		m_FileTree.SetWindowPos(0, 0, 0, 150, cy, SWP_NOZORDER);
	}
	if (m_FileList.m_hWnd)
	{
		m_FileList.SetWindowPos(0, 150, 0, cx, cy, SWP_NOZORDER);
	}

}


void CDlgE::OnRclickTree1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CPoint pos;
	// 获取鼠标坐标(是一个屏幕坐标)
	GetCursorPos(&pos);
	// 将屏幕坐标转换成树控件的客户区坐标
	m_FileTree.ScreenToClient(&pos);

	HTREEITEM hItem = m_FileTree.HitTest(pos);
	if (hItem)
	{
		m_curPath = (wchar_t*)m_FileTree.GetItemData(hItem);
	}
	else {
		m_curPath.Empty();
	}

	CMenu* pSubMenu = m_menu.GetSubMenu(0);
	GetCursorPos(&pos);
	pSubMenu->TrackPopupMenu(0, pos.x, pos.y, this);
	*pResult = 0;
}


void CDlgE::OnMenuClick()
{
	// 删除所有列表节点
	m_FileList.DeleteAllItems();

	// 遍历文件夹获取vs的垃圾文件
	std::vector<CString> paths;
	GetVSFiles(m_curPath, &paths);
	for (auto& i : paths) {
		// 将所有垃圾文件插入到列表控件
		m_FileList.InsertItem(0, i);

		// 删除垃圾文件
		 DeleteFile(i);
	}
}
