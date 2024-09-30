#include "UIElement.h"

UIElement::UIElement(HINSTANCE hInstance, int id, UIElementType type, HWND parentHwnd, int x, int y, int width, int height) 
    : m_hInstance(hInstance), m_id(id), m_type(type), m_parentHwnd(parentHwnd), m_x(x), m_y(y), m_width(width), m_height(height), m_hwnd(nullptr)
{
}

UIElement::~UIElement() {
}

UIButton::UIButton(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height)
    : UIElement(hInstance, id, UIElementType::Button, parentHwnd, x, y, width, height)
{
    m_hwnd = CreateWindow(
        L"BUTTON",
        L"Button",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x, y, width, height,
        parentHwnd,
        (HMENU)m_id,
        m_hInstance,
        NULL
    );
}

UITextField::UITextField(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height)
    : UIElement(hInstance, id, UIElementType::TextField, parentHwnd, x, y, width, height)
{
    m_hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        L"EDIT",
        L"",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL,
        x, y, width, height,
        parentHwnd,
        (HMENU)m_id,
        m_hInstance,
        NULL
    );
}
