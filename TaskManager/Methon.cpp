#include "pch.h"
#include "Methon.h"
#include <Psapi.h>
BOOL EnumProcess(std::vector<PROCESSINFO>* proclist)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE) {
		return false;
	}
	PROCESSENTRY32 stcPe = { sizeof(stcPe) };
	//获取头节点
	if (Process32First(hSnap, &stcPe))
	{
		//循环遍历
		do
		{
			PROCESSINFO pi = *(PROCESSINFO*)& stcPe;
			
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, false, stcPe.th32ParentProcessID);
			if (hProcess == NULL)
			{
				pi.dwMemoryUsage = 0;
			}
			else
			{
				PROCESS_MEMORY_COUNTERS pmc = { sizeof(PROCESS_MEMORY_COUNTERS) };
				GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
				pi.dwMemoryUsage = pmc.WorkingSetSize;
				CloseHandle(hProcess);
			}
			proclist->push_back(pi);
		} while (Process32Next(hSnap, &stcPe));
	}
	CloseHandle(hSnap);
	return true;
}
BOOL EnumThreadForProcess(DWORD PID, std::vector<THREADENTRY32>* ThreadList)
{
	//1 创建快照
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0); //0表示当前进程
	// 首次遍历
	THREADENTRY32 thread32 = { sizeof(thread32) };
	if (Thread32First(hSnap, &thread32))
	{
		do
		{
			if (thread32.th32OwnerProcessID == PID)
			{
				ThreadList->push_back(thread32);
			}
		} while (Thread32Next(hSnap, &thread32));

	}
	CloseHandle(hSnap);
	return true;
}
BOOL EnumProcessModul(DWORD dwPid, std::vector<MODULEENTRY32>* moduleList)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPid);
	if (hSnap == INVALID_HANDLE_VALUE)return false;
	MODULEENTRY32 mInfo = { sizeof(MODULEENTRY32) };
	if (!Module32First(hSnap,&mInfo))return false;
	do 
	{
		moduleList->push_back(mInfo);
	} while (Module32Next(hSnap,&mInfo));
	return true;
}

BOOL EnumProcessHeap()
 {
// 	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_PROCESS, 0);
// 	if (INVALD_HANDLE_VALUE == hProcess)
// 	{
// 		;
// 	}
// 	pe32.dwSize = sizeof(pe32)
// 		if (!Process32First(hProcessSnap, &pe32))
// 		{
// 			;
// 		}
// 	do
// 	{
// 		hProcessHeapSnap = CreateToolhelp32Snapshot(TH32_SNAPHEAPLIST, pe32.dwProcessID);
// 		if (INVALD_HANDLE_VALUE == hProcessHeapSnap)
// 			continue;
// 		if (Heap32ListFirst())
// 		{
// 			;
// 		}
// 		do
// 		{
// 			//print heap list info
// 			if (Heap32First())
// 			{
// 				;
// 			}
// 			do
// 			{
// 				//print heap info
// 				//here u can use ToolhelpReadProcessMemory  or other api to read other process memory.
// 
// 			} while (Heap32Next());
// 		} while (Heap32ListNext());
// 		CloseHandle(hProcessHeapSnap);
// 		pe32.dwSize = sizeof(pe32);
// 	} while (Process32Next(hProcessSnap, &pe32))
// 		CloseHandle(hProcessSnap);
	return 0;
}

BOOL EnumFile(CString path)
{

	return 0;
}

