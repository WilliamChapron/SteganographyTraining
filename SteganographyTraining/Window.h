#pragma once

#include <windows.h>
#include <string>

class ClientApp;

class Window {
public:
    Window(HINSTANCE hInstance, ClientApp* clientApp);
    ~Window();

    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    void Run();

    HWND GetHWND() const;
private:
    HWND m_hwnd;
    HINSTANCE hInstance;
};
