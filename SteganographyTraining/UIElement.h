#pragma once

#include <windows.h>

enum class UIElementType {
    Button,
    TextField,
};

class UIElement {
public:
    UIElement(HINSTANCE hInstance, int id, UIElementType type, HWND parentHwnd, int x, int y, int width, int height);
    virtual ~UIElement();

    inline HWND GetHWND() const { return m_hwnd; }
    inline int GetID() const { return m_id; }
    inline UIElementType GetType() const { return m_type; }

    inline int GetX() const { return m_x; }
    inline int GetY() const { return m_y; }
    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }

protected:
    HWND m_hwnd;
    HINSTANCE m_hInstance;
    int m_id;
    UIElementType m_type;
    int m_x, m_y, m_width, m_height;  
    HWND m_parentHwnd;
};

class UIButton : public UIElement {
public:
    UIButton(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height);
};

class UITextField : public UIElement {
public:
    UITextField(HINSTANCE hInstance, int id, HWND parentHwnd, int x, int y, int width, int height);
};
