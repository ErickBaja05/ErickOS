//
// Created by User on 12/8/2025.
//
#include <iostream>
#include "toDo/toDo.h"
#include "notesApp/notesApp.h"
#include "bankSimulatorApp/bankSimulatorApp.h"
#include "musicApp/musicApp.h"

void run(TaskList * list, NoteStack * stack, ClientQueue* queue, PlayList * playlist);
void mainMenu();

int main(){
    TaskList * toDoList = new TaskList();
    NoteStack * notesStack = new NoteStack();
    ClientQueue * clientQueue = new ClientQueue();
    PlayList * playlist = new PlayList();
    run(toDoList,notesStack, clientQueue,playlist);
}

void mainMenu(){
    std::cout << "*******BIENVENIDO A ERICKOS******" << std::endl;
    std::cout << "1. toDo list (LinkedList)" << std::endl;
    std::cout << "2. Notes App (STACK)" << std::endl;
    std::cout << "3. Bank Simulator App (QUEUE)" << std::endl;
    std::cout << "4. Music Playlist APP (DOUBLY CIRCULAR LINKED LIST)" << std::endl;
    std::cout << "5. Proyecto 5" << std::endl;
    std::cout << "6. Salir" << std::endl;
    std::cout << "Ingrese una opcion: " << std::endl;

}

void run(TaskList * list, NoteStack * stack, ClientQueue* queue, PlayList * playlist) {

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
                runToDo(list);
                option = -1;
                break;
            case 2:
                runNotesApp(stack);
                option = -1;
                break;
            case 3:
                runBankApp(queue);
                option = -1;
                break;
            case 4:
                runMusicApp(playlist);
                option = -1;
                break;
            case 5:
                std::cout << "AUN EN DESAROLLO" << std::endl;
                option = -1;
                break;
            case 6:
                std::cout << "GRACIAS POR USAR ERICK OS - ERICK BAJANA 2025" << std::endl;
                delete list;
                delete stack;
                delete queue;
                delete playlist;
                break;
            default:
                std::cout << "Opcion invalida." << std::endl;
                option = -1;
                break;
        }


    }
}
