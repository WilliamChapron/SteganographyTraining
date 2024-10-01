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
    
    HWND hwndWindowI = clientApp->GetWindow()->GetHWND();
    UIManager* uiManagerI = clientApp->GetUIManager();


    COLORREF buttonColor = RGB(0, 120, 215);  // Exemple de couleur pour le bouton
    std::string buttonText = "Cliquez ici";   // Texte pour le bouton

    UIButton* button = uiManagerI->CreateButton(hwndWindowI, 1, 200, 200, 100, 30, buttonColor, buttonText);

    COLORREF textFieldColor = RGB(155, 255, 255); // Exemple de couleur pour le champ de texte
    std::string textFieldText = "Entrez du texte"; // Texte pour le champ de texte

    UITextField* textField = uiManagerI->CreateTextField(hwndWindowI, 2, 50, 100, 200, 30, textFieldColor, textFieldText);
 


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

