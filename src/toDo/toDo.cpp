
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "toDo/toDo.h"


int N_TASK = 1;


void menuToDo(){
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

void addTask(TaskList *& list, std::string description){
    // CREATION OF THE NODE TO BE ADDED , DATE IS STORED JUST AFTER THAT MOMENT
    TasKNode* toAdd = new TasKNode();
    toAdd->description = description;
    std::string currentTime = getTimeCustom();
    toAdd->dateCreated = currentTime;
    toAdd->next = nullptr;
    

    // FIRST ELEMENT ADDED
    if(list->head == nullptr){
        list->head = toAdd;
    }else{
         // ITERATE IN ALL THE LINKED LIST UNTIL FIND AND SPACE.
        TasKNode* current = list->head;
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

void deleteTask(TaskList *& list, int ID){
    TasKNode* current = list->head;
    TasKNode* previous = nullptr;
    char confirmation;
    
    while (current != nullptr){
        if(current->id == ID){
            std::cout << "DESCRIPCIÓN DE LA TAREA A ELIMINAR:\n";
            std::cout << current->description << std::endl;
            std::cout << "CREADA EL: " << current->dateCreated << std::endl;
            std::cout << "¿Desea eliminar esta tarea? [Y/n]: ";
            std::cin >> confirmation;
            confirmation = toupper(confirmation);
            if(confirmation != 'N'){
                // THE NODE TO ELIMINATE IS THE HEAD.
                if(previous == nullptr){
                    list->head = current->next;
                }else{
                    // TO KEEP THE LINKED FORMAT AVOIDING THE NODE TO BE DELETED
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

void lookForTask(TaskList *list, std::string &keyword){
    TasKNode* current = list->head;
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
            std::cout << "ESTADO: ******PENDIENTE****" <<std::endl;  
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

void completeTask(TaskList *&list, int id){
    
    TasKNode* current = list->head;
    TasKNode* previous = nullptr;
  
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

void showTasks(TaskList *&list){
    if(list->head == nullptr){
        std::cout << " LA LISTA ESTA VACIA " << std::endl;
        std::cout << "PRESIONE CUALQUIER TECLA PARA CONTINUAR..." << std::endl;
        std::cin.ignore(); std::cin.get();
        return;
    }
    TasKNode *aux = list->head;
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

void emptyList(TaskList *&list){
    TasKNode * current = list->head;
    TasKNode * temp;
    while(current != nullptr){
        temp = current;
        current = current->next;
        delete temp;
         

    }
    list->head = nullptr;
    std::cout << "La lista ha sido vaciada correctamente." << std::endl;
   

}


void saveTasks(TaskList *&list){
    std::ofstream file("data/toDo/taskTodo.txt");
    if(!file){
        std::cout << "Error al abrir el archivo para guardar los datos" << std::endl;
        return;
    }

    if(list->head == nullptr){
        std::cout << " LA LISTA ESTA VACIA, NO SE GUARDA NADA " << std::endl;
        file << -1;
        std::cout << "PRESIONE CUALQUIER TECLA PARA CONTINUAR..." << std::endl;
        std::cin.get();
        return;
    }

    TasKNode *current = list->head;
    while(current != nullptr){
        if(!current->status){
             file<< current->id <<std::endl;
             file<< current->description << std::endl;
             file<< current ->dateCreated <<std::endl;
        
        }


        current = current->next;
    }
    file << -1;
    file.close();

}

void loadTasks(TaskList *&list){



    std::ifstream file("data/toDo/taskTodo.txt");

     // Verificar si el archivo está vacío
    file.peek(); 
    if (file.eof()) {
        return;
    }
    if(!file){
        std::cout << "Error al abrir el archivo para guardar los datos" << std::endl;
        return;
    }
    int id;
    int maxId = 1;
    std::string description;
    std::string creationDate;
    file >> id;
    TasKNode* last = nullptr;
    while(id != -1){
        TasKNode* newNode = new TasKNode();
        newNode->id = id;
        if(id > maxId) maxId = id;
        file.get();
        std::getline(file,description);
        newNode->description = description;
        std::getline(file,creationDate);
        newNode->dateCreated = creationDate;
        
        newNode->next = nullptr;
        if(list->head == nullptr){
            list->head = newNode;
        }else{
            last->next = newNode;    
        }
        last = newNode;
        
        file >> id;
    }
    N_TASK = ++maxId;

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



void runToDo(TaskList *&list){
    loadTasks(list);
    int option = -1;
    std::string description;
    int id;
    char confirmation;
    while (option < 0 || option > 7){
        
        menuToDo();
        std::cin >> option;
        if(option < 0 || option > 7){
            std::cout << "OPCION INVALIDA, INTENTE OTRA VEZ" << std::endl;
            std::cin.ignore();
            continue;
        }
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
            confirmation = toupper(confirmation);
            if(confirmation != 'N'){
                emptyList(list);
            }else{
                std::cout << "Operacion cancelada... Presione una tecla para continuar" << std::endl;
                std::cin.get();
            }
            option = -1;
            break;
        case 7:
            std::cout << "Las tareas pendientes se guardaran en el archivo \"taskToDo.txt\", las tareas completadas se eliminaran." <<std::endl;
            std::cout << "Guardando tareas...." << std::endl;
            saveTasks(list);
            std::cout << "TAREAS GUARDADAS CON EXITO" << std::endl;
            std::cout << "Vaciando la lista del programa... no te preocupes, tus tareas ya estan a salvo :3" << std::endl;
            emptyList(list);
            delete list;
            std::cout << "La proxima vez que inicies el programa , en la opcion 5 podras ver las tareas que te faltan por completar, hasta pronto" << std::endl;
                std::cout << "PRESIONE CUALQUIER TECLA PARA CONTINUAR....";
                std::cin.get();
            break;
        default:
            break;
        }
    }
}