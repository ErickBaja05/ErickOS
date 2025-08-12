//
// Created by User on 12/8/2025.
//
#include <iostream>
#include "toDo/toDo.h"

void run(List *& toDoList);
void mainMenu();
int main(){
    List * toDoList = new List();
    run(toDoList);
}

void mainMenu(){
    std::cout << "*******BIENVENIDO A ERICKOS******" << std::endl;
    std::cout << "1. toDo list (LinkedList)" << std::endl;
    std::cout << "2. Proyecto 2" << std::endl;
    std::cout << "3. Proyecto 3" << std::endl;
    std::cout << "4. Proyecto 4" << std::endl;
    std::cout << "5. Proyecto 5" << std::endl;
    std::cout << "6. Salir" << std::endl;
    std::cout << "Ingrese una opcion: " << std::endl;

}

void run(List *& toDoList) {

    int option = -1;
    while(option < 0 || option > 6) {
        mainMenu();
        std::cin >> option;
        if (option < 0 || option > 6) {
            std::cout << "Opcion invalida intente otra vez." << std::endl;
            continue;
        }
        switch (option) {
            case 1:
                runToDo(toDoList);
                option = -1;
                break;
            case 2:
                std::cout << "AUN EN DESAROLLO" << std::endl;
                option = -1;
                break;
            case 3:
                std::cout << "AUN EN DESAROLLO" << std::endl;
                option = -1;
                break;
            case 4:
                std::cout << "AUN EN DESAROLLO" << std::endl;
                option = -1;
                break;
            case 5:
                std::cout << "AUN EN DESAROLLO" << std::endl;
                option = -1;
                break;
            case 6:
                std::cout << "GRACIAS POR USAR ERICK OS - ERICK BAJANA 2025" << std::endl;
                break;
            default:
                std::cout << "Opcion invalida." << std::endl;
                option = -1;
                break;
        }


    }
}
