
// TaskManagerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TaskManager.h"
#include "TaskManagerDlg.h"
#include "afxdialogex.h"
#include "CDlgA.h"
#include "CDlgC.h"
#include "CMyTab.h"
#include "CDlgD.h"
#include "CDlgE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTaskManagerDlg 对话框



CTaskManagerDlg::CTaskManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASKMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaskManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CTaskManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(ID_32773, &CTaskManagerDlg::On32773)
	ON_COMMAND(ID_32774, &CTaskManagerDlg::On32774)
	ON_COMMAND(ID_32775, &CTaskManagerDlg::On32775)
	ON_COMMAND(ID_32776, &CTaskManagerDlg::On32776)
END_MESSAGE_MAP()


// CTaskManagerDlg 消息处理程序

BOOL CTaskManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	::RegisterHotKey(m_hWnd, 0x1234, MOD_CONTROL | MOD_SHIFT, 'L');
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_Tab.InsertTabWnd(4,
		new CDlgA, IDD_DIALOG1,
		new CDlgC, IDD_DIALOG3,
		new CDlgD, IDD_DIALOG4,
		new CDlgE, IDD_DIALOG5 );

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTaskManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTaskManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTaskManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTaskManagerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (m_Tab.m_hWnd)
	{
		CRect rect = { 0,0,cx,cy };
		m_Tab.MoveWindow(rect);
		for (auto&i:m_Tab.m_WndVec)
		{
			rect.DeflateRect(1, 25, 1, 1);
			i->MoveWindow(rect);
		}
	}
	// TODO: 在此处添加消息处理程序代码
}

//关机
void CTaskManagerDlg::On32773()
{
	// TODO: 在此添加命令处理程序代码
}

//重启
void CTaskManagerDlg::On32774()
{
	// TODO: 在此添加命令处理程序代码
}

//睡眠
void CTaskManagerDlg::On32775()
{
	// TODO: 在此添加命令处理程序代码
}

//锁屏
void CTaskManagerDlg::On32776()
{
	EnableDebugPrivilege();
	LockWorkStation();
}


BOOL CTaskManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	if ((pMsg->message==WM_HOTKEY) &&(pMsg->wParam==0x1234))
	{
		if (IsWindowVisible()==TRUE)
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			ShowWindow(SW_SHOW);
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
