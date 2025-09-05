//
// Created by User on 1/9/2025.
//

#include <iostream>
#include <fstream>
#include "bankSimulatorApp/bankSimulatorApp.h"
#include "utils/utils.h"


int N_CLIENT = 1;

void menuBankApp(){
    std::cout << "***** Simulador de cola de banco *********" <<std::endl;
    std::cout << "1. Poner cliente a la cola" <<std::endl;
    std:: cout <<"2. Atender a un cliente" <<std::endl;
    std::cout << "3. Mostrar al siguiente cliente a atenderse" <<std::endl;
    std::cout << "4. Ver a todos los clientes" <<std::endl;
    std::cout << "5. Eliminar a todos los clientes de la cola" <<std::endl;
    std::cout << "6. Guardar y volver al menu principal" <<std::endl;
    std::cout << "Ingrese una opcion: ";
}

void enqueueClient(ClientQueue *queue, ClientNode *client) {
    if (isQueueEmpty(queue)) {
        queue->head = client;
        queue->tail = client;
        return;
    }

    queue->tail->next = client;
    queue->tail = client;

}
ClientNode* buildClient() {
    ClientNode* client = new ClientNode();
    client->id = N_CLIENT++;
    client->arrivalTime = getTimeCustom();
    std::cout << "INGRESE EL NOMBRE DEL CLIENTE: " << std::endl;
    std::getline(std::cin, client->name);
    std::cout << "INGRESE EL TIPO DE SERVICIO: " <<std::endl;
    std::getline(std::cin, client->serviceType);
    return client;
}

void dequeueClient(ClientQueue *queue) {
    if (isQueueEmpty(queue)) {
        return;
    }
    ClientNode *delNode = queue->head;
    queue->head = queue->head->next;
    delete delNode;

    if (isQueueEmpty(queue)) {
        queue->tail = nullptr;
    }
}

void showClient(ClientNode *client) {
    std::cout << "ID: " << client->id<< std::endl;
    std::cout << "NOMBRE " << client->name<< std::endl;
    std::cout << "TIPO DE SERVICIO: " << client->serviceType<< std::endl;
    std::cout << "FECHA Y HORA DE INGRESO: " << client->arrivalTime << std::endl;
    std::cout << "----------------------------" << std::endl;
}

ClientNode* peekClient(ClientQueue *queue) {
    if (isQueueEmpty(queue)) {
        return nullptr;
    }
    return queue->head;

}

void showClients(ClientQueue *queue) {
    ClientNode* client = queue->head;
    while (client != nullptr) {
        showClient(client);
        client = client->next;
    }
}

void emptyClientQueue(ClientQueue *queue) {
    while (!isQueueEmpty(queue)) {
        dequeueClient(queue);
    }
}

bool isQueueEmpty(ClientQueue *queue) {
    return queue->head == nullptr;
}

int saveQueue(ClientQueue *queue) {
    std::ofstream file;
    file.open("data/bankSimulatorApp/clients.txt");

    if(!file){
        return 1;
    }

    if (isQueueEmpty(queue)) {
        return 2;
    }

    ClientNode* current = queue->head;
    while (current != nullptr) {
        file << current->id << std::endl;
        file << current->name << std::endl;
        file << current->serviceType << std::endl;
        file << current->arrivalTime <<  std::endl;
        current = current->next;
    }
    file << -1;
    file.close();
    return 0;

}

int loadQueue(ClientQueue *queue) {
    std::ifstream file;
    file.open("data/bankSimulatorApp/clients.txt");
    int id;
    std::string name;
    std::string serviceType;
    std::string arrivalTime;
    if(!file){
        return 1;
    }
    file.peek();
    if (file.eof()) {
        return 2;
    }

    int maxId = 1;
    file >> id;
    while (id != -1) {
        ClientNode* client = new ClientNode();
        if (id > maxId){maxId = id;}
        file.ignore();
        getline(file, name);
        getline(file, serviceType);
        getline(file, arrivalTime);
        client->id = id;
        client->name = name;
        client->serviceType = serviceType;
        client->arrivalTime = arrivalTime;
        enqueueClient(queue, client);
        file >> id;
    }
    file.close();
    N_CLIENT = ++maxId;
    return 0;
}

