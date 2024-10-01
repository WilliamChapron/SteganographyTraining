#pragma once

#include <windows.h>
#include <vector>
#include <string>

class UIElement;

class UIButton;
class UITextField;
class UICheckBox;
class UIRadioButton;
class UILabel;
class UIPanel;

const int MAX_ELEMENTS = 100; 

class UIManager {
public:
    UIManager(HINSTANCE hInstance);
    ~UIManager();

    UIButton* CreateButton(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text);
    UITextField* CreateTextField(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text);
    UICheckBox* CreateCheckBox(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text);
    UIRadioButton* CreateRadioButton(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text);
    UILabel* CreateLabel(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text);
    UIPanel* CreatePanel(HWND parentHwnd, int id, int x, int y, int width, int height, COLORREF color, const std::string& text);


    void HandleClickAtPosition(int x, int y);


    // Getter
    HWND GetHWND(int id) const; 
    inline UIElement** GetAllElements() {return m_pElements; }
    inline int GetElementsCount() { return m_elementCount;  }


private:
    HINSTANCE m_hInstance;
    UIElement* m_pElements[MAX_ELEMENTS];
    int m_elementCount;
};
