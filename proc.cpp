
#include"proc.h"

DWORD getprocid(const wchar_t* procname) {

	DWORD procid = 0;
	HANDLE hsnap = (CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0));
	if (hsnap != INVALID_HANDLE_VALUE)
	{
		PROCESSENTRY32 procentry;
		procentry.dwSize = sizeof(procentry);
		if (Process32First(hsnap, &procentry))
		{
			do
			{
				if (!_wcsicmp(procentry.szExeFile, procname)) {
					procid = procentry.th32ProcessID;
					break;
				}
			} while (Process32Next(hsnap, &procentry));

		}
	}
	CloseHandle(hsnap);
	return procid;





}







DWORD getmodulebaseaddres(DWORD procid, const wchar_t* modname) {

	DWORD modbaseaddr = 0;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procid);
	if (hsnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modentry;
		modentry.dwSize = sizeof(modentry);
		if (Module32First(hsnap, &modentry))
		{
			do
			{
				if (!_wcsicmp(modentry.szModule, modname))
				{

					modbaseaddr = (DWORD)modentry.modBaseAddr;
					break;
				}



			} while (Module32Next(hsnap, &modentry));
		}
	}

	CloseHandle(hsnap);
	return modbaseaddr;







}