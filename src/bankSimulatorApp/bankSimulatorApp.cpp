//
// Created by User on 1/9/2025.
//

#include <iostream>
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

void enqueueClient(ClientQueue *&queue, ClientNode *client) {
    if (isQueueEmpty(queue)) {
        queue->head = client;
        queue->tail = client;
        return;
    }

    queue->tail->next = client;
    queue->tail = client;

}
ClientNode* buildCliente() {
    ClientNode* client = new ClientNode();
    client->id = N_CLIENT++;
    client->arrivalTime = getTimeCustom();
    std::cout << "INGRESE EL NOMBRE DEL CLIENTE: " << std::endl;
    std::getline(std::cin, client->name);
    std::cout << "INGRESE EL TIPO DE SERVICIO: " <<std::endl;
    std::getline(std::cin, client->serviceType);
    return client;
}

void dequeueClient(ClientQueue *&queue) {
    if (isQueueEmpty(queue)) {
        std::cout << "Dequeue de empty queue" <<std::endl;
        return;
    }
    ClientNode *delNode = queue->head;
    queue->head = queue->head->next;
    delete delNode;

    if (queue->head == nullptr) {
        queue->tail = nullptr;
    }
}

void peekClient(ClientQueue *&queue) {
    if (isQueueEmpty(queue)) {
        std::cout << "Peek empty queue" <<std::endl;
        return;
    }
    std::cout << "PROXIMO CLIENTE A ATENDERSE: " <<std::endl;
    std::cout << "ID: " << queue->head->id << std::endl;
    std::cout << "NOMBRE " << queue->head->name<< std::endl;
    std::cout << "TIPO DE SERVICIO: " << queue->head->serviceType<< std::endl;
    std::cout << "FECHA Y HORA DE INGRESO: " << queue->head->arrivalTime << std::endl;
    std::cout << "----------------------------" << std::endl;
}



bool isQueueEmpty(ClientQueue *&queue) {
    return queue->head == nullptr;
}

void runBankApp() {
    int op = -1;
    while (op < 0 || op > 6) {
        menuBankApp();
        std::cin >> op;
        if (op < 0 || op > 6) {
            std::cout << "OPCION NO VALIDA, INTENTE DE NUEVO" <<std::endl;
            continue;
        }
        switch (op) {
            case 1:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 2:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 3:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 4:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 5:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                op = -1;
                break;
            case 6:
                std::cout << "HASTA PRONTO " <<std::endl;

        }

    }


}