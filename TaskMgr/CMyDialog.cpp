// CMyDialog.cpp: 实现文件
//
#include "CMyDialog.h"
#include "afxdialogex.h"


// CMyDialog 对话框

IMPLEMENT_DYNAMIC(CMyDialog, CDialogEx)

CMyDialog::CMyDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CMyDialog::~CMyDialog()
{
}

void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialogEx)
END_MESSAGE_MAP()


// CMyDialog 消息处理程序


