#pragma once
#include "Resource.h"
#include <vector>
using namespace std;

// CMyTab

class CMyTab : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTab)

public:
	CMyTab();
	virtual ~CMyTab();
	/*CDialogEx* m_dlgA;
	CDlgA m_dlgA;
	CDlgB m_dlgB;
	CDlgC m_dlgC;*/
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:

	// 提供接口用于创建对话框(组: 窗口指针+ID)
	void InsertTabWnd(int count, ...);

	// 显示窗口
	void ShowTabWnd(int index);
	afx_msg void OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	// 用于保存所有的窗口指针
	vector<CDialogEx*> m_WndVec;

};


