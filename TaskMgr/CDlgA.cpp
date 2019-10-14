// CDlgA.cpp: 实现文件
//

#include "CDlgA.h"
#include "afxdialogex.h"


// CDlgA 对话框

IMPLEMENT_DYNAMIC(CDlgA, CDialogEx)

CDlgA::CDlgA(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CDlgA::~CDlgA()
{
}

void CDlgA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgA, CDialogEx)
END_MESSAGE_MAP()


// CDlgA 消息处理程序
