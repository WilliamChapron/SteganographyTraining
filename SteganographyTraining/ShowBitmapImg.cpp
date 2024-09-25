#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

HBITMAP hBitmap = nullptr;
HDC imgDeviceContext = nullptr;
uint8_t* pixels = nullptr;
BITMAPINFOHEADER infoHeader;
BITMAPFILEHEADER fileHeader;
HDC mainDeviceContext = nullptr;


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    AllocConsole();

    // Rediriger stdout vers la console
    FILE* fp;
    if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0) {
        MessageBox(NULL, L"Erreur lors de la redirection de stdout", L"Erreur", MB_OK);
        return -1;
    }



    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        100, 100, 1000, 800,            // Position x, y and size cx, cy

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );



    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        mainDeviceContext = BeginPaint(hwnd, &ps);

        std::ifstream file("C:\\Users\\wchapron\\Documents\\GitHub\\SteganographyTraining\\loadBitmap.bmp", std::ios::binary);
        if (!file) {
            MessageBox(NULL, L"Erreur lors de l'ouverture du fichier BMP", L"Erreur", MB_OK);
            return 0;
        }

        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

        if (fileHeader.bfType != 0x4D42) {
            MessageBox(NULL, L"Erreur! Format de fichier non reconnu.", L"Erreur", MB_OK);
            return 0;
        }

        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

        if (infoHeader.biBitCount != 24) {
            MessageBox(NULL, L"Erreur! Seuls les fichiers BMP 24 bits sont support�s.", L"Erreur", MB_OK);
            return 0;
        }

        int row_padded = (infoHeader.biWidth * 3);
        pixels = new uint8_t[row_padded * infoHeader.biHeight];

        file.read(reinterpret_cast<char*>(pixels), row_padded * infoHeader.biHeight);
        file.close();

        hBitmap = CreateDIBitmap(
            mainDeviceContext,
            &infoHeader,
            CBM_INIT,
            pixels,
            (BITMAPINFO*)(&infoHeader),
            DIB_RGB_COLORS
        );

        if (!hBitmap) {
            MessageBox(NULL, L"Erreur lors de la cr�ation du bitmap", L"Erreur", MB_OK);
            return 0;
        }

        imgDeviceContext = CreateCompatibleDC(mainDeviceContext);
        if (!imgDeviceContext) {
            MessageBox(NULL, L"Erreur lors de la cr�ation du Device Context", L"Erreur", MB_OK);
            DeleteObject(hBitmap);
            return 0;
        }

        HBITMAP oldBitmap = (HBITMAP)SelectObject(imgDeviceContext, hBitmap);

        BOOL result = StretchBlt(
            mainDeviceContext,
            0,
            0,
            800,
            600,
            imgDeviceContext,
            0,
            0,
            infoHeader.biWidth,
            infoHeader.biHeight,
            SRCCOPY
        );

        //BitBlt(
    //    mainDeviceContext, 
    //    0,                 
    //    0,                 
    //    infoHeader.biWidth, 
    //    infoHeader.biHeight, 
    //    imgDeviceContext,   
    //    0,                  
    //    0,                  
    //    SRCCOPY
    //);

        SelectObject(imgDeviceContext, oldBitmap);
        DeleteDC(imgDeviceContext);

        EndPaint(hwnd, &ps);

        return 0;
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}