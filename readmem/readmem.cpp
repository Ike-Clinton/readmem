#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "service.h"

using namespace std;

/**
* This program gets a process handle to "Minesweeper"
* it then prints out the value at "address" every half second
* using ReadProcessMemory
* This value is simply the current number of mines on the level
*/
int main()
{
	// Offsets
	DWORD dwImageBase = 0x400000;
	DWORD dwVirtualAddress = 0x00001000;
	DWORD dwBaseAddress = 0x000111;
	//DWORD dwOldWorldBase = 0x103BBA8;
	DWORD pWorldBase = 0x103ABF0;
	//WORD wOldPlayerOffset = 0x1650;
	WORD wPlayerOffset = 0x1658;
	BYTE bVstateOffset = 0x34;

	//HWND hwnd;
	//hwnd = FindWindow(NULL, L"DayZ");

	// The process ID, used to r/w into the memory
	//DWORD pid;
	// Get the process ID and place the value at the address of pid
	//GetWindowThreadProcessId(hwnd, &pid);
	//cout << "pid = " << pid << "\n";

	LPTSTR DriverFilePath = TEXT("n0h8m8.sys");

	LPTSTR SvcName = TEXT("n0h8m8");
	LPTSTR SvcDisplayName = TEXT("n0h8m8");

	CService svc(DriverFilePath, SvcName, SvcDisplayName, SERVICE_DEMAND_START);
	
	if (svc.CreateSvc() == SVC_OK)
	{
		printf("Service creation successful\n");
	}
	else
	{
		printf("Service creation failed\n");
		return 1;
	}

	DWORD ERROR_CODE;
	ERROR_CODE = svc.StartSvc();
	if (ERROR_CODE == SVC_OK)
	{
		printf("Service started. \n Pres key to stop. . . \n");
	}
	else
	{
		printf("Service startup failed with code %lu\n", ERROR_CODE);
		return 1;
	}

	getchar();

	if (svc.StopSvc() == SVC_OK)
		printf("Service stop: OK.\n");
	else {
		printf("Service stop: FAILD.\n");
		return 1;
	}

	if (svc.UnloadSvc() == SVC_OK)
		printf("Service unload: OK.\n");
	else {
		printf("Service unload: FAILD.\n");
		return 1;
	}



	return 0;
}






