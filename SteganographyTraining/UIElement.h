#pragma once

#include <windows.h>
#include <string>     

enum class UIElementType {
    Button,
    TextField,
    CheckBox,      
    RadioButton,   
    Label,
    Panel,
};

class UIElement {
public:
    UIElement(HINSTANCE hInstance, int id, UIElementType type, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text);
    ~UIElement();

    inline HWND GetHWND() const { return m_hwnd; }
    inline int GetID() const { return m_id; }
    inline UIElementType GetType() const { return m_type; }

    void PerformPaint(HDC hdc) {
        HBRUSH hBrush = CreateSolidBrush(m_color);
        RECT rect = { 0, 0, m_width, m_height };

        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);

        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkMode(hdc, TRANSPARENT); 

        // Dessiner le texte
        DrawTextA(hdc, m_text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        needRedraw = true;
    }

    inline int GetX() const { return m_x; }
    inline int GetY() const { return m_y; }
    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }

    inline COLORREF GetColor() const { return m_color; }
    inline std::string GetText() const { return m_text; }

    inline void SetColor(COLORREF color) { m_color = color; }
    inline void SetText(const std::string& text) { m_text = text; }

    std::wstring GetTypeAsString() const;

    bool needRedraw = true;

protected:
    HWND m_hwnd;
    HINSTANCE m_hInstance;
    int m_id;
    UIElementType m_type;
    int m_x, m_y, m_width, m_height;
    HWND m_parentHwnd;

    COLORREF m_color;
    std::string m_text;


};

class UIButton : public UIElement {
public:
    UIButton(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text);
};

class UITextField : public UIElement {
public:
    UITextField(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text);
};

class UICheckBox : public UIElement {
public:
    UICheckBox(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text);
};

class UIRadioButton : public UIElement {
public:
    UIRadioButton(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text);
};

class UILabel : public UIElement {
public:
    UILabel(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text);
};





class UIPanel : public UIElement {
public:
    UIPanel(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height, COLORREF color, const std::string& text);
};
