//
// Created by User on 18/8/2025.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iomanip>


#include "notesApp/notesApp.h"
#include "toDo/toDo.h"

int N_NOTE = 1;

void menuNotesApp(){
    std::cout << "***** Organizador de notas *********" <<std::endl;
    std::cout << "1. Escribir una nota" <<std::endl;
    std:: cout <<"2. Ver nota mas reciente" <<std::endl;
    std::cout << "3. Eliminar nota mas reciente" <<std::endl;
    std::cout << "4. Listar todas las notas" <<std::endl;
    std::cout << "5. Buscar nota por palabra clave" <<std::endl;
    std::cout << "6. Eliminar todas las notas" <<std::endl;
    std::cout << "7. Guardar y volver al menu principal" <<std::endl;
    std::cout << "Ingrese una opcion: ";
}

void writeNote(NodeStack *& stack) {
    NoteNode *newNote = new NoteNode();
    newNote->id = N_TASK;
    newNote->creationDate = getTimeCustom();
    std::cout << "Ingresa el contenido de la nota: " << std::endl;
    getline(std::cin,newNote->content);
    newNote->next = stack->top;
    stack->top = newNote;
    std::cout << "Nota agregada correctamente " << std::endl;

}

bool isEmpty(NodeStack *& stack) {
    return stack->top == nullptr;
}
void runNotesApp(NodeStack *& stack) {
    int op = -1;
    while (op < 0 || op > 7) {
        menuNotesApp();
        std::cin >> op;
        if (op < 0 || op > 7) {
            std::cerr << "Opcion invalida" << std::endl;
            continue;
        }
        switch (op) {
            case 1:
                std::cout << "STILL BEING DEVELOPED: " << std::endl;
                op = -1;
                break;
            case 2:
                std::cout << "STILL BEING DEVELOPED" << std::endl;
                op = -1;
                break;
            case 3:
                std::cout << "STILL BEING DEVELOPED" << std::endl;
                op = -1;
                break;
            case 4:
                std::cout << "STILL BEING DEVELOPED" << std::endl;
                op = -1;
                break;
            case 5:
                std::cout << "STILL BEING DEVELOPED" << std::endl;
                op = -1;
                break;
            case 6:
                std::cout << "STILL BEING DEVELOPED" << std::endl;
                op = -1;
                break;
            case 7:
                std::cout << "Hasta pronto" << std::endl;
                break;
            default:
                std::cout << "Opcion invalida" << std::endl;
                op = -1;
                break;

        }
    }
}

