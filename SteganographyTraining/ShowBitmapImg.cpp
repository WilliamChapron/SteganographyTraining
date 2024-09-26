//
//#ifndef UNICODE
//#define UNICODE
//#endif 
//
//#include <windows.h>
//#include <fstream>
//#include <iostream>
//#include <vector>
//
//#include <stdexcept>
//#include <thread> // Pour std::this_thread::sleep_for
//
//HBITMAP hBitmap = nullptr;
//HDC imgDeviceContext = nullptr;
//uint8_t* pixels = nullptr;
//BITMAPINFOHEADER infoHeader;
//BITMAPFILEHEADER fileHeader;
//HDC mainDeviceContext = nullptr;
//
//
//int idTimer = -1;
//int currentPixelIndex = 0;
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
//{
//    AllocConsole();
//
//    // Rediriger stdout vers la console
//    FILE* fp;
//    if (freopen_s(&fp, "CONOUT$", "w", stdout) != 0) {
//        MessageBox(NULL, L"Erreur lors de la redirection de stdout", L"Erreur", MB_OK);
//        return -1;
//    }
//
//
//    // Register the window class.
//    const wchar_t CLASS_NAME[] = L"Sample Window Class";
//
//    WNDCLASS wc = { };
//
//    wc.lpfnWndProc = WindowProc;
//    wc.hInstance = hInstance;
//    wc.lpszClassName = CLASS_NAME;
//
//    RegisterClass(&wc);
//
//    // Create the window.
//
//    HWND hwnd = CreateWindowEx(
//        0,                              // Optional window styles.
//        CLASS_NAME,                     // Window class
//        L"Learn to Program Windows",    // Window text
//        WS_OVERLAPPEDWINDOW,            // Window style
//
//        // Size and position
//        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
//
//        NULL,       // Parent window    
//        NULL,       // Menu
//        hInstance,  // Instance handle
//        NULL        // Additional application data
//    );
//
//    if (hwnd == NULL)
//    {
//        return 0;
//    }
//
//    ShowWindow(hwnd, nCmdShow);
//
//    // Run the message loop.
//
//    MSG msg = { };
//    while (GetMessage(&msg, NULL, 0, 0) > 0)
//    {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//
//    return 0;
//}
//
//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{
//    switch (uMsg)
//    {
//
//        case WM_CREATE:
//            SetTimer(hwnd, idTimer = 1, 1, NULL);
//            return 0;
//        
//        case WM_DESTROY:
//            KillTimer(hwnd, idTimer);
//            PostQuitMessage(0);
//            return 0;
//        
//        case WM_TIMER:
//            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
//            return 0;
//
//        case WM_PAINT:
//            {
//
//                PAINTSTRUCT ps;
//                mainDeviceContext = BeginPaint(hwnd, &ps);
//        
//                std::ifstream file("C:\\Users\\wchapron\\Documents\\GitHub\\SteganographyTraining\\loadBitmap.bmp", std::ios::binary);
//                if (!file) {
//                    MessageBox(NULL, L"Erreur lors de l'ouverture du fichier BMP", L"Erreur", MB_OK);
//                    return 0;
//                }
//        
//                file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
//                if (fileHeader.bfType != 0x4D42) {
//                    MessageBox(NULL, L"Erreur! Format de fichier non reconnu.", L"Erreur", MB_OK);
//                    return 0;
//                }
//        
//                file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
//                if (infoHeader.biBitCount != 24) {
//                    MessageBox(NULL, L"Erreur! Seuls les fichiers BMP 24 bits sont supportés.", L"Erreur", MB_OK);
//                    return 0;
//                }
//        
//                int row_padded = (infoHeader.biWidth * 3);
//                pixels = new uint8_t[row_padded * infoHeader.biHeight];
//        
//                file.read(reinterpret_cast<char*>(pixels), row_padded * infoHeader.biHeight);
//                file.close();
//        
//                if (currentPixelIndex < infoHeader.biWidth * infoHeader.biHeight)
//                {
//                    int width = infoHeader.biWidth;
//                    int height = infoHeader.biHeight;
//
//                    // Affichez jusqu'à 100 pixels à la fois
//                    for (int i = 0; i < 1000 && currentPixelIndex < (width * height); i++, currentPixelIndex++)
//                    {
//                        int pixelY = currentPixelIndex / width;
//                        int pixelX = currentPixelIndex % width;
//
//                        int pixelIndex = (pixelY * width + pixelX) * 3;
//
//                        COLORREF color = RGB(pixels[pixelIndex + 2], pixels[pixelIndex + 1], pixels[pixelIndex]);
//
//
//                        SetPixel(mainDeviceContext, pixelX, (height - pixelY - 1), color);
//                    }
//                }
//        
//                EndPaint(hwnd, &ps);
//                return 0;
//            }
//    return 0;
//
//    }
//    return DefWindowProc(hwnd, uMsg, wParam, lParam);
//}
//
//
//
