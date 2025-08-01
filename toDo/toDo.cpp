#include "toDo.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
int N_TAREA = 1;

struct Node {
    int id = N_TAREA;
    string description;
    bool status = false;
    string dateCreated;
    Node *next;

};

struct List {
    Node *head = nullptr;
};

int main(){
    List * toDoList = new List();
    runToDo(toDoList);
    return 0;
}


void mainMenu(){
    cout << "*****LISTA DE TAREAS PENDIENTES *********" <<endl;
    cout << "1. Agregar una tarea a la lista" <<endl;
    cout << "2. Eliminar una tarea por ID" <<endl;
    cout << "3. Buscar tareas con palabra clave" <<endl;
    cout << "4. Marcar tarea como completada" <<endl;
    cout << "5. Mostrar todas las tareas" <<endl; 
    cout << "6. Vaciar la lista" <<endl;
    cout << "7. Cargar tareas desde archivo" <<endl;  
    cout << "8. Volver al menu principal" <<endl;
    cout << "Ingrese una opcion: ";

}

void emptyList(List *list){
    Node * current = list->head;
    Node * temp;
    while(current != nullptr){
        temp = current;
        current = current->next;
        delete temp;
         

    }
    list->head = nullptr;
    cout << "La lista ha sido vaciada correctamente." << endl;
    cout << "PRESIONE UNA TECLA PARA CONTINUAR...."<< endl;
    cin.get();

}


void addTask(List *& list, string description){

    Node* toAdd = new Node();
    toAdd->description = description;
    string currentTime = getTimeCustom();
    toAdd->dateCreated = currentTime;
    toAdd->next = nullptr;

    // FIRST ELEMENT ADDED
    if(list->head == nullptr){
        list->head = toAdd;
    }else{
         // ITERATE IN ALL THE LINKED LIST UNTIL FIND AND SPACE.
        Node* current = list->head;
        while(current->next != nullptr){
        current = current->next;
    }

    current->next = toAdd;
    }

    N_TAREA++;
    
    cout << "Tarea añadida con exito!!" <<endl;
    cout << "Lista de tareas en la lista: " << endl;
    showTasks(list);
    cout << "PRESIONE UNA TECLA PARA CONTINUAR...."<< endl;
    cin.get();

}

void deleteTask(List *& list, int ID){
    Node* current = list->head;
    Node* previous = nullptr;
    char confirmation;
    
    while (current != nullptr){
        if(current->id = ID){
            cout << "DESCRIPCIÓN DE LA TAREA A ELIMINAR:\n";
            cout << current->description << endl;
            cout << "CREADA EL: " << current->dateCreated << endl;
            cout << "¿Desea eliminar esta tarea? [Y/n]: ";
            cin >> confirmation;
            if(confirmation != 'n'){
                // first node to eliminate is the head
                if(previous == nullptr){
                    list->head = current->next;
                }else{
                    previous->next = current->next;
                }
                delete current;
                
            }else{
                 cout << "Eliminación cancelada. Presione una tecla para continuar..." << endl;
                cin.ignore(); cin.get();
            }
            cout << "TAREA ELIMINADA CON EXITO" << endl;
            cout << "PRESIONE UNA TECLA PARA CONTINUAR...." << endl;
            cin.get();
            
            return;
        }
        previous = current;
        current = current->next;
        
    }
    cout << "LA TAREA CON ESE ID NO EXISTE" << endl;

}

string getTimeCustom() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    ostringstream oss;
    oss <<setfill('0')
        <<setw(2) << localTime->tm_mday << "/"
        <<setw(2) << (localTime->tm_mon + 1) << "/"
        << (localTime->tm_year + 1900)
        << " -> "
        <<setw(2) << localTime->tm_hour << ":"
        <<setw(2) << localTime->tm_min;

    return oss.str();
}

void showTasks(List *&list){
    Node *aux = list->head;
    while(aux != nullptr){
        if(aux->status){
            cout << "TAREAS COMPLETADAS: " <<endl;    
        }else{
            cout << "TAREAS PENDIENTES: " <<endl;  
        }
        cout << "ID DE TAREA: " << aux->id <<endl;
        cout << "DESCRIPCION: " << aux->description << endl;
        cout << "AGREGADA EL: "  << aux ->dateCreated <<endl;
        cout << "------------------------------------" << endl;
        aux = aux->next;
    }
}

void runToDo(List *&list){
    int option = -1;
    string description;
    int id;
    char confirmation;
    while (option < 0 || option > 8){
        mainMenu();
        cin >> option;
        switch (option)
        {
        case 1:
            
            option = -1;
            cout << "Ingrese la descripcion de la tarea: " << endl;
            cin.ignore();
            getline(cin,description);
            addTask(list,description);
            option = -1;
            break;
        case 2:
            cout << "Ingrese el id de la tarea a eliminar (puede ver todas las tareas en la opcion 5)" <<endl;
            cin >> id;
            deleteTask(list,id);
            option = -1;
            break;
        case 3:
            cout << "STILL BEING DEVELOPED" <<endl;
            option = -1;
            break;
        case 4:
            cout << "STILL BEING DEVELOPED" <<endl;
            option = -1;
            break;
        case 5:
            showTasks(list);
            option = -1;
            break;
        case 6:
            cout << "Se eliminaran todas las tareas de la lista , seguro quiere continuar? [Y/n]" << endl;
            cin >> confirmation;
            if(confirmation != 'n' || confirmation != 'N'){
                emptyList(list);
            }else{
                cout << "Operacion cancelada... Presione una tecla para continuar" << endl;
                cin.get();
            }
            cout << "STILL BEING DEVELOPED" <<endl;
            option = -1;
            break;
        case 7:
            cout << "STILL BEING DEVELOPED" <<endl;
            option = -1;
            break;
        default:
            break;
        }
    }
}