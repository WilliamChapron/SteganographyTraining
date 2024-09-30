#include <iostream>
#include <stdexcept>
#include <string>

#include "Window.h"
#include "ClientApp.h"
#include "UIManager.h"
#include "UIElement.h"


Window::Window(HINSTANCE hInstance, ClientApp* clientApp) : m_hInstance(hInstance) {
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
    static int lastClickX = 0;
    static int lastClickY = 0;

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
        if (!clientApp) {
            break;
        }

        UIManager* uiManagerI = clientApp->GetUIManager();
        if (uiManagerI == nullptr) {
            break;
        }

        // Exemple d'affichage d'éléments UI (commenté dans votre code)
        // UIElement** elements = uiManagerI->GetAllElements();
        // for (int i = 0; i < MAX_ELEMENTS; ++i) {
        //     if (elements[i] != nullptr) {
        //         std::wstring type;
        //         switch (elements[i]->GetType()) {
        //         case UIElementType::Button:
        //             type = L"Button";
        //             break;
        //         case UIElementType::TextField:
        //             type = L"TextField";
        //             break;
        //         }
        //         std::wcout << L"Element ID : " + std::to_wstring(elements[i]->GetID()) + L" -- Type : " + type + L"\n" << std::endl;
        //     }
        // }
        break;
    }

    //case WM_LBUTTONDOWN: {
    //    lastClickX = LOWORD(lParam);
    //    lastClickY = HIWORD(lParam);
    //    break;
    //}

    // #TODO Faire un tableau de use state qui lie un boutton a une action, chaque button peut etre liée a une action et quand il est retrouvé, pour chaque evenement clique, remplissage ou autre on fait des choses 

    case WM_COMMAND: {
        int commandId = LOWORD(wParam);
        switch (commandId) {
            case 1: // Button Id, with it we can retrieve button class
                MessageBox(hwnd, (L"Clic détecté sur le bouton à la position : (" +
                    std::to_wstring(lastClickX) + L", " +
                    std::to_wstring(lastClickY) + L")").c_str(),
                    L"Info", MB_OK);

                ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
                //if (clientApp) {
                //    UIManager* uiManager = clientApp->GetUIManager();
                //    uiManager->HandleClickAtPosition(lastClickX, lastClickY);
                //}
                break;
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