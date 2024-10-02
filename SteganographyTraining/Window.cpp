#include <iostream>
#include <stdexcept>
#include <string>

#include "Window.h"
#include "ClientApp.h"
#include "UIManager.h"
#include "UIElement.h"
#include "BitmapImage.h"



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
        //SetTimer(hwnd, 1, 16, NULL);
        break;
    }
    case WM_COMMAND: {

        if (HIWORD(wParam) == BN_CLICKED) {

            HWND buttonHwnd = (HWND)lParam;

            UIButton* element = (UIButton*)GetWindowLongPtr(buttonHwnd, GWLP_USERDATA);

            if (element) {

                InvalidateRect(hwnd, NULL, TRUE);
                element->PerformClick();

            }
        }
        if (HIWORD(wParam) == EN_CHANGE) {
        }
        if (HIWORD(wParam) == EN_SETFOCUS) {
            int id = LOWORD(wParam);
            if (id == 2) {
                /*MessageBox(hwnd, L"Le texte a été modifié!", L"Information", MB_OK);*/
            }
        }
        
        break;
    }

    case WM_LBUTTONDOWN: { // Message pour le clic gauche
        // Vérifiez si le clic se produit dans le contrôle EDIT
        HWND hwndEdit = GetDlgItem(hwnd, 2); // Remplacez 2 par l'ID de votre contrôle EDIT
        if (hwndEdit && (HWND)lParam == hwndEdit) {
            MessageBox(hwnd, L"Clic sur le champ de texte!", L"Information", MB_OK);
        }
        break;
    }

    case WM_TIMER: {
        ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (!clientApp) {
            break;
        }

        int timerId = static_cast<int>(wParam);

        clientApp->GetUIManager()->HandleTimerDispawn(timerId);

        break;
    }

    // Stylize All Element Correspond to our style param send
 //   case WM_PAINT: {
 //       PAINTSTRUCT ps;
 //       HDC hdc = BeginPaint(hwnd, &ps);

 //       // Fill Window
 //       RECT clientRect;
 //       GetClientRect(hwnd, &clientRect); 
 //       HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0)); 
 //       FillRect(hdc, &clientRect, hBrush); 
 //       DeleteObject(hBrush); 


 //       // Check & Init part
 //       ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
 //       if (!clientApp) {
 //           EndPaint(hwnd, &ps);
 //           break;
 //       }
 //       if (!clientApp->isControlEventStarted) {
 //           EndPaint(hwnd, &ps);
 //           break;
 //       }
 //       UIManager* uiManager = clientApp->GetUIManager();
 //       if (!uiManager) {
 //           EndPaint(hwnd, &ps);
 //           break;
 //       }

 //       UIElement** elements = uiManager->GetAllElements();
 //       int elementCount = uiManager->GetElementsCount();

 //       // Draw Controls
 //       for (int i = 0; i < elementCount; ++i) {
 //           UIElement* element = elements[i];
 //           HWND elementHwnd = element->GetHWND();

 //           PAINTSTRUCT psElement;
 //           HDC hdcElement = BeginPaint(elementHwnd, &psElement);

 //           element->PerformPaint(hdcElement);

 //           EndPaint(elementHwnd, &psElement);
 //       }

 //       

 //       // Show img
 //       //clientApp->m_bitmapImgLoader = new BitmapImage();
 //       //clientApp->m_bitmapImgLoader->Load("C:\\Users\\wchapron\\Documents\\GitHub\\SteganographyTraining\\bmp_test.bmp");
 //       BitmapImage* img = clientApp->m_bitmapImgLoader;

 //       if (clientApp->m_bitmapImgLoader != nullptr) {

 //           std::wcout << "Bit map show" << std::endl;

 //           HBITMAP hBitmap = nullptr;
 //           HDC imgDeviceContext = nullptr;
 //           HDC mainDeviceContext = hdc;

 //           hBitmap = CreateDIBitmap(
 //               mainDeviceContext,
 //               &img->m_infoHeader,
 //               CBM_INIT,
 //               &img->m_pPixelData,
 //               (BITMAPINFO*)(&img->m_infoHeader),
 //               DIB_RGB_COLORS
 //           );

 //           if (!hBitmap) {
 //               MessageBox(NULL, L"Erreur lors de la création du bitmap", L"Erreur", MB_OK);
 //               return 0;
 //           }

 //           imgDeviceContext = CreateCompatibleDC(mainDeviceContext);
 //           if (!imgDeviceContext) {
 //               MessageBox(NULL, L"Erreur lors de la création du Device Context", L"Erreur", MB_OK);
 //               DeleteObject(hBitmap);
 //               return 0;
 //           }

 //           HBITMAP oldBitmap = (HBITMAP)SelectObject(imgDeviceContext, hBitmap);

 ///*           BOOL result = StretchBlt(
 //               mainDeviceContext,
 //               0,
 //               0,
 //               200,
 //               100,
 //               imgDeviceContext,
 //               0,
 //               0,
 //               img->m_infoHeader.biWidth,
 //               img->m_infoHeader.biHeight,
 //               SRCCOPY
 //           );*/

 //           BitBlt(
 //               mainDeviceContext, 
 //               0,                 
 //               0,                 
 //               img->m_infoHeader.biWidth, 
 //               img->m_infoHeader.biHeight,
 //               imgDeviceContext,   
 //               0,                  
 //               0,                  
 //               SRCCOPY
 //           );

 //           SelectObject(imgDeviceContext, oldBitmap);
 //           DeleteDC(imgDeviceContext);
 //       }


 //       EndPaint(hwnd, &ps);
 //       break;
 //   }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        // Check & Init part
        ClientApp* clientApp = (ClientApp*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (!clientApp) {
            EndPaint(hwnd, &ps);
            break;
        }
        // Show img
        clientApp->m_bitmapImgLoader = new BitmapImage();
        clientApp->m_bitmapImgLoader->Load("C:\\Users\\wchapron\\Documents\\GitHub\\SteganographyTraining\\mario.bmp");
        BitmapImage* img = clientApp->m_bitmapImgLoader;

        if (clientApp->m_bitmapImgLoader != nullptr) {

            std::wcout << "Bit map show" << std::endl;

            HBITMAP hBitmap = nullptr;
            HDC imgDeviceContext = nullptr;
            HDC mainDeviceContext = hdc;

            hBitmap = CreateDIBitmap(
                mainDeviceContext,
                &img->m_infoHeader,
                CBM_INIT,
                &img->m_pPixelData,
                (BITMAPINFO*)(&img->m_infoHeader),
                DIB_RGB_COLORS
            );

            if (!hBitmap) {
                MessageBox(NULL, L"Erreur lors de la création du bitmap", L"Erreur", MB_OK);
                return 0;
            }
            imgDeviceContext = CreateCompatibleDC(mainDeviceContext);
            if (!imgDeviceContext) {
                MessageBox(NULL, L"Erreur lors de la création du Device Context", L"Erreur", MB_OK);
                DeleteObject(hBitmap);
                return 0;
            }

            HBITMAP oldBitmap = (HBITMAP)SelectObject(imgDeviceContext, hBitmap);

            BitBlt(
                mainDeviceContext,
                0,
                0,
                img->m_infoHeader.biWidth,
                img->m_infoHeader.biHeight,
                imgDeviceContext,
                0,
                0,
                SRCCOPY
            );

            //BOOL result = StretchBlt
            //(
            //    mainDeviceContext,
            //    0,
            //    0,
            //    200,
            //    100,
            //    imgDeviceContext,
            //    0,
            //    0,
            //    img->m_infoHeader.biWidth,
            //    img->m_infoHeader.biHeight,
            //    SRCCOPY
            //);

            SelectObject(imgDeviceContext, oldBitmap);
            DeleteDC(imgDeviceContext);
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