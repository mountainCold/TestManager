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

	// �ṩ�ӿ����ڴ����Ի���(��: ����ָ��+ID)
	void InsertTabWnd(int count, ...);

	// ��ʾ����
	void ShowTabWnd(int index);
	afx_msg void OnTcnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	// ���ڱ������еĴ���ָ��
	vector<CDialogEx*> m_WndVec;

};


