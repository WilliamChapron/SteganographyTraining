#include <iostream>
#include <stdexcept>
#include <string>

#include "Window.h"
#include "ClientApp.h"
#include "UIManager.h"
#include "UIElement.h"


Window::Window(HINSTANCE hInstance, ClientApp* clientApp) : hInstance(hInstance) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Sample Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        clientApp
    );

    ShowWindow(m_hwnd, SW_SHOWDEFAULT);
}

Window::~Window() {
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        if (pCreate) {
            ClientApp* clientApp = (ClientApp*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)clientApp);
        }
        SetTimer(hwnd, 1, 16, NULL);
        break;
    }

    case WM_TIMER: {
        ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (clientApp) {
            OutputDebugString((L"L" + clientApp->string).c_str());
            std::wcout << clientApp->string << std::endl;

            UIManager* test = clientApp->m_pUIManager;
            if (test != nullptr) {
                UIElement** elements = clientApp->m_pUIManager->GetAllElements();
                for (int i = 0; i < MAX_ELEMENTS; ++i) {
                    if (elements[i] != nullptr) {
                        std::wstring type;
                        switch (elements[i]->GetType()) {
                        case UIElementType::Button:
                            type = L"Button";
                            break;
                        case UIElementType::TextField:
                            type = L"TextField";
                            break;
                        }
                        //OutputDebugString((L"Element ID: " + std::to_wstring(elements[i]->GetID()) + L", Type: " + type + L"\n").c_str());
                        std::wcout << L"Element ID : " + std::to_wstring(elements[i]->GetID()) + L"--" + L"Type : " + type + L"\n" << std::endl;
                    }
                }
            }
        }
        break;
    }

    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


void Window::Run() {
    MSG msg;
    while (GetMessage(&msg, m_hwnd, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HWND Window::GetHWND() const {
    return m_hwnd;
}
