// CDlgC.cpp: 实现文件
//

#include "CDlgC.h"
#include "afxdialogex.h"


// CDlgC 对话框

IMPLEMENT_DYNAMIC(CDlgC, CDialogEx)

CDlgC::CDlgC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

}

CDlgC::~CDlgC()
{
}

void CDlgC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgC, CDialogEx)
END_MESSAGE_MAP()


// CDlgC 消息处理程序
