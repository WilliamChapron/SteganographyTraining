#include "UIElement.h"



UIElement::UIElement(HINSTANCE hInstance, int id, UIElementType type, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text)
    : m_hInstance(hInstance), m_id(id), m_type(type), m_parentHwnd(parentHwnd), m_x(x), m_y(y), m_width(width), m_height(height), m_hwnd(nullptr), m_color(color), m_text(text)
{
}

std::wstring UIElement::GetTypeAsString() const {
    switch (m_type) {
    case UIElementType::Button:
        return L"Button";
    case UIElementType::TextField:
        return L"TextField";
    case UIElementType::CheckBox:
        return L"CheckBox";
    case UIElementType::RadioButton:
        return L"RadioButton";
    case UIElementType::Label:
        return L"Label";
    case UIElementType::Panel:
        return L"Panel";
    default:
        return L"Unknown";
    }
}

UIButton::UIButton(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text)
    : UIElement(hInstance, id, UIElementType::Button, parentHwnd, x, y, width, height, color, text)
{
    m_hwnd = CreateWindow(
        L"BUTTON",
        std::wstring(text.begin(), text.end()).c_str(),
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        x, y, width, height,
        parentHwnd,
        (HMENU)m_id,
        m_hInstance,
        NULL
    );



    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);  // Stocke l'instance de la classe
}



UITextField::UITextField(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text)
    : UIElement(hInstance, id, UIElementType::TextField, parentHwnd, x, y, width, height, color, text)
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

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);  // Stocke l'instance de la classe
}

UICheckBox::UICheckBox(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text)
    : UIElement(hInstance, id, UIElementType::CheckBox, parentHwnd, x, y, width, height, color, text)
{
    m_hwnd = CreateWindow(
        L"BUTTON",
        std::wstring(text.begin(), text.end()).c_str(),
        WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
        x, y, width, height,
        parentHwnd, (HMENU)id, hInstance, NULL
    );

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);  // Stocke l'instance de la classe
}

UIRadioButton::UIRadioButton(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text)
    : UIElement(hInstance, id, UIElementType::RadioButton, parentHwnd, x, y, width, height, color, text)
{
    m_hwnd = CreateWindow(
        L"BUTTON",
        std::wstring(text.begin(), text.end()).c_str(),
        WS_VISIBLE | WS_CHILD | BS_RADIOBUTTON,
        x, y, width, height,
        parentHwnd, (HMENU)id, hInstance, NULL
    );

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);  // Stocke l'instance de la classe
}

UILabel::UILabel(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL, )
    : UIElement(hInstance, id, UIElementType::Label, parentHwnd, x, y, width, height, color, text)
{
    m_hwnd = CreateWindow(
        L"STATIC",
        std::wstring(text.begin(), text.end()).c_str(),
        WS_VISIBLE | WS_CHILD,
        x, y, width, height,
        parentHwnd, (HMENU)id, hInstance, NULL
    );

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);  // Stocke l'instance de la classe
}

UIPanel::UIPanel(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text)
    : UIElement(hInstance, id, UIElementType::Panel, parentHwnd, x, y, width, height, color, text)
{
    m_hwnd = CreateWindow(
        L"STATIC",
        NULL,
        WS_CHILD | WS_VISIBLE,
        x,
        y,
        width,
        height,
        parentHwnd,
        (HMENU)id,
        hInstance,
        NULL
    );

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, (LONG_PTR)this);
}



//#TODO Panel proc