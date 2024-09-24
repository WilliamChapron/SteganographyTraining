#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <string>

HWND test1 = nullptr;

void Additionner(HWND hwnd, HWND hEdit1, HWND hEdit2);

void Additionner(HWND hwnd, HWND hEdit1, HWND hEdit2) {
    int length1 = GetWindowTextLength(hEdit1);
    int length2 = GetWindowTextLength(hEdit2);

    wchar_t* buffer1 = new wchar_t[length1 + 1];
    wchar_t* buffer2 = new wchar_t[length2 + 1];

    GetWindowText(hEdit1, buffer1, length1 + 1);
    GetWindowText(hEdit2, buffer2, length2 + 1);

    // Convertir les chaînes en entiers
    try {
        int value1 = std::stoi(buffer1);
        int value2 = std::stoi(buffer2);
        int sum = value1 + value2; // Effectuer l'addition

        // Convertir le résultat en texte
        std::wstring result = std::to_wstring(sum);

        // Envoyer un message avec le résultat
        SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sum);
    }
    catch (const std::invalid_argument& e) {
        MessageBox(hwnd, L"Veuillez entrer des nombres valides.", L"Erreur", MB_OK | MB_ICONERROR);
    }
    catch (const std::out_of_range& e) {
        MessageBox(hwnd, L"Les nombres sont trop grands.", L"Erreur", MB_OK | MB_ICONERROR);
    }

    delete[] buffer1;
    delete[] buffer2;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_COMMAND: {
        // Vérifiez quel bouton a été cliqué
        switch (LOWORD(wParam)) {
        case 1: { // Identifiant pour le bouton 1
            HWND hEdit1 = GetDlgItem(hwnd, 3); // Champ 1
            HWND hEdit2 = GetDlgItem(hwnd, 4); // Champ 2
            Additionner(hwnd, hEdit1, hEdit2); // Appel de la fonction d'addition
            break; // Sortir de ce case
        }
        case 2: { // Identifiant pour le bouton 2
            std::cout << "Bouton 2 cliqué!" << std::endl;
            break; // Sortir de ce case
        }
        case 3: { // Identifiant pour le champ 1
            std::cout << "Champ 1 cliqué!" << std::endl;
            break; // Sortir de ce case
        }
        case 4: { // Identifiant pour le champ 2
            std::cout << "Champ 2 cliqué!" << std::endl;
            break; // Sortir de ce case
        }
        default: {
            // Si l'identifiant ne correspond à aucun des cas, vous pouvez gérer ici
            break; // Sortir du switch
        }
        }
        break; // Sortir du WM_COMMAND
    }

    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }

    case WM_SETTEXT: {
        int sum = static_cast<int>(lParam); // lParam contient la somme
        std::string result = "Somme: " + std::to_string(sum);

        SetWindowTextA(test1, result.c_str());
        break;
    }

    default: {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    }
    return 0;
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    AllocConsole();  // Crée une nouvelle console pour l'application

    // Rediriger les flux std::cout et std::cin vers la nouvelle console
    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);  // Redirige stdout vers la console
    freopen_s(&file, "CONIN$", "r", stdin);   // Redirige stdin vers la console

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SampleWindowClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        L"SampleWindowClass",
        L"Sample Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    // Créez le bouton 1
    CreateWindow(
        L"BUTTON",  // nom de la classe
        L"Bouton 1",  // texte du bouton
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles
        50,         // x position
        150,        // y position
        100,        // largeur
        30,         // hauteur
        hwnd,       // parent window
        (HMENU)1,   // identifiant du bouton 1
        NULL,
        NULL
    );

    // Créez le bouton 2
    CreateWindow(
        L"BUTTON",  // nom de la classe
        L"Bouton 2",  // texte du bouton
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles
        50,         // x position
        200,        // y position
        100,        // largeur
        30,         // hauteur
        hwnd,       // parent window
        (HMENU)2,   // identifiant du bouton 2
        NULL,
        NULL
    );

    // Créez le champ d'édition 1
    CreateWindowEx(
        0,                      // Options de style supplémentaires
        L"EDIT",                // Type de contrôle
        L"",                    // Texte initial (vide)
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, // Styles
        50,                    // Position X
        10,                    // Position Y
        200,                   // Largeur
        25,                    // Hauteur
        hwnd,                  // Handle de la fenêtre parent
        (HMENU)3,              // identifiant du champ 1
        hInstance,            // Handle de l'instance
        NULL                   // Paramètres supplémentaires
    );

    // Créez le champ d'édition 2
    CreateWindowEx(
        0,                      // Options de style supplémentaires
        L"EDIT",                // Type de contrôle
        L"",                    // Texte initial (vide)
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, // Styles
        50,                    // Position X
        100,                   // Position Y
        200,                   // Largeur
        25,                    // Hauteur
        hwnd,                  // Handle de la fenêtre parent
        (HMENU)4,              // identifiant du champ 2
        hInstance,            // Handle de l'instance
        NULL                   // Paramètres supplémentaires
    );

    test1 = CreateWindow(
        L"BUTTON",  // nom de la classe
        L"RESULTAT",  // texte du bouton
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles
        500,         // x position
        300,        // y position
        100,        // largeur
        30,         // hauteur
        hwnd,       // parent window
        (HMENU)5,   // identifiant du bouton 2
        NULL,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
