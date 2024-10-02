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

    static bool onePaint = false;

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
        //InvalidateRect(hwnd, NULL, TRUE);
        ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (!clientApp) {
            break;
        }

        UIManager* uiManagerI = clientApp->GetUIManager();
        if (uiManagerI == nullptr) {
            break;
        }
        break;
    }

    // #TODO Faire un tableau de use state qui lie un boutton a une action, chaque button peut etre liée a une action et quand il est retrouvé, pour chaque evenement clique, remplissage ou autre on fait des choses 

    case WM_COMMAND: {
        //int commandId = LOWORD(wParam);

        //ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        //if (!clientApp) {
        //    break;
        //}
        //if (!clientApp->isControlEventStarted) {
        //    break;
        //}
        //UIManager* uiManager = clientApp->GetUIManager();
        //if (!uiManager) {
        //    break;
        //}

        //UIElement** elements = uiManager->GetAllElements();
        //int elementCount = uiManager->GetElementsCount();

        //for (int i = 0; i < elementCount; ++i) {
        //    if (elements[i] != nullptr && elements[i]->GetID() == commandId) {
        //        std::wcout << L"Element trouvé: ID=" << elements[i]->GetID()
        //            << L", Type=" << elements[i]->GetTypeAsString()
        //            << L", Position=(" << elements[i]->GetX() << L"," << elements[i]->GetY() << L")"
        //            << L", Dimensions=" << elements[i]->GetWidth() << L"x" << elements[i]->GetHeight() << std::endl;


        //        elements[i]->PerformClick();
        //        /*SendMessage(hwnd, WM_SETREDRAW, i, 0);*/
        //        //InvalidateRect(hwnd, NULL, TRUE);
        //        
        //        break;
        //    }
        //}
        //break;
        
        if (HIWORD(wParam) == BN_CLICKED) {
            HWND buttonHwnd = (HWND)lParam;  

            // Récupérer l'instance UIButton associée à cet hwnd
            UIButton* element = (UIButton*)GetWindowLongPtr(buttonHwnd, GWLP_USERDATA);

            if (element) {
                std::wcout << L"Element trouvé:" << std::endl;
                std::wcout << L"  ID: " << element->GetID() << std::endl;
                std::wcout << L"  Type: " << element->GetTypeAsString() << std::endl;
                std::wcout << L"  Position: (" << element->GetX() << L", " << element->GetY() << L")" << std::endl;
                std::wcout << L"  Taille: (" << element->GetWidth() << L", " << element->GetHeight() << L")" << std::endl;
                InvalidateRect(hwnd, NULL, TRUE); // Invalider tout le rectangle du bouton

            }
            else {
                std::wcout << L"Aucun élément trouvé pour le hwnd: " << buttonHwnd << std::endl;
            }
        }
    }

    //case WM_COMMAND: {
    //    int commandId = LOWORD(wParam);

    //    break;
    //}

    case WM_SETFOCUS: {
        break;
    }

    case WM_SETREDRAW: {
        //int index = static_cast<int>(wParam); 
        //std::wcout << L"Redraw Element" << std::to_wstring(index) << std::endl;

        //ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        //if (!clientApp) {
        //    break;
        //}
        //UIManager* uiManager = clientApp->GetUIManager();
        //if (!uiManager) {
        //    break;
        //}

        //// Obtenir le tableau des éléments
        //UIElement** elements = uiManager->GetAllElements();
        //int elementCount = uiManager->GetElementsCount();

        //// Vérifier que l'index est valide
        //if (index >= 0 && index < elementCount) {
        //    UIElement* element = elements[index];
        //    HWND elementHwnd = element->GetHWND();

        //    // Invalider le rectangle de l'élément
        //    InvalidateRect(elementHwnd, NULL, TRUE);

        //    // Gérer le dessin de l'élément
        //    PAINTSTRUCT ps;
        //    HDC hdcElement = BeginPaint(elementHwnd, &ps);

        //    // Appel de la méthode PerformPaint pour dessiner l'élément
        //    element->PerformPaint(hdcElement);

        //    EndPaint(elementHwnd, &ps);
        //}
        //else {
        //    std::wcout << L"Index out of range" << std::endl;
        //}
        //break;
    }

      
    // Stylize All Element Correspond to our style param send
    case WM_PAINT: {
        //if (onePaint) {
        //    break;
        //}
        onePaint = true;
        std::wcout << L"Paint" << std::endl;
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (!clientApp) {
            EndPaint(hwnd, &ps);
            break;
        }
        if (!clientApp->isControlEventStarted) {
            EndPaint(hwnd, &ps);
            break;
        }
        UIManager* uiManager = clientApp->GetUIManager();
        if (!uiManager) {
            EndPaint(hwnd, &ps);
            break;
        }

        UIElement** elements = uiManager->GetAllElements();
        int elementCount = uiManager->GetElementsCount();

        for (int i = 0; i < elementCount; ++i) {
            UIElement* element = elements[i];
            HWND elementHwnd = element->GetHWND();

            PAINTSTRUCT psElement;
            HDC hdcElement = BeginPaint(elementHwnd, &psElement);

            element->PerformPaint(hdcElement);

            EndPaint(elementHwnd, &psElement);
        }
        EndPaint(hwnd, &ps);
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
    MSG msg = {};
    while (GetMessage(&msg, m_hwnd, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}