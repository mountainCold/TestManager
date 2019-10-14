#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
struct PROCESSINFO : public PROCESSENTRY32
{
	DWORD dwMemoryUsage; //内存使用率
	double dCpuUsage = 0;// cpu 使用率
};
BOOL EnumProcess(std::vector<PROCESSINFO>* proclist);
BOOL EnumThreadForProcess(DWORD PID, std::vector<THREADENTRY32>* ThreadList);
BOOL EnumProcessModul(DWORD dwPid, std::vector<MODULEENTRY32>* moduleList);
BOOL EnumProcessHeap();
BOOL EnumFile(CString path);
BOOL CALLBACK EnumWindowProcM(HWND hWnd, LPARAM lParam);
double getProcessMemoryUsage(DWORD dwPid);
double getProcessCpuUsage(DWORD dwPid);
double getCpuUsage();
/************************************************************************
// 函数名: EnableDebugPrivilege
// 功  能: 将程序的权限提升为SeDebug权限
// 全  名: EnableDebugPrivilege
// 权  限: public
// 返回值: bool
// 形  参: BOOL bIsOpen
//************************************************************************/
bool EnableDebugPrivilege();

