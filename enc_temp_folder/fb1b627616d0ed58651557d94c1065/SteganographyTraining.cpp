#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>



bool LoadBMP(const char* filePath) {
    BITMAP bitmap;

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        MessageBox(NULL, L"Erreur lors de l'ouverture du fichier BMP", L"Erreur", MB_OK);
        return false;
    }

    BITMAPFILEHEADER fileHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

    if (fileHeader.bfType != 0x4D42) { // 'BM type'
        throw std::runtime_error("Erreur! Format de fichier non reconnu.");
    }

    BITMAPINFOHEADER infoHeader;
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

    
    // Line Size byte
    int bytesPerPixel = infoHeader.biBitCount / 8;
    int row_padded = (infoHeader.biWidth * 3);

    uint8_t* pixels = new uint8_t[row_padded * infoHeader.biHeight];
    file.read(reinterpret_cast<char*>(pixels), row_padded * infoHeader.biHeight);


    // 3 Byte
    if (infoHeader.biBitCount != 24) {
        throw std::runtime_error("Erreur! Seuls les fichiers BMP 24 bits sont supportés.");
    }


    //// Log
    //int i = 0;
    //for (int y = 0; y < infoHeader.biHeight; y++) {
    //    for (int x = 0; x < infoHeader.biWidth; x++) {

    //        int arrayXYIndex = y * row_padded + x * 3;

    //        uint8_t blue = pixels[arrayXYIndex];
    //        uint8_t green = pixels[arrayXYIndex + 1];
    //        uint8_t red = pixels[arrayXYIndex + 2];

    //        std::cout << "Pixel (" << x << ", " << y << "): R=" << static_cast<int>(red) << " G=" << static_cast<int>(green) << " B=" << static_cast<int>(blue) << std::endl;

    //        std::cout << ++i << std::endl;
    //    }
    //}

    //// Random Edit **
    //// Create intern seed
    //std::srand(static_cast<unsigned int>(std::time(nullptr))); 

    //for (int i = 0; i < 10; ++i) { 
    //    // Rand X/Y
    //    int x = std::rand() % infoHeader.biWidth;
    //    int y = std::rand() % infoHeader.biHeight;

    //    // Rand RGB
    //    uint8_t blue = static_cast<uint8_t>(std::rand() % 256);  
    //    uint8_t green = static_cast<uint8_t>(std::rand() % 256); 
    //    uint8_t red = static_cast<uint8_t>(std::rand() % 256);    

    //    // Calculate index
    //    int pixelIndex = y * row_padded + x * 3;

    //    // 
    //    pixels[pixelIndex] = blue;
    //    pixels[pixelIndex + 1] = green;
    //    pixels[pixelIndex + 2] = red;
    //}

    // Write
    std::ofstream outputFile("C:\\Users\\wchapron\\source\\repos\\SteganographyTraining\\mario_sortie.bmp", std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Erreur lors de la création du fichier BMP de sortie.");
    }

    outputFile.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    outputFile.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    outputFile.write(reinterpret_cast<char*>(pixels), row_padded * infoHeader.biHeight);


    return true;
}

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

    if (!LoadBMP("C:\\Users\\wchapron\\source\\repos\\SteganographyTraining\\mario.bmp")) {
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
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

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
        HDC hdc = BeginPaint(hwnd, &ps);

        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}