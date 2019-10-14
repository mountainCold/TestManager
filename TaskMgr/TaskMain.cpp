#include <afxwin.h>
#include "resource.h"
#include "CMyDialog.h"
class CTaskMgr :public CWinApp
{
public:
	virtual BOOL InitInstance();

private:

};
BOOL CTaskMgr::InitInstance()
{
	CMyDialog MyDialog;
	MyDialog.DoModal();
	return true;
}
CTaskMgr taskMgr;