#include <iostream>
#include <fstream>
#include <windows.h>

#include "BitmapImage.h"
#include "ClientApp.h"
#include "Window.h"
#include "UIElement.h"
#include "UIManager.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    ClientApp* clientApp = new ClientApp();

    // Init Window / UIManager
    if (!clientApp->Initialize(hInstance)) {
        return 1;
    }

    HWND hwndWindow = clientApp->GetWindow()->GetHWND();
    UIManager* uiManager = clientApp->GetUIManager();

    // Dimensions de la fenêtre
    RECT windowRect;
    GetClientRect(hwndWindow, &windowRect);
    int windowWidth = windowRect.right;
    int windowHeight = windowRect.bottom;

    // Diviser la fenêtre en deux moitiés
    int halfWidth = windowWidth / 2;
    int panelHeight = windowHeight;

    // Couleurs et textes
    COLORREF leftPanelColor = RGB(173, 216, 230); // Light Blue
    COLORREF topRightPanelColor = RGB(240, 248, 255); // Alice Blue
    COLORREF bottomRightPanelColor = RGB(255, 239, 204); // Peach Puff
    COLORREF buttonColor = RGB(70, 130, 180); // Steel Blue
    COLORREF textFieldColor = RGB(255, 255, 255); // White
    COLORREF labelColor = RGB(25, 25, 112); // Midnight Blue
    COLORREF labelHighlightColor = RGB(255, 140, 0); // Dark Orange

    // Left
    UIPanel* leftPanel = uiManager->CreatePanel(hwndWindow, 1, 50, 20, halfWidth - 100, panelHeight - 100, leftPanelColor, "");
    UILabel* leftLabel = uiManager->CreateLabel(hwndWindow, 2, windowWidth / 6, windowHeight - 50, 200, 30, labelHighlightColor, "Decode Message");

    // Top right
    UIPanel* topRightPanel = uiManager->CreatePanel(hwndWindow, 3, halfWidth + 20, 20, halfWidth, panelHeight / 2 - 50, topRightPanelColor, "");
    UILabel* topRightTitle = uiManager->CreateLabel(hwndWindow, 4, halfWidth + 300, 50, 200, 30, labelColor, "DECODE IMAGE");
    UILabel* topRightInputFieldLabel = uiManager->CreateLabel(hwndWindow, 5, halfWidth + 300, 120, 200, 30, labelHighlightColor, "File path : ");
    UITextField* topRightInputField = uiManager->CreateTextField(hwndWindow, 6, halfWidth + 250, 150, 300, 30, textFieldColor, "");
    UIButton* buttonLoadFile = uiManager->CreateButton(hwndWindow, 7, halfWidth + 300, 200, 200, 60, buttonColor, "Load the file");

    buttonLoadFile->SetOnClickCallback([]() {
        std::wcout << "Le bouton a été cliqué !" << std::endl;
        });

    // Bottom right
    UIPanel* Panel = uiManager->CreatePanel(hwndWindow, 8, halfWidth + 20, 20 + panelHeight / 2 - 50, halfWidth, panelHeight / 2 - 50, bottomRightPanelColor, "");
    UILabel* Title = uiManager->CreateLabel(hwndWindow, 9, halfWidth + 300, panelHeight / 2, 200, 30, labelColor, "ENCODE IMAGE");
    UILabel* InputFieldLabel = uiManager->CreateLabel(hwndWindow, 10, halfWidth + 180, 70 + panelHeight / 2, 200, 30, labelHighlightColor, "Text To Encode");
    UITextField* InputField = uiManager->CreateTextField(hwndWindow, 11, halfWidth + 180, 100 + panelHeight / 2, 200, 30, textFieldColor, "");
    UILabel* inputFieldLabelOutputFile = uiManager->CreateLabel(hwndWindow, 12, halfWidth + 400, 70 + panelHeight / 2, 200, 30, labelHighlightColor, "Output file : ");
    UITextField* inputFieldOutputFile = uiManager->CreateTextField(hwndWindow, 13, halfWidth + 400, 100 + panelHeight / 2, 200, 30, textFieldColor, "");
    UIButton* bottomRightButtonEncodeFile = uiManager->CreateButton(hwndWindow, 7, halfWidth + 180, panelHeight / 2 + 160, 300, 60, buttonColor, "1. Encode file");
    UIButton* bottomRightButtonSaveFile = uiManager->CreateButton(hwndWindow, 7, halfWidth + 400, panelHeight / 2 + 160, 200, 60, buttonColor, "2. Save file");

    // Set Control WM_COMMAND active
    clientApp->isControlEventStarted = true;

    clientApp->GetWindow()->Run();

    return 0;
}



//BitmapImage image;
//if (!image.Load("C:\\Users\\wchapron\\source\\repos\\WilliamChapron\\SteganographyTraining\\bmp_test.bmp")) {
//    std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
//    return 1;
//}
//else {
//    std::cout << "Image chargée avec succès." << std::endl;
//}

//if (!image.Save("C:\\Users\\wchapron\\source\\repos\\WilliamChapron\\SteganographyTraining\\bmp_test_copy.bmp")) {
//    std::cerr << "Erreur : Impossible de sauvegarder l'image." << std::endl;
//    return 1;
//}
//else {
//    std::cout << "Image sauvegardée avec succès." << std::endl;
//}

