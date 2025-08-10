
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "toDo.h"


int N_TASK = 1;

struct Node {
    int id = N_TASK;
    std::string description;
    bool status = false;
    std::string dateCreated;
    Node *next = nullptr;

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
    std::cout << "*****LISTA DE TAREAS PENDIENTES *********" <<std::endl;
    std::cout << "1. Agregar una tarea a la lista" <<std::endl;
    std:: cout <<"2. Eliminar una tarea por ID" <<std::endl;
    std::cout << "3. Buscar tareas con palabra clave" <<std::endl;
    std::cout << "4. Marcar tarea como completada" <<std::endl;
    std::cout << "5. Mostrar todas las tareas" <<std::endl; 
    std::cout << "6. Vaciar la lista" <<std::endl;
    std::cout << "7. Guardar y volver al menu principal" <<std::endl;
    std::cout << "Ingrese una opcion: ";

}
void addTask(List *& list, std::string description){

    Node* toAdd = new Node();
    toAdd->description = description;
    std::string currentTime = getTimeCustom();
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

    N_TASK++;
    
    std::cout << "Tarea añadida con exito!!" <<std::endl;
    std::cout << "Lista de tareas en la lista: " << std::endl;
    showTasks(list);
    std::cout << "PRESIONE UNA TECLA PARA CONTINUAR...."<< std::endl;
    std::cin.get();

}

void deleteTask(List *& list, int ID){
    Node* current = list->head;
    Node* previous = nullptr;
    char confirmation;
    
    while (current != nullptr){
        if(current->id == ID){
            std::cout << "DESCRIPCIÓN DE LA TAREA A ELIMINAR:\n";
            std::cout << current->description << std::endl;
            std::cout << "CREADA EL: " << current->dateCreated << std::endl;
            std::cout << "¿Desea eliminar esta tarea? [Y/n]: ";
            std::cin >> confirmation;
            if(confirmation == 'y' || confirmation =='Y'){
                // first node to eliminate is the head
                if(previous == nullptr){
                    list->head = current->next;
                }else{
                    previous->next= current->next;

                }
                delete current;
                
            }else{
                std::cout << "Eliminación cancelada. Presione una tecla para continuar..." << std::endl;
                std::cin.get();
                return;
            }
            std::cout << "TAREA ELIMINADA CON EXITO" << std::endl;
            std::cout << "PRESIONE UNA TECLA PARA CONTINUAR...." << std::endl;
            std::cin.get();
            
            return;
        }
        previous = current;
        current = current->next;
        
    }
    std::cout << "LA TAREA CON ESE ID NO EXISTE" << std::endl;

}

void lookForTask(List *list, std::string &keyword){
    Node* current = list->head;
    bool founded = false;
    std::cout << "TAREAS QUE CONTIENEN: \" " << keyword << "\":" << std::endl;
    std::string keywordUpper = keyword;
    std::transform(keywordUpper.begin(), keywordUpper.end(), keywordUpper.begin(), ::toupper);
    while(current!= nullptr){
       
        std::string descUpper = current->description;
        std::transform(descUpper.begin(), descUpper.end(), descUpper.begin(), ::toupper);
        if(descUpper.find(keywordUpper) != std::string::npos){
            founded = true;
            if(current->status){
            std::cout << "ESTADO: COMPLETADA!!!" <<std::endl;    
        }else{
            std::cout << "ESTADO: PENDIENTE****" <<std::endl;  
        }
        std::cout << "ID DE TAREA: " << current->id <<std::endl;
        std::cout << "DESCRIPCION: " << current->description << std::endl;
        std::cout << "AGREGADA EL: "  << current ->dateCreated <<std::endl;
        std::cout << "------------------------------------" << std::endl;
        
        }
        current = current->next;
    } 
    if(!founded){
        std::cout << "NO HAY TAREAS QUE CONTENGAN LA PALABRA CLAVE: \"" <<keyword <<"\"" << std::endl;
    }

}

