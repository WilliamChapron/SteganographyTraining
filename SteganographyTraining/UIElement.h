#pragma once

#include <windows.h>

enum class UIElementType {
    Button,
    TextField,
};

class UIElement {
public:
    UIElement(HINSTANCE hInstance, int id, UIElementType type);
    virtual ~UIElement();

    virtual void Create(HWND parentHwnd, int x, int y, int width, int height) = 0;

    inline HWND GetHWND() const { return hwnd; } 
    inline int GetID() const { return id; }     

    UIElementType GetType() const;

protected:
    HWND hwnd;
    HINSTANCE hInstance;
    int id;
    UIElementType type;
};

class UIButton : public UIElement {
public:
    UIButton(HINSTANCE hInstance, int id);
    void Create(HWND parentHwnd, int x, int y, int width, int height) override;
};

class UITextField : public UIElement {
public:
    UITextField(HINSTANCE hInstance, int id);
    void Create(HWND parentHwnd, int x, int y, int width, int height) override;
};