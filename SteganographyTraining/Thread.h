#include <windows.h>
#include <iostream>

// Assurez-vous que cette ligne est incluse avant la définition de la classe
#pragma once

// Déclaration de la classe ClientApp
class ClientApp;


template<typename MethodType, typename InstanceType>
struct ThreadData {
    MethodType method;           // Pointeur vers la méthode membre
    InstanceType* instance;      // Pointeur vers l'instance de la classe
};

// Classe Thread
class Thread {
public:

    template<typename InstanceType, typename MethodType>
    static DWORD WINAPI StaticThreadFunction(LPVOID lpParam) {
        auto* data = reinterpret_cast<ThreadData<MethodType, InstanceType>*>(lpParam);
        (data->instance->*(data->method))(); 
        delete data; 
        return 0;
    }

    template<typename InstanceType, typename MethodType>
    HANDLE Init(InstanceType* instance, MethodType method) {
        auto* threadData = new ThreadData<MethodType, InstanceType>{ method, instance };

        // Créer le thread
        HANDLE threadHandle = CreateThread(
            NULL,
            0,
            StaticThreadFunction<InstanceType, MethodType>,
            threadData,
            0,
            NULL
        );

        if (threadHandle == NULL) {
            std::cerr << "Erreur lors de la création du thread" << std::endl;
            delete threadData; // Libérer la mémoire en cas d'erreur
            return NULL;
        }

        return threadHandle; // Retourner le handle du thread
    }

    HANDLE m_handle; // Gérer le handle du thread si nécessaire
};
