#include <iostream>

#include "ClientApp.h"
#include "Window.h"
#include "UIManager.h"

ClientApp::ClientApp() {
}


ClientApp::~ClientApp() {
}

bool ClientApp::Initialize(HINSTANCE hInstance) {

    AllocConsole();
    m_pWindow = new Window(hInstance, this);
    m_pUIManager = new UIManager(hInstance);

    return true;
}