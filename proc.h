#include<iostream>
#include<Windows.h>
#include<TlHelp32.h>
#include<vector>
#include<fstream>
#include<ctime>
#include<sstream>

DWORD getprocid(const wchar_t* procname);



DWORD getmodulebaseaddres(DWORD procid, const wchar_t* modname);
