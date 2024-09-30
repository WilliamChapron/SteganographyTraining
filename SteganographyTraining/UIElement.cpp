#include "UIElement.h"


UIElement::UIElement(HINSTANCE hInstance, int id, UIElementType type) : hInstance(hInstance), id(id), type(type), hwnd(nullptr) 
{
}

UIElement::~UIElement() 
{
}

UIElementType UIElement::GetType() const {
    return type;
}

UIButton::UIButton(HINSTANCE hInstance, int id) : UIElement(hInstance, id, UIElementType::Button) 
{
}

void UIButton::Create(HWND parentHwnd, int x, int y, int width, int height) 
{
    hwnd = CreateWindow(
        L"BUTTON",
        L"Button",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x,
        y,
        width,
        height,
        parentHwnd,
        (HMENU)id,
        hInstance,
        NULL);
}

UITextField::UITextField(HINSTANCE hInstance, int id) : UIElement(hInstance, id, UIElementType::TextField) 
{
}

void UITextField::Create(HWND parentHwnd, int x, int y, int width, int height) {
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
        x,
        y,
        width,
        height,
        parentHwnd,
        (HMENU)id,
        hInstance,
        NULL);
}