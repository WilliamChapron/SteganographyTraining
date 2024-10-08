#include <iostream>
#include <fstream>
#include <windows.h>
#include <algorithm> // Pour std::replace

#include "BitmapImage.h"
#include "ClientApp.h"
#include "Window.h"
#include "UIElement.h"
#include "UIManager.h"
#include "Steganography.h"

#include "Thread.h"

void OpenFileDialog(HWND hwnd, OPENFILENAME ofn)
{
    char szFile[260];
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = (LPWSTR)szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Bitmap image (.bmp)\0*.bmp";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    GetOpenFileName(&ofn);
}

std::wstring ConvertSlashesToDoubleBackslashes(const std::wstring& inputText) {
    std::string inputStr(inputText.begin(), inputText.end());
    std::string outputStr;

    for (char c : inputStr) {
        if (c == '/') {
            outputStr += '\\';
            outputStr += '\\';
        }
        else {
            outputStr += c;
        }
    }

    return std::wstring(outputStr.begin(), outputStr.end());
}




class TestClass2 {
public:
    void Execute() {
        std::cout << "TestClass2::Execute called" << std::endl;
    }
};

class TestClass1 {
public:
    void Run() {
        std::cout << "TestClass1::Run called" << std::endl;
    }
    TestClass2* testClass2 = new TestClass2; // Instance de TestClass1
};


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    ClientApp* clientApp = new ClientApp();
    OPENFILENAME ofn;

    // Init Window / UIManager
    if (!clientApp->Initialize(hInstance)) {
        return 1;
    }

    HWND hwndWindow = clientApp->GetWindow()->GetHWND();
    UIManager* uiManager = clientApp->GetUIManager();

    // Dimensions de la fen�tre
    RECT windowRect;
    GetClientRect(hwndWindow, &windowRect);
    int windowWidth = windowRect.right;
    int windowHeight = windowRect.bottom;

    // Diviser la fen�tre en deux moiti�s
    int halfWidth = windowWidth / 2;
    int panelHeight = windowHeight;

    // Couleurs et textes dans le style Tesla
    COLORREF leftPanelColor = RGB(34, 34, 34); // Gris anthracite
    COLORREF topRightPanelColor = RGB(45, 45, 48); // Gris sombre moderne
    COLORREF bottomRightPanelColor = RGB(64, 64, 64); // Gris acier
    COLORREF buttonColor = RGB(220, 20, 60); // Rouge Tesla (Crimson)
    COLORREF textFieldColor = RGB(245, 245, 245); // Blanc glac�
    COLORREF labelColor = RGB(255, 255, 255); // Blanc pur pour un contraste net
    COLORREF labelHighlightColor = RGB(255, 69, 0); // Rouge vif (Orange Red) pour les �l�ments mis en �vidence


    // Left
    UIPanel* leftPanel = uiManager->CreatePanel(hwndWindow, 1, 50, 90, halfWidth - 100, panelHeight - 200, leftPanelColor, "");
    UITextField* leftLabel = uiManager->CreateTextField(hwndWindow, 2, windowWidth / 6 - 100, windowHeight - 100, 300, 60, RGB(255,255,255), "Decode Message : No message ", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_AUTOVSCROLL, true);

    // Top right
    UIPanel* topRightPanel = uiManager->CreatePanel(hwndWindow, 3, halfWidth + 20, 50, halfWidth, panelHeight / 2 - 100, topRightPanelColor, "");
    UILabel* topRightTitle = uiManager->CreateLabel(hwndWindow, 4, halfWidth + 300, 50, 200, 30, RGB(0, 0, 0), "DECODE IMAGE");
    UILabel* topRightInputFieldLabel = uiManager->CreateLabel(hwndWindow, 5, halfWidth + 300, 120, 200, 30, topRightPanelColor, "File path : ");
    UITextField* topRightInputField = uiManager->CreateTextField(hwndWindow, 6, halfWidth + 250, 150, 300, 30, textFieldColor, "");
    UIButton* buttonLoadFile = uiManager->CreateButton(hwndWindow, 7, halfWidth + 300, 200, 200, 60, buttonColor, "Load the file");



    // Bottom right
    UIPanel* Panel = uiManager->CreatePanel(hwndWindow, 8, halfWidth + 20, panelHeight / 2, halfWidth, panelHeight / 2 - 100, bottomRightPanelColor, "");
    UILabel* Title = uiManager->CreateLabel(hwndWindow, 9, halfWidth + 300, panelHeight / 2, 200, 30, RGB(0, 0, 0), "ENCODE IMAGE");
    UILabel* InputFieldLabel = uiManager->CreateLabel(hwndWindow, 10, halfWidth + 130, 70 + panelHeight / 2, 200, 30, bottomRightPanelColor, "Text To Encode :");
    UITextField* InputField = uiManager->CreateTextField(hwndWindow, 11, halfWidth + 180, 100 + panelHeight / 2, 200, 30, textFieldColor, "");
    UILabel* inputFieldLabelOutputFile = uiManager->CreateLabel(hwndWindow, 12, halfWidth + 340, 70 + panelHeight / 2, 200, 30, bottomRightPanelColor, "Output file : ");
    UITextField* inputFieldOutputFile = uiManager->CreateTextField(hwndWindow, 13, halfWidth + 400, 100 + panelHeight / 2, 200, 30, textFieldColor, "");
    UIButton* bottomRightButtonEncodeFile = uiManager->CreateButton(hwndWindow, 14, halfWidth + 180, panelHeight / 2 + 160, 200, 60, buttonColor, "1. Encode file");
    UIButton* bottomRightButtonSaveFile = uiManager->CreateButton(hwndWindow, 15, halfWidth + 400, panelHeight / 2 + 160, 200, 60, buttonColor, "2. Save file");


    // Apply Interactions To button
    {
        // Load File Btn
        buttonLoadFile->SetOnClickCallback([clientApp, hwndWindow, halfWidth, ofn]() {
            std::wstring inputText = clientApp->GetUIManager()->GetText(hwndWindow, 6);

            if (!inputText.empty()) {
                inputText = ConvertSlashesToDoubleBackslashes(inputText);
                MessageBox(hwndWindow, inputText.c_str(), L"Input Text", MB_OK);
            }

            clientApp->m_bitmapImgLoader = new BitmapImage();
            //OpenFileDialog(hwndWindow, ofn);
            //if (clientApp->m_bitmapImgLoader->loadFile((const char *)ofn.lpstrFile)) {
            //    InvalidateRect(hwndWindow, NULL, TRUE); // Demande un redessin
            //    clientApp->GetUIManager()->CreateButtonWithTimer(hwndWindow, halfWidth + 330, 250, 200, 30, L"Image Uploaded Successfully");
            //}
            clientApp->GetUIManager()->CreateButtonWithTimer(hwndWindow, halfWidth + 330, 250, 200, 30, L"Image Uploaded Successfully");

            clientApp->m_bitmapImgLoader->loadFile("C:\\Users\\wchapron\\Documents\\GitHub\\SteganographyTraining\\mario.bmp");

            // Show encoded message if available
            
            //clientApp->GetUIManager()->SetText(hwndWindow, 2, (wchar_t*)Steganography::Decode(clientApp->m_bitmapImgLoader));
            //std::cout << Steganography::decode(clientApp->m_bitmapImgLoader);
            clientApp->GetUIManager()->SetText(hwndWindow, 2, L"test");


        });

        // Encode img Btn
        bottomRightButtonEncodeFile->SetOnClickCallback([clientApp, hwndWindow, halfWidth, panelHeight]() {
            std::wstring inputText = clientApp->GetUIManager()->GetText(hwndWindow, 14);
            if (!inputText.empty()) {
                inputText = ConvertSlashesToDoubleBackslashes(inputText);
                //MessageBox(hwndWindow, inputText.c_str(), L"Input Text", MB_OK);
            }
            clientApp->GetUIManager()->CreateButtonWithTimer(hwndWindow, halfWidth + 180, 240 + panelHeight / 2 - 20, 200, 30, L"Image Encoded Successfully");
            });




        // Save File btn
        bottomRightButtonSaveFile->SetOnClickCallback([clientApp, hwndWindow, halfWidth, panelHeight]() {
            std::wstring inputText = clientApp->GetUIManager()->GetText(hwndWindow, 14);
            if (!inputText.empty()) {
                inputText = ConvertSlashesToDoubleBackslashes(inputText);
                //MessageBox(hwndWindow, inputText.c_str(), L"Input Text", MB_OK);
            }
            clientApp->GetUIManager()->CreateButtonWithTimer(hwndWindow, halfWidth + 400, 240 + panelHeight / 2 - 20, 200, 30, L"Image Saved Successfully");
            });


        

    }
    

    // Set Control WM_COMMAND active
    clientApp->isControlEventStarted = true;


    TestClass1 testClass1;

    Thread thread;

    HANDLE threadHandle = thread.Init(testClass1.testClass2, &TestClass2::Execute);

    WaitForSingleObject(threadHandle, INFINITE);

    CloseHandle(threadHandle);

    clientApp->GetWindow()->Run();

    return 0;
}



//BitmapImage image;
//if (!image.Load("C:\\Users\\wchapron\\source\\repos\\WilliamChapron\\SteganographyTraining\\bmp_test.bmp")) {
//    std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
//    return 1;
//}
//else {
//    std::cout << "Image charg�e avec succ�s." << std::endl;
//}

//if (!image.Save("C:\\Users\\wchapron\\source\\repos\\WilliamChapron\\SteganographyTraining\\bmp_test_copy.bmp")) {
//    std::cerr << "Erreur : Impossible de sauvegarder l'image." << std::endl;
//    return 1;
//}
//else {
//    std::cout << "Image sauvegard�e avec succ�s." << std::endl;
//}

