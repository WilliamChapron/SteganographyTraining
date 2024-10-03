//#include "Thread.h"
//#include "ClientApp.h"
//
//#include <windows.h>
//#include <iostream>
//
//static DWORD WINAPI Thread::StaticThreadFunction(LPVOID lpParam) {
//    ClientApp* window = reinterpret_cast<ClientApp*>(lpParam);
//}
//
//Window* window = reinterpret_cast<Window*>(lpParam);
//
//// Appeler la méthode Run() de Window
//if (window) {
//    window->Run();
//}
//
//HANDLE Thread::Init(ClientApp* clientAppInstance) {
//    HANDLE threadHandle = CreateThread(
//        NULL,                      
//        0,                         
//        Test,                       
//        NULL,              
//        0,           
//        NULL
//    );
//
//    if (threadHandle == NULL) {
//        std::cerr << "Erreur lors de la création du thread" << std::endl;
//        return NULL;
//    }
//
//    return threadHandle;
//}