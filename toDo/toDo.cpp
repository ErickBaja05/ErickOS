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

int main(){
    Node * toDoList = nullptr;
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


void addTask(Node *& list){

    Node* toAdd = new Node();
    cout << "Ingrese la descripcion de la tarea: " << endl;
    cin.ignore();
    getline(cin, toAdd->description);
    string currentTime = getTimeCustom();
    toAdd->dateCreated = currentTime;
    toAdd->next = nullptr;

    // FIRST ELEMENT ADDED
    if(list == nullptr){
        list = toAdd;
    }else{
         // ITERATE IN ALL THE LINKED LIST UNTIL FIND AND SPACE.
        Node* current = list;
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

void showTasks(Node *&list){
    Node *aux = list;
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

void runToDo(Node *&list){
    int option = -1;
    while (option < 0 || option > 8){
        mainMenu();
        cin >> option;
        switch (option)
        {
        case 1:
            addTask(list);
            option = -1;
            break;
        case 2:
            cout << "STILL BEING DEVELOPED" <<endl;
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
            cout << "STILL BEING DEVELOPED" <<endl;
            option = -1;
            break;
        case 6:
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