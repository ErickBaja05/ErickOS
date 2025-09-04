
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "toDo/toDo.h"

#include "bankSimulatorApp/bankSimulatorApp.h"
#include "utils/utils.h"


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

TaskNode* buildTask() {
    // CREATION OF THE NODE TO BE ADDED , DATE IS STORED JUST AFTER THAT MOMENT
    TaskNode* task = new TaskNode();
    task->id = N_TASK++;
    task->dateCreated = getTimeCustom();
    task->next = nullptr;
    std::cout << "Ingrese la descripcion de la tarea: " << std::endl;
    std::cin.ignore();
    getline(std::cin,task->description);
    return task;

}

void addTask(TaskList *& list, TaskNode* task){
    // FIRST ELEMENT ADDED
    if(isListEmpty(list)){
        list->head = task;
    }else{
         // ITERATE IN ALL THE LINKED LIST UNTIL FIND AND SPACE.
        TaskNode* current = list->head;
        while(current->next != nullptr){
        current = current->next;
    }

    current->next = task;
    }

}

bool isListEmpty(TaskList *& list) {
    return list->head == nullptr;
}

TaskNode* lookTaskId(TaskList *& list, int id) {
    TaskNode* current = list->head;
    while (current != nullptr) {
        if(current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;

}

void deleteTask(TaskList *& list, TaskNode* task) {
    if (task == nullptr) {
        return;
    }
    if (task == list->head) {
        list->head = task->next;
        delete task;
        return;
    }
    TaskNode* current = list->head;
    TaskNode* previous = nullptr;
    while (current != task) {
        previous = current;
        current = current->next;
    }
    previous->next = current->next;
    delete current;
}

TaskList* lookForTasks(TaskList *list ,std::string &keyword) {
    TaskList* auxiliarList = new TaskList();
    TaskNode* current = list->head;
    bool founded = false;
    std::string keywordUpper = keyword;
    std::transform(keywordUpper.begin(), keywordUpper.end(), keywordUpper.begin(), ::toupper);
    while(current!= nullptr){
        std::string descUpper = current->description;
        std::transform(descUpper.begin(), descUpper.end(), descUpper.begin(), ::toupper);
        if(descUpper.find(keywordUpper) != std::string::npos){
           addTask(auxiliarList, current);
        }
        current = current->next;
    }
    return auxiliarList;
}

void completeTask(TaskNode* task){
    task->status = true;

}
void showTask(TaskNode* task) {
    if(task->status){
        std::cout << "ESTADO: COMPLETADA!!!" <<std::endl;
    }else{
        std::cout << "ESTADO: PENDIENTE****" <<std::endl;
    }
    std::cout << "ID DE TAREA: " << task->id <<std::endl;
    std::cout << "DESCRIPCION: " << task->description << std::endl;
    std::cout << "AGREGADA EL: "  << task ->dateCreated <<std::endl;
    std::cout << "------------------------------------" << std::endl;
}

void showTasks(TaskList *&list){
    if(isListEmpty(list)){
        return;
    }
    TaskNode *aux = list->head;
    while(aux != nullptr){
        showTask(aux);
        aux = aux->next;
    }

    
}

void emptyList(TaskList *&list){
    if (isListEmpty(list)){return;}
    TaskNode * current = list->head;
    TaskNode * temp;
    while(current != nullptr){
        temp = current;
        current = current->next;
        delete temp;
         

    }
    list->head = nullptr;
   

}


int saveTasks(TaskList *&list){
    int result = 0;
    std::ofstream file("data/toDo/taskTodo.txt");
    if(!file){
         result = 1;
    }

    if(isListEmpty(list)){
        result = 2;
    }

    TaskNode *current = list->head;
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
    return result;


}

int loadTasks(TaskList *&list){
    int result = 0;
    std::ifstream file("data/toDo/taskTodo.txt");

     // Verificar si el archivo está vacío
    file.peek(); 
    if (file.eof()) {
        result = 1;
    }
    if(!file){
        result = 2;
    }
    int id;
    int maxId = 1;
    std::string description;
    std::string creationDate;
    file >> id;
    TaskNode* last = nullptr;
    while(id != -1){
        TaskNode* newNode = new TaskNode();
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
    return result;

}

void runToDo(TaskList *&list){
    int load = loadTasks(list);
    if (load == 2){ std::cout << "Error al momento de acceder a los datos guardados" <<std::endl;};
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

        switch (option) {
            case 1: {
                TaskNode* task = buildTask();
                addTask(list, task);
                std::cout << "Tarea añadida con exito!!" <<std::endl;
                std::cout << "Lista de tareas en la lista: " << std::endl;
                showTasks(list);
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR...."<< std::endl;
                std::cin.ignore() ; std::cin.get();
                option = -1;
                break;
            }

            case 2: {
                std::cout << "Ingrese el id de la tarea a eliminar (puede ver todas las tareas en la opcion 5)" <<std::endl;
                std::cin >> id;
                TaskNode* task = lookTaskId(list,id);
                if (!isListEmpty(list)) {
                    if(task != nullptr) {
                        showTask(task);
                        std::cout << "¿Desea eliminar esta tarea? [Y/n]: ";
                        std::cin >> confirmation;
                        confirmation = toupper(confirmation);
                        if(confirmation != 'n') {
                            deleteTask(list, task);
                            std::cout << "TAREA ELIMINADA CON EXITO" << std::endl;

                        }else {
                            std::cout << "Eliminación cancelada" <<std::endl;
                        }
                    }else {
                        std::cout << "LA TAREA CON ESE ID NO EXISTE" << std::endl;

                    }
                }else {
                    std::cout << "LA LISTA ESTA VACIA" <<std::endl;
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR...." << std::endl;
                std::cin.ignore() ; std::cin.get();



                option = -1;
                break;
            }

            case 3: {
                std::cout << "Ingrese la descripcion de la tarea o una palabra clave para recuperar varias:" <<std::endl;
                std::cin.ignore();
                std::getline(std::cin,description);
                TaskList* auxiliarList = lookForTasks(list,description);
                if (!isListEmpty(auxiliarList)) {
                    std::cout << "TAREAS QUE CONTIENEN: \" " << description << "\":" << std::endl;
                    showTasks(auxiliarList);
                    emptyList(auxiliarList);
                    delete auxiliarList;
                }else {
                    std::cout << "NO HAY TAREAS QUE CONTENGAN LA PALABRA CLAVE: \"" <<description <<"\"" << std::endl;
                    delete auxiliarList;
                }
                option = -1;
                break;
            }

            case 4: {
                std::cout << "Ingrese el ID de la tarea que ha finalizado: (puede ver todas las tareas en la opcion 5) " << std::endl;
                std::cin >> id;
                TaskNode* task = lookTaskId(list,id);
                if (task != nullptr) {
                    completeTask(task);
                    std::cout << "TAREA MARCADA COMO COMPLETADA" << std::endl;
                }else {
                    std::cout << "LA TAREA CON ESE ID NO EXISTE" << std::endl;
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR...." << std::endl;
                std::cin.ignore() ; std::cin.get();
                option = -1;
                break;
            }

            case 5:
                if (isListEmpty(list)) {
                    std::cout << "LA LISTA ESTA VACIA " << std::endl;
                }else {
                    showTasks(list);
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR...." << std::endl;
                std::cin.ignore() ; std::cin.get();
                option = -1;
                break;
            case 6:
                std::cout << "Se eliminaran todas las tareas de la lista , seguro quiere continuar? [Y/n]" << std::endl;
                std::cin >> confirmation;
                confirmation = toupper(confirmation);
                if(confirmation != 'N'){
                    emptyList(list);
                    std::cout << "La lista se ha vaciado correctamente" << std::endl;
                }else{
                    std::cout << "Operacion cancelada... Presione una tecla para continuar" << std::endl;
                    std::cin.ignore() ; std::cin.get();
                }
                option = -1;
                break;
            case 7:{

                std::cout << "Las tareas pendientes se guardaran en el archivo \"taskToDo.txt\", las tareas completadas se eliminaran." <<std::endl;
                std::cout << "Guardando tareas...." << std::endl;
                if (isListEmpty(list)) {
                    std::cout << " LA LISTA ESTA VACIA, NO SE GUARDA NADA " << std::endl;
                }else {
                    int save = saveTasks(list);
                    if (save == 1) {
                        std::cout << "Error al abrir el archivo para guardar los datos" << std::endl;
                    }else {
                        std::cout << "TAREAS AGREGADAS CON EXITO " << std::endl;
                        std::cout << "La proxima vez que inicies el programa , en la opcion 5 podras ver las tareas que te faltan por completar, hasta pronto" << std::endl;
                    }
                }
                emptyList(list);
                delete list;
                std::cout << "PRESIONE CUALQUIER TECLA PARA CONTINUAR.....";
                std::cin.ignore() ; std::cin.get();
                break;
            }
            default:
                break;
        }
    }
}