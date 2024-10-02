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
    COLORREF panelColor = RGB(200, 240, 240);
    COLORREF panel2Color = RGB(200, 140, 140);
    COLORREF buttonColor = RGB(0, 120, 215);

    UIPanel* leftPanel = uiManager->CreatePanel(hwndWindow, 1, 0, 0, halfWidth, panelHeight, panelColor, "");
    UILabel* leftLabel = uiManager->CreateLabel(hwndWindow, 2, 20, 50, 200, 30, RGB(0, 0, 0), "Nom:");

    // Champ de texte pour le premier panel
    UITextField* leftTextField = uiManager->CreateTextField(hwndWindow, 3, 20, 90, 200, 30, RGB(255, 255, 255), "");

    // Bouton d'envoi pour le premier panel
    UIButton* leftButton = uiManager->CreateButton(hwndWindow, 4, 20, 130, 100, 30, buttonColor, "Envoyer");
    leftButton->SetOnClickCallback([]() { MessageBox(NULL, L"Le bouton a été cliqué !", L"Notification", MB_OK);});

    // Création du deuxième panel (droite)
    UIPanel* rightPanel = uiManager->CreatePanel(hwndWindow, 5, halfWidth, 0, halfWidth, panelHeight, panel2Color, "");

    // Label pour le deuxième panel
    UILabel* rightLabel = uiManager->CreateLabel(hwndWindow, 6, halfWidth + 20, 50, 200, 30, RGB(0, 0, 0), "Prénom:");

    // Champ de texte pour le deuxième panel
    UITextField* rightTextField = uiManager->CreateTextField(hwndWindow, 7, halfWidth + 20, 90, 200, 30, RGB(255, 255, 255), "");

    // Bouton d'envoi pour le deuxième panel
    UIButton* rightButton = uiManager->CreateButton(hwndWindow, 8, halfWidth + 20, 130, 100, 30, buttonColor, "Envoyer");

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

