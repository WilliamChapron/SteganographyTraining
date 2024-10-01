#include "UIManager.h"
#include "UIElement.h"

#include <iostream>
#include <string>

UIManager::UIManager(HINSTANCE hInstance) : m_hInstance(hInstance) {}

UIManager::~UIManager() {
    for (UIElement* element : m_pElements) {
        delete element; 
    }
}


UIButton* UIManager::CreateButton(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text) {
    UIButton* button = new UIButton(m_hInstance, id, parentHwnd, x, y, width, height, color, text);

    if (m_elementCount < MAX_ELEMENTS) {
        m_pElements[m_elementCount] = button;
        ++m_elementCount;
    }

    return button;
}


UITextField* UIManager::CreateTextField(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text) {
    UITextField* textField = new UITextField(m_hInstance, id, parentHwnd, x, y, width, height, color, text);

    if (m_elementCount < MAX_ELEMENTS) {
        m_pElements[m_elementCount] = textField;
        ++m_elementCount;
    }

    return textField;
}


UICheckBox* UIManager::CreateCheckBox(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text) {
    UICheckBox* checkBox = new UICheckBox(m_hInstance, id, parentHwnd, x, y, width, height, color, text);

    if (m_elementCount < MAX_ELEMENTS) {
        m_pElements[m_elementCount] = checkBox;
        ++m_elementCount;
    }

    return checkBox;
}


UIRadioButton* UIManager::CreateRadioButton(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text) {
    UIRadioButton* radioButton = new UIRadioButton(m_hInstance, id, parentHwnd, x, y, width, height, color, text);

    if (m_elementCount < MAX_ELEMENTS) {
        m_pElements[m_elementCount] = radioButton;
        ++m_elementCount;
    }

    return radioButton;
}

UILabel* UIManager::CreateLabel(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text) {
    UILabel* label = new UILabel(m_hInstance, id, parentHwnd, x, y, width, height, color, text);

    if (m_elementCount < MAX_ELEMENTS) {
        m_pElements[m_elementCount] = label;
        ++m_elementCount;
    }

    return label;
}

UIPanel* UIManager::CreatePanel(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text) {
    UIPanel* panel = new UIPanel(m_hInstance, id, parentHwnd, x, y, width, height, color, text);

    if (m_elementCount < MAX_ELEMENTS) {
        m_pElements[m_elementCount] = panel;
        ++m_elementCount;
    }

    return panel;
}

HWND UIManager::GetHWND(int id) const {
    for (UIElement* element : m_pElements) {
        if (element->GetID() == id) {
            return element->GetHWND();
        }
    }
    return NULL; 
}

#include <windows.h>

void UIManager::HandleClickAtPosition(int x, int y) {
    bool elementFound = false;

    for (int i = 0; i < m_elementCount; ++i) {
        UIElement* element = m_pElements[i];

        if (x >= element->GetX() && x <= element->GetX() + element->GetWidth() &&
            y >= element->GetY() && y <= element->GetY() + element->GetHeight()) {
            elementFound = true;

            MessageBox(NULL, L"Clic détecté sur l'élément UI.", L"Succès", MB_OK | MB_ICONINFORMATION);
            std::wcout << L"Clic détecté sur l'élément UI." << std::endl;
            return; 
        }
    }

    if (!elementFound) {
        MessageBox(NULL, L"Aucun élément UI détecté à cette position.", L"Erreur", MB_OK | MB_ICONERROR);
    }
}
