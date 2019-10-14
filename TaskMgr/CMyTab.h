#pragma once
#include "resource.h"
#include <afxdialogex.h>
#include "CDlgC.h"
#include "CDlgA.h"
#include "CDlgB.h"
// CMyTab

class CMyTab : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTab)

public:
	CMyTab();
	virtual ~CMyTab();


protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
private:
	/*CDialogEx* m_dlgA;*/
	CDlgA m_dlgA;
	CDlgB m_dlgB;
	CDlgC m_dlgC;
};


