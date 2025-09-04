//
// Created by User on 18/8/2025.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <iomanip>
#include "notesApp/notesApp.h"
#include "utils/utils.h"

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

void pushNote(NoteStack *& stack) {

    NoteNode *newNote = new NoteNode();
    newNote->id = N_NOTE++;
    newNote->creationDate = getTimeCustom();
    std::cout << "Ingresa el contenido de la nota: " << std::endl;
    getline(std::cin,newNote->content);
    newNote->next = stack->top;
    stack->top = newNote;
    std::cout << "Nota agregada correctamente " << std::endl;

}
void peekNote(NoteStack *& stack) {
    if (isStackEmpty(stack)) {
        std::cout <<" LA PILA ESTA VACIA " <<std::endl;
        std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
        std::cin.ignore() , std::cin.get();
        return;
    }
    std::cout <<"******ULTIMA NOTA REGISTRADA *******" <<std::endl;
    std::cout << "ID: " << stack->top->id <<std::endl;
    std::cout <<"Fecha de creacion: " << stack->top->creationDate <<std::endl;
    std::cout <<"Contenido: " << stack->top->content<< std::endl;
    std::cout <<"***********************************" <<std::endl;

}

void popNote(NoteStack *& stack) {
    if (isStackEmpty(stack)) {
        std::cout <<" LA PILA ESTA VACIA " <<std::endl;
        std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
        std::cin.ignore() , std::cin.get();
        return;
    }
    char confirmation;
    peekNote(stack);
    std::cout << "Se eliminara esta nota, desea continuar? (Y/n)" <<std::endl;
    std::cin >> confirmation;
    confirmation = toupper(confirmation);
    if (confirmation != 'N') {
        NoteNode *aux = stack->top;
        stack->top = stack->top->next;
        delete aux;
        std::cout << "Eliminacion realizada correctamente" << std::endl;
        std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
        std::cin.ignore() , std::cin.get();
    }else {
        std::cout << "Eliminacin cancelada" <<std::endl;
        std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
        std::cin.ignore() , std::cin.get();
    }
}



void showStackNotes(NoteStack *& stack) {
    if (isStackEmpty(stack)) {
        std::cout <<" LA PILA ESTA VACIA " <<std::endl;
        std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
        std::cin.ignore() , std::cin.get();
        return;
    }
    std::cout << "***** NOTAS APILADAS******" <<std::endl;
    NoteNode *current = stack->top;
    while (current != nullptr) {
        std::cout << "ID: " << current->id <<std::endl;
        std::cout <<"Fecha de creacion: " << current->creationDate <<std::endl;
        std::cout <<"Contenido: " << current->content<< std::endl;
        std::cout <<"***********************************" <<std::endl;
        current = current->next;
    }
}

void lookForNote(NoteStack *& stack , std::string keyword ) {
    bool founded = false;
    NoteNode *current = stack->top;
    std::cout << "NOTAS QUE CONTIENEN LA PALABRA: \"" << keyword << "\"EMPEZANDO DESDE LA MAS RECIENTE" <<std::endl;
    std::string keywordUpper = keyword;
    std::transform(keywordUpper.begin(), keywordUpper.end(), keywordUpper.begin(), ::toupper);
    while (current!= nullptr) {
        std::string contentUpper = current->content;
        std::transform(contentUpper.begin(), contentUpper.end(), contentUpper.begin(), ::toupper);
        if (contentUpper == keywordUpper) {
            founded = true;
            std::cout << "ID: " << current->id <<std::endl;
            std::cout <<"Fecha de creacion: " << current->creationDate <<std::endl;
            std::cout <<"Contenido: " << current->content<< std::endl;
            std::cout <<"***********************************" <<std::endl;

        }
        current = current->next;
    }
    if (!founded) {
        std::cout << "NO EXISTEN NOTAS CON LA PALABRA: " << keyword << std::endl;
    }
}

void emptyStack(NoteStack *& stack) {
    NoteNode *current = stack->top;
    NoteNode *temp;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
    stack->top = nullptr;
    std::cout << "La pila ha sido vaciada correctamente: " << std::endl;
}