BOOL CALLBACK EnumWindowProcM(HWND hWnd, LPARAM lParam)
{
	TCHAR buff[200];
	std::vector<DWORD>* vName = (std::vector<DWORD>*)lParam;
	GetWindowText(hWnd, buff, 200);
	if (/*IsWindowVisible(hWnd)==*/TRUE)
	{
		if (wcslen(buff) != 0)
		{
			vName->push_back((DWORD)hWnd);
		}	
	}
	return true;
}
double getProcessMemoryUsage(DWORD dwPid)
{
	HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
		FALSE,
		dwPid);
	double usage = 0;
	if (hProc != NULL) {

		PROCESS_MEMORY_COUNTERS pmc = { sizeof(PROCESS_MEMORY_COUNTERS) };;
		GetProcessMemoryInfo(hProc, &pmc, sizeof(pmc));
		usage = pmc.WorkingSetSize;
		CloseHandle(hProc);
	}
	return usage / 1024;
}
double	FILETIME2Double(const _FILETIME& fileTime)
{
	return	double(fileTime.dwHighDateTime * 4.294967296e9) + double(fileTime.dwLowDateTime);
}
#include <Winternl.h>
void getProcessTime(DWORD dwPid, LARGE_INTEGER* kernelTIme, LARGE_INTEGER* userTime)
{
	typedef struct _KERNEL_USERTEXTIMES
	{
		LARGE_INTEGER CreateTime;
		LARGE_INTEGER ExitTime;
		LARGE_INTEGER KernelTime;
		LARGE_INTEGER UserTime;
	} KERNEL_USERTEXTIMES, * PKERNEL_USERTEXTIMES;
	KERNEL_USERTEXTIMES time;
#define ProcessTimes  4

	HANDLE hProc = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwPid);
	if (hProc == NULL) {
		return;
	}
	decltype(NtQueryInformationProcess)* fnNtQueryInformationProcess;
	fnNtQueryInformationProcess = (decltype(NtQueryInformationProcess)*)
		(GetProcAddress(GetModuleHandle(_T("ntdll.dll")), "NtQueryInformationProcess"));

	DWORD read = 0;
	fnNtQueryInformationProcess(hProc,
		(PROCESSINFOCLASS)ProcessTimes,
		&time,
		sizeof(time),
		&read);
	*kernelTIme = time.KernelTime;
	*userTime = time.UserTime;
	CloseHandle(hProc);
}
double getProcessCpuUsage(DWORD dwPid)
{
	// 公式: (进程内核时间 + 进程用户时间) / (CPU内核时间 + CPU用户时间)

	LARGE_INTEGER kernelTime = { 0 };
	LARGE_INTEGER userTime = { 0 };
	getProcessTime(dwPid, &kernelTime, &userTime);

	//			空闲时间		内核时间		用户时间
	FILETIME cpuIdleTime = {}, cpuKernelTime = {}, cpuUserTime = {};

	// 获取时间
	GetSystemTimes((FILETIME*)& cpuIdleTime, (FILETIME*)& cpuKernelTime, (FILETIME*)& cpuUserTime);

	double proc = FILETIME2Double(*(FILETIME*)& kernelTime) + FILETIME2Double(*(FILETIME*)& userTime);
	double cpu = FILETIME2Double(cpuKernelTime) + FILETIME2Double(cpuKernelTime);
	return proc / cpu * 100.0;
}
double getCpuUsage()
{
	//			空闲时间		内核时间		用户时间
	_FILETIME	idleTime, kernelTime, userTime;
	// 获取时间
	GetSystemTimes(&idleTime, &kernelTime, &userTime);

	// 等待1000毫秒
	HANDLE	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	// 等待1000毫秒,使用内核对象等待会更精确
	WaitForSingleObject(hEvent, 1000);
	CloseHandle(hEvent);

	// 获取新的时间
	_FILETIME	newIdleTime, newKernelTime, newUserTime;
	GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);
	// 将各个时间转换
	double	dOldIdleTime = FILETIME2Double(idleTime);
	double	dNewIdleTime = FILETIME2Double(newIdleTime);
	double	dOldKernelTime = FILETIME2Double(kernelTime);
	double	dNewKernelTime = FILETIME2Double(newKernelTime);
	double	dOldUserTime = FILETIME2Double(userTime);
	double	dNewUserTime = FILETIME2Double(newUserTime);
	// 计算出使用率
	//		使用率 = 100.0 - (新空闲时间 - 旧空闲时间) / (新内核时间-旧内核时间  + 新用户时间 - 旧用户时间) *100.0
	return	int(100.0 - (dNewIdleTime - dOldIdleTime) / (dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUserTime) * 100.0);
}

bool EnableDebugPrivilege()
{
	HANDLE hToken = NULL;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;
	TOKEN_ELEVATION_TYPE ElevationType;
	DWORD dwSize = 0;
	if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,&hToken))
	{
		MessageBoxA(NULL,"打开失败",0,0);
		return   FALSE;
	}


	if(!LookupPrivilegeValue(NULL,SE_DEBUG_NAME,&sedebugnameValue))
	{
		CloseHandle(hToken);
		MessageBoxA(NULL,"获取失败",0,0);
		return false;
	}
	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // 选择还是关闭

	if(!AdjustTokenPrivileges(hToken,FALSE,&tkp,sizeof(tkp),NULL,NULL))
	{
		CloseHandle(hToken);
		MessageBoxA(NULL,"获取权限失败",0,0);
		return false;
	}
	if(GetTokenInformation(hToken,TokenElevationType,&ElevationType,sizeof(TOKEN_ELEVATION_TYPE),&dwSize))
	{
		// 如果令牌是以受限的权限运行 (TokenElevationTypeLimited) ,
		if(ElevationType == TokenElevationTypeLimited)
		{
			//MessageBox( NULL , L"您必须以管理员身份运行,否则无法获取获取系统的内存使用率" , 0 , 0 );
			return	FALSE;
		}
	}
	return true;
}
