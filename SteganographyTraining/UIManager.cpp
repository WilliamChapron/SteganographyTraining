#include "UIManager.h"
#include "UIElement.h"


UIManager::UIManager(HINSTANCE hInstance) : hInstance(hInstance) {}

UIManager::~UIManager() {
    for (UIElement* element : m_pElements) {
        delete element; 
    }
}

UIButton* UIManager::CreateButton(HWND parentHwnd, int id, int x, int y, int width, int height) {
    UIButton* button = new UIButton(hInstance, id);
    button->Create(parentHwnd, x, y, width, height);

    if (elementCount < MAX_ELEMENTS) {
        m_pElements[elementCount] = button;  
        ++elementCount;  
    }
    return button;
}

UITextField* UIManager::CreateTextField(HWND parentHwnd, int id, int x, int y, int width, int height) {
    UITextField* textField = new UITextField(hInstance, id);
    textField->Create(parentHwnd, x, y, width, height);

    if (elementCount < MAX_ELEMENTS) {
        m_pElements[elementCount] = textField;  
        ++elementCount;  
    }
    return textField;
}

HWND UIManager::GetHWND(int id) const {
    for (UIElement* element : m_pElements) {
        if (element->GetID() == id) {
            return element->GetHWND();
        }
    }
    return NULL; 
}
