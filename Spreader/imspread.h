#pragma once
#ifndef IMSPREAD_H
#define IMSPREAD_H

#include "includes.h"

bool InfectIM();
bool SendMessage(HWND hwnd, int iWindow);
bool Send(int iWindow);
void Focus(HWND hwnd);
void Clear();


#endif // IMSPREAD_H
