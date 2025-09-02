//
// Created by User on 1/9/2025.
//

#include <iostream>
#include "bankSimulatorApp/bankSimulatorApp.h"



int N_CLIENT = 1;

void menuBankApp(){
    std::cout << "***** Simulador de cola de banco *********" <<std::endl;
    std::cout << "1. Poner cliente a la cola" <<std::endl;
    std:: cout <<"2. Atender a un cliente" <<std::endl;
    std::cout << "3. Mostrar al siguiente cliente a atenderse" <<std::endl;
    std::cout << "4. Ver a todos los clientes" <<std::endl;
    std::cout << "5. Eliminar a todos los clientes de la cola" <<std::endl;
    std::cout << "6. Guardar y volver al menu principal" <<std::endl;
    std::cout << "Ingrese una opcion: ";
}


void runBankApp() {
    int op = -1;
    while (op < 0 || op > 6) {
        menuBankApp();
        std::cin >> op;
        if (op < 0 || op > 6) {
            std::cout << "OPCION NO VALIDA, INTENTE DE NUEVO" <<std::endl;
            continue;
        }
        switch (op) {
            case 1:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 2:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 3:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 4:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 5:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 6:
                std::cout << "HASTA PRONTO " <<std::endl;

        }

    }


}