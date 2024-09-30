#pragma once

#include <windows.h>
#include <vector>

class UIElement;
class UIButton;
class UITextField;

const int MAX_ELEMENTS = 100; 

class UIManager {
public:
    UIManager(HINSTANCE hInstance);
    ~UIManager();

    UIButton* CreateButton(HWND parentHwnd, int id, int x, int y, int width, int height);
    UITextField* CreateTextField(HWND parentHwnd, int id, int x, int y, int width, int height);

    HWND GetHWND(int id) const; 

    UIElement** GetAllElements() {
        return m_pElements; 
    }


private:
    HINSTANCE hInstance;
    UIElement* m_pElements[MAX_ELEMENTS];
    int elementCount;  
};