void runBankApp(ClientQueue* queue) {
    if (loadQueue(queue) == 1){std::cout << "Error al abrir el archivo para cargar los clientes" <<std::endl;}
    int op = -1;
    char confirmation;
    while (op < 0 || op > 6) {
        menuBankApp();
        std::cin >> op;
        if (op < 0 || op > 6) {
            std::cout << "OPCION NO VALIDA, INTENTE DE NUEVO" <<std::endl;
            continue;
        }
        switch (op) {
            case 1: {
                std::cin.ignore();
                ClientNode* client = buildClient();
                enqueueClient(queue, client);
                std::cout << "CLIENTE AGREGADO CORRECTAMENTE!!" << std::endl;
                std::cout << "----------------------------" << std::endl;
                std::cout <<"LISTA DE CLIENTES: "<<std::endl;
                showClients(queue);
                std::cout << "Presione una tecla para continuar..." <<std::endl;
                std::cin.get();
                op = -1;
                break;
            }

            case 2: {
                ClientNode* client = peekClient(queue);
                if (client == nullptr) {
                    std::cout << "NO HAY CLIENTES EN LA COLA" <<std::endl;
                }else {
                    std::cout<< "CLIENTE ATENDIDO: " <<std::endl;
                    showClient(client);
                    dequeueClient(queue);
                    std::cout <<"CLIENTES PENDIENTES: "<<std::endl;
                    showClients(queue);
                }
                op = -1;
                std::cout << "Presione una tecla para continuar..." <<std::endl;
                std::cin.ignore(); std::cin.get();
                break;
            }
            case 3: {
                ClientNode* client = peekClient(queue);
                if (client == nullptr) {
                    std::cout << "NO HAY CLIENTES EN LA COLA" <<std::endl;
                }else {
                    std::cout<< "PROXIMO CLIENTE A SER ATENDIDO: " <<std::endl;
                    showClient(client);
                }
                std::cout << "Presione una tecla para continuar..." <<std::endl;
                std::cin.ignore(); std::cin.get();
                op = -1;
                break;
            }
            case 4:
                if (isQueueEmpty(queue)) {
                    std::cout << "NO HAY CLIENTES EN LA COLA" <<std::endl;
                }else {
                    std::cout <<"CLIENTES EN LA COLA: "<<std::endl;
                    showClients(queue);
                }
                std::cout << "Presione una tecla para continuar..." <<std::endl;
                std::cin.ignore(); std::cin.get();
                op = -1;
                break;
            case 5:
                std::cin.ignore();
                std::cout << "Se eliminaran a todos los clientes de la cola , seguro quiere continuar? [Y/n]" << std::endl;
                std::cin >> confirmation;
                confirmation = toupper(confirmation);
                if(confirmation != 'N'){
                    emptyClientQueue(queue);
                    std::cout << "La cola ha sido vaciada correctamente: " << std::endl;
                }else{
                    std::cout << "Operacion cancelada" << std::endl;
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore() ; std::cin.get();
                op = -1;
                break;
            case 6:
                if (isQueueEmpty(queue)) {
                    std::cout << "NO HAY CLIENTES PARA GUARDAR" <<std::endl;
                }else {
                    if (saveQueue(queue) == 1) {
                        std::cout << "Error al abrir el archivo para guardar a los clientes" << std::endl;
                    }else {
                        std::cout << "Guardando clientes en el archivo clientes.txt..." <<std::endl;
                        std::cout << "CLIENTES GUARDADOS" << std::endl;
                        std::cout << "Hasta pronto" << std::endl;
                        emptyClientQueue(queue);
                    }
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore(); std::cin.get();
        }

    }

}