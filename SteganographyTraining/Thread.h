#include <windows.h>
#include <iostream>

#pragma once

class ClientApp;

class Thread
{
public:
    HANDLE Init(ClientApp* clientAppInstance);
    static DWORD WINAPI StaticThreadFunction(LPVOID lpParam);
private:
	HANDLE m_handle;
};

