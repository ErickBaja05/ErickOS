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
NoteNode* buildNote() {
    NoteNode *newNote = new NoteNode();
    newNote->id = N_NOTE++;
    newNote->creationDate = getTimeCustom();
    std::cout << "Ingrese la descripcion de la nota: " <<std::endl;
    std::getline(std::cin,newNote->content);
    return newNote;
}

void pushNote(NoteStack * stack, NoteNode * newNote) {
    newNote->next = stack->top;
    stack->top = newNote;

}
NoteNode* peekNote(NoteStack * stack) {
    if (isStackEmpty(stack)) {
        return nullptr;
    }
    return stack->top;

}


void popNote(NoteStack * stack) {
    if (isStackEmpty(stack)) {
        return;
    }
    NoteNode *aux = stack->top;
    stack->top = stack->top->next;
    delete aux;
}

void showNote(const NoteNode * note) {
    std::cout << "ID: " << note->id <<std::endl;
    std::cout <<"Fecha de creacion: " << note->creationDate <<std::endl;
    std::cout <<"Contenido: " << note->content << std::endl;
    std::cout <<"***********************************" <<std::endl;
}

void showStackNotes(NoteStack * stack) {
    if (isStackEmpty(stack)) {
        return;
    }
    NoteNode *current = stack->top;
    while (current != nullptr) {
        showNote(current);
        current = current->next;
    }
}


NoteStack* lookForNotes(NoteStack *stack, std::string keyword ) {
    NoteStack *auxStack = new NoteStack();
    NoteNode *current = stack->top;
    std::string keywordUpper = keyword;
    std::transform(keywordUpper.begin(), keywordUpper.end(), keywordUpper.begin(), ::toupper);
    while (current!= nullptr) {
        std::string contentUpper = current->content;
        std::transform(contentUpper.begin(), contentUpper.end(), contentUpper.begin(), ::toupper);
        if (contentUpper.find(keywordUpper) != std::string::npos) {
            NoteNode* note = new NoteNode();
            note->id = current->id;
            note->content = current->content;
            note->creationDate = current->creationDate;
            pushNote(auxStack, note);

        }
        current = current->next;
    }
    reverseStack(auxStack);
    return auxStack;

}

void emptyStack(NoteStack * stack) {
    NoteNode *current = stack->top;
    NoteNode *temp;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
    stack->top = nullptr;
}

int saveNotes(NoteStack *stack) {
    std::ofstream outFile;
    outFile.open("data/notesApp/notes.txt");
    if(!outFile){
        return 1;
    }

    if (stack->top == nullptr) {
        return 2;
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
    return 0;
}

int loadNotes(NoteStack * stack) {
    std::ifstream file("data/notesApp/notes.txt");

    if(!file){
        return 1;
    }
    // Verificar si el archivo está vacío
    file.peek();
    if (file.eof()) {
        return 2;
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
    return 0;
}

void reverseStack(NoteStack * stack) {
    if (stack->top == nullptr || stack->top->next == nullptr) {
        return;
    }

    NoteStack *reversed = new NoteStack();

   NoteNode *current = stack->top;
    while (current != nullptr) {
        NoteNode *nextNode = current->next;
        current->next = reversed->top;
        reversed->top = current;
        current = nextNode;
    }
    stack->top = reversed->top;
    delete reversed;
}

bool isStackEmpty(NoteStack * stack) {
    return stack->top == nullptr;
}
void runNotesApp(NoteStack * stack) {
    if (loadNotes(stack) == 1) {
        std::cout << "Error al abrir el archivo para recuperar los datos guardados" << std::endl;
    }
    int op = -1;
    std::string description;
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
            case 1: {
                std::cin.ignore();
                NoteNode* note = buildNote();
                pushNote(stack,note);
                std::cout << "Nota apilada correctamente" << std::endl;
                std::cout << "presione una tecla para continuar..." << std::endl;
                std::cin.get();
                op = -1;
                break;
            }

            case 2: {
                NoteNode* top = peekNote(stack);
                if (top == nullptr) {
                    std::cout << "LA PILA ESTA VACIA" <<std::endl;
                }else {
                    std::cout << "TOPE DE LA PILA:" <<std::endl;
                    showNote(top);
                }
                std::cout << "presione una tecla para continuar..." << std::endl;
                std::cin.ignore(); std::cin.get();
                op = -1;
                break;
            }
            case 3: {
                std::cin.ignore();
                NoteNode* top = peekNote(stack);
                showNote(top);
                std::cout << "Se eliminara esta nota, desea continuar? (Y/n)" <<std::endl;
                std::cin >> confirmation;
                confirmation = toupper(confirmation);
                if (confirmation != 'N') {
                    popNote(stack);
                    std::cout << "Eliminacion realizada correctamente" << std::endl;
                }else {
                    std::cout << "Eliminacion cancelada" <<std::endl;

                }
                op = -1;
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore() ;std::cin.get();
                break;
            }

            case 4:
                std::cout << "***** NOTAS APILADAS******" <<std::endl;
                showStackNotes(stack);
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore();std::cin.get();
                op = -1;
                break;
            case 5: {
                std::cin.ignore();
                std::cout << "Ingrese la palabra clave o frase para buscar coincidencias: " <<std::endl;
                std::getline(std::cin , description);
                NoteStack* auxStack = lookForNotes(stack, description);
                if (isStackEmpty(auxStack)) {
                    std::cout << "NO EXISTEN NOTAS CON LA PALABRA: " << description << std::endl;
                }else {
                    std::cout << "NOTAS QUE CONTIENEN: \"" << description << "\"EMPEZANDO DESDE LA MAS RECIENTE" <<std::endl;
                    showStackNotes(auxStack);
                    emptyStack(auxStack);
                    delete auxStack;
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.get();
                op = -1;
                break;
            }

            case 6:
                std::cin.ignore();
                std::cout << "Se eliminaran todas las notas de la pila , seguro quiere continuar? [Y/n]" << std::endl;
                std::cin >> confirmation;
                confirmation = toupper(confirmation);
                if(confirmation != 'N'){
                    emptyStack(stack);
                    std::cout << "La pila ha sido vaciada correctamente: " << std::endl;
                }else{
                    std::cout << "Operacion cancelada" << std::endl;

                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore() ; std::cin.get();
                op = -1;
                break;
            case 7:
                if (isStackEmpty(stack)) {
                    std::cout << "NO SE TIENEN NOTAS PARA GUARDAR" << std::endl;
                }else {
                    if (saveNotes(stack) == 1) {
                        std::cout << "Error al abrir el archivo para guardar los datos" << std::endl;
                    }else {
                        std::cout << "Guardando pila de notas en el archivo notas.txt..." <<std::endl;
                        std::cout << "NOTAS GUARDADAS" << std::endl;
                        std::cout << "Hasta pronto" << std::endl;
                        emptyStack(stack);
                    }
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore();std::cin.get();

                break;
            default:
                std::cout << "Opcion invalida" << std::endl;
                op = -1;
                break;

        }
    }
}

