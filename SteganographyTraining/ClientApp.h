#pragma once

#include <windows.h>

class Window;
class UIManager;

class ClientApp {
public:
    ClientApp();
    ~ClientApp();
    
    bool Initialize(HINSTANCE hInstance);

    Window* m_pWindow;
    UIManager* m_pUIManager;

    std::wstring string = L"Hello";
private:

};