void completeTask(List *&list, int id){
    
    Node* current = list->head;
    Node* previous = nullptr;
  
    while (current != nullptr){
        if(current->id == id){
            current->status = true;  
            std::cout << "TAREA MARCADA COMO COMPLETADA" << std::endl;
            std::cout << "PRESIONE UNA TECLA PARA CONTINUAR...." << std::endl;
            std::cin.get();
            return;
        }
        previous = current;
        current = current->next;
        
    }
    std::cout << "LA TAREA CON ESE ID NO EXISTE" << std::endl;


}

void showTasks(List *&list){
    if(list->head == nullptr){
        std::cout << " LA LISTA ESTA VACIA " << std::endl;
        std::cout << "PRESIONE CUALQUIER TECLA PARA CONTINUAR..." << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }
    Node *aux = list->head;
    while(aux != nullptr){
        if(aux->status){
            std::cout << "ESTADO: COMPLETADA!!!" <<std::endl;    
        }else{
            std::cout << "ESTADO: PENDIENTE****" <<std::endl;  
        }
        std::cout << "ID DE TAREA: " << aux->id <<std::endl;
        std::cout << "DESCRIPCION: " << aux->description << std::endl;
        std::cout << "AGREGADA EL: "  << aux ->dateCreated <<std::endl;
        std::cout << "------------------------------------" << std::endl;
        aux = aux->next;
    }
}

void emptyList(List *&list){
    Node * current = list->head;
    Node * temp;
    while(current != nullptr){
        temp = current;
        current = current->next;
        delete temp;
         

    }
    list->head = nullptr;
    std::cout << "La lista ha sido vaciada correctamente." << std::endl;
    std::cout << "PRESIONE UNA TECLA PARA CONTINUAR...."<< std::endl;
    std::cin.get();

}



std::string getTimeCustom() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    std::ostringstream oss;
    oss << std::setfill('0')
        << std::setw(2) << localTime->tm_mday << "/"
        << std::setw(2) << (localTime->tm_mon + 1) << "/"
        << (localTime->tm_year + 1900)
        << " -> "
        << std::setw(2) << localTime->tm_hour << ":"
        << std::setw(2) << localTime->tm_min;

    return oss.str();
}



void runToDo(List *&list){
    int option = -1;
    std::string description;
    int id;
    char confirmation;
    while (option < 0 || option > 8){
        mainMenu();
        std::cin >> option;
        switch (option)
        {
        case 1:
            
            option = -1;
            std::cout << "Ingrese la descripcion de la tarea: " << std::endl;
            std::cin.ignore();
            getline(std::cin,description);
            addTask(list,description);
            option = -1;
            break;
        case 2:
            std::cout << "Ingrese el id de la tarea a eliminar (puede ver todas las tareas en la opcion 5)" <<std::endl;
            std::cin >> id;
            deleteTask(list,id);
            option = -1;
            break;
        case 3:
            std::cout << "Ingrese la descripcion de la tarea o una palabra clave para recuperar varias:" <<std::endl;
            std::cin.ignore();
            std::getline(std::cin,description);
            lookForTask(list,description);
            option = -1;
            break;
        case 4:
            std::cout << "Ingrese el ID de la tarea que ha finalizado: (puede ver todas las tareas en la opcion 5) " << std::endl;
            std::cin >> id;
            completeTask(list,id);
            option = -1;
            break;
        case 5:
            showTasks(list);
            option = -1;
            break;
        case 6:
            std::cout << "Se eliminaran todas las tareas de la lista , seguro quiere continuar? [Y/n]" << std::endl;
            std::cin >> confirmation;
            if(confirmation == 'y' || confirmation == 'Y'){
                emptyList(list);
            }else{
                std::cout << "Operacion cancelada... Presione una tecla para continuar" << std::endl;
                std::cin.get();
            }
            option = -1;
            break;
        case 7:
            std::cout << "STILL BEING DEVELOPED" <<std::endl;
            option = -1;
            break;
        default:
            break;
        }
    }
}