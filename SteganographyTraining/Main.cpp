#include <iostream>
#include <fstream>
#include <windows.h>

#include "BitmapImage.h"
#include "ClientApp.h"
#include "Window.h"
#include "UIManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    ClientApp* clientApp = new ClientApp();

    // Init Window / UIManager
    if (!clientApp->Initialize(hInstance)) {
        return 1; 
    }
    
    HWND hwndWindowI = clientApp->GetWindow()->GetHWND();
    UIManager* uiManagerI = clientApp->GetUIManager();

    uiManagerI->CreateButton(hwndWindowI, 1, 200, 200, 100, 30);    
    uiManagerI->CreateTextField(hwndWindowI, 2, 50, 100, 200, 30); 
    HWND buttonHWND = uiManagerI->GetHWND(1);
    HWND textFieldHWND = uiManagerI->GetHWND(2); 


    if (buttonHWND) {
        SetWindowText(buttonHWND, L"Click Mdsdsd"); // Modifier le texte du bouton
    }

    if (textFieldHWND) {
        SetWindowText(textFieldHWND, L"Entrez du texte ici..."); // Ajouter du texte par défaut
    }


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

