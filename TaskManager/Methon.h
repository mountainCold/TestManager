#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
struct PROCESSINFO : public PROCESSENTRY32
{
	DWORD dwMemoryUsage; //�ڴ�ʹ����
	double dCpuUsage = 0;// cpu ʹ����
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
// ������: EnableDebugPrivilege
// ��  ��: �������Ȩ������ΪSeDebugȨ��
// ȫ  ��: EnableDebugPrivilege
// Ȩ  ��: public
// ����ֵ: bool
// ��  ��: BOOL bIsOpen
//************************************************************************/
bool EnableDebugPrivilege();