void saveNotes(NoteStack *& stack) {
    std::ofstream outFile;
    outFile.open("data/notesApp/notes.txt");
    if(!outFile){
        std::cout << "Error al abrir el archivo para guardar los datos" << std::endl;
        return;
    }

    if (stack->top == nullptr) {
        std::cout << "NO SE TIENEN NOTAS PARA GUARDAR" << std::endl;
        return;
    }

    NoteNode *aux = stack->top;
    while (aux != nullptr) {
        outFile << aux->id << std::endl;
        outFile << aux->creationDate << std::endl;
        outFile << aux->content << std::endl;
        aux = aux->next;
    }
    outFile << -1;
    outFile.close();

}

void loadNotes(NoteStack *& stack) {
    std::ifstream file("data/notesApp/notes.txt");

    if(!file){
        std::cout << "Error al abrir el archivo para guardar los datos" << std::endl;
        return;
    }
    // Verificar si el archivo está vacío
    file.peek();
    if (file.eof()) {
        return;
    }
    int id;
    int maxId = 1;
    std::string creationDate;
    std::string content;
    file >> id;
    while (id != -1) {
        NoteNode *newNode = new NoteNode();
        if (id > maxId) maxId = id;
        file.get();
        std::getline(file, creationDate);
        std::getline(file, content);
        newNode->id = id;
        newNode->creationDate = creationDate;
        newNode->content = content;
        newNode->next = stack->top;
        stack->top = newNode;
        file >> id;

    }


    file.close();
    reverseStack(stack);
    N_NOTE = ++ maxId;
}

void reverseStack(NoteStack *&stack) {
    if (stack == nullptr || stack->top == nullptr || stack->top->next == nullptr) {
        // Nothing to reverse if stack is empty or has only one element
        return;
    }

    NoteStack *reversed = new NoteStack(); // temporary stack

    // Pop elements from original and push into reversed
    NoteNode *current = stack->top;
    while (current != nullptr) {
        NoteNode *nextNode = current->next;  // Save the next node
        current->next = reversed->top;       // Point to top of reversed stack
        reversed->top = current;             // Move current node to reversed stack
        current = nextNode;                  // Move to next node
    }

    // Update original stack to reversed
    stack->top = reversed->top;

    delete reversed; // Free the temporary stack (not its nodes, because they were reused)
}

bool isStackEmpty(NoteStack *& stack) {
    return stack->top == nullptr;
}
void runNotesApp(NoteStack *& stack) {
    loadNotes(stack);
    int op = -1;
    std::string keyword;
    char confirmation;
    while (op < 0 || op > 7) {
        menuNotesApp();
        std::cin >> op;
        if (op < 0 || op > 7) {
            std::cout << "Opcion invalida, intente otra vez" << std::endl;
            std::cin.ignore();
            continue;
        }
        switch (op) {
            case 1:
                std::cin.ignore();
                pushNote(stack);
                op = -1;
                break;
            case 2:
                peekNote(stack);
                op = -1;
                break;
            case 3:
                popNote(stack);
                op = -1;
                break;
            case 4:
                showStackNotes(stack);
                std::cout << "STILL BEING DEVELOPED" << std::endl;
                op = -1;
                break;
            case 5:
                std::cin.ignore();
                std::cout << "Ingrese la palabra clave o frase para buscar coincidencias: " <<std::endl;
                std::getline(std::cin , keyword);
                lookForNote(stack, keyword);
                op = -1;
                break;
            case 6:
                std::cout << "Se eliminaran todas las notas de la pila , seguro quiere continuar? [Y/n]" << std::endl;
                std::cin >> confirmation;
                confirmation = toupper(confirmation);
                if(confirmation != 'N'){
                    emptyStack(stack);
                }else{
                    std::cout << "Operacion cancelada... Presione una tecla para continuar" << std::endl;
                    std::cin.ignore() , std::cin.get();
                }
                op = -1;
                break;
            case 7:
                std::cout << "Guardando pila de notas en el archivo notas.txt..." <<std::endl;
                saveNotes(stack);
                std::cout << "NOTAS GUARDADAS" << std::endl;
                std::cout << "Hasta pronto" << std::endl;
                emptyStack(stack);
                delete stack;
                break;
            default:
                std::cout << "Opcion invalida" << std::endl;
                op = -1;
                break;

        }
    }
}

