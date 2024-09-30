//#include <windows.h>
//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <bitset> 
//#include <cstdint>
//
//#define EMPTY_CASE 0
//#define FILL_CASE 1
//
//#define ROUND 0 
//#define CROSS 1
//
//
//const int BASE_POSITION_FILL = 1; // Starting from 1 for FILL/EMPTY (positions 1-9)
//const int BASE_POSITION_SYMBOL = 10; // Starting from 10 for CROSS/ROUND (positions 10-18)
//
//
//struct PlayerData {
//    int symbol;
//    int indexChoice;
//};
//
//bool GetBit(int32_t appStates, int basePosition) {
//    int position = basePosition - 1;
//    int32_t mask = (1 << position);
//
//    int32_t operationResult = appStates & mask; // Si le bite a la position dans app state =0, en etant comparé a 1 il donne 0, s'il est egal a 1 il donne 1, 
//
//    return operationResult;
//}
//
//
//void SetBit1(int32_t& appStates, int basePosition) {
//    int position = basePosition - 1;
//    int32_t mask = (1 << position); // 000000001 MASK DE COMPARAISON
//
//    // Si a la position du masque il y a 0 sa met 1, s'il y a 1 sa met 0 (il faut pas que sa soit ce cas)
//    appStates |= mask; // OR op
//}
//
//void SetBit0(int32_t& appStates, int basePosition) {
//    int position = basePosition - 1;
//    // Crée le masque de comparaison (a quel position on veut remplacer)
//    int32_t mask = (1 << position); 
//    //std::cout << "Mask " << std::bitset<32>(mask) << std::endl;
//
//    // Passant de 0000000000001 à 1111111111111110
//    int32_t invertedMask = ~mask; // Inverser le masque
//
//    // A l'endroit du zero, s'il y a un 1 sa va mettre un 0 car 1 & 0 avec l'op AND font 0 et nous on veut rempalcer par 0
//    appStates &= invertedMask; // Applique l'opération ET pour mettre le bit à 0
//
//}
//
//void ShowGrid(int32_t appStates, int rows, int cols) {
//
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//
//            // Show case
//            int index = (j * rows) + i;
//
//            int fillStateCase = GetBit(BASE_POSITION_FILL + index - 1, appStates);
//
//            if (fillStateCase == EMPTY_CASE) {
//                std::cout << "| " << "?" << " ";
//            }
//            else if (fillStateCase == FILL_CASE) {
//
//                int cOrRStateCase = GetBit(BASE_POSITION_SYMBOL + index - 1, appStates);
//
//
//                if (cOrRStateCase == CROSS) {
//                    std::cout << "CROSS" << std::endl;
//                    std::cout << "| " << "X" << " ";
//                }
//                else if (cOrRStateCase == ROUND) {
//                    std::cout << "ROUND" << std::endl;
//                    std::cout << "| " << "O" << " ";
//                }
//                
//            }
//            //
//
//
//        }
//        std::cout << "|" << std::endl;
//
//
//        for (int j = 0; j < cols; j++) {
//            std::cout << "-----";
//        }
//        std::cout << "-" << std::endl;
//    }
//
//}
//
//void PerformSetCase(int32_t& appStates, PlayerData& playerData) {
//    if (GetBit(BASE_POSITION_FILL + playerData.indexChoice - 1, appStates) == EMPTY_CASE) {
//
//        // Set bool Fill or Empty (Fill) in MEMORY between 10 and 18
//        // pos in MEMORY between 1 and 32
//
//        SetBit1(appStates, BASE_POSITION_FILL + playerData.indexChoice - 1);
//
//        // Set case X or O in MEMORY between 10 and 18
//
//        if (playerData.symbol == ROUND) {
//            SetBit0(appStates, BASE_POSITION_SYMBOL + playerData.indexChoice - 1);
//        }
//        if (playerData.symbol == CROSS) {
//            SetBit1(appStates, BASE_POSITION_SYMBOL + playerData.indexChoice - 1);
//        }
//    }
//    else {
//
//    }
//}
//
//void UpdateGrid(int32_t& appStates, PlayerData& player1, PlayerData& player2) {
//    std::cout << player1.indexChoice << std::endl;
//    std::cout << player2.indexChoice << std::endl;
//
//
//    PerformSetCase(appStates, player1);
//    //PerformSetCase(appStates, player2);
//
//}
//
//int main() {
//    int32_t appStates = 0;
//
//    int rows = 3;
//    int cols = 3;
//
//    PlayerData player1{ CROSS, 0 };
//    PlayerData player2{ ROUND, 0 };
//
//    ShowGrid(appStates, rows, cols);
//
//    while (true) {
//
//        std::cin >> player1.indexChoice;
//        std::cin >> player2.indexChoice;
//
//        UpdateGrid(appStates, player1, player2);
//   
//        std::cout << "APP STATE : " << std::bitset<32>(appStates) << std::endl;
//        ShowGrid(appStates, rows, cols);
//    }
//
//
//    
//
//    return 0;
//}
//
//
//
//
//
//
