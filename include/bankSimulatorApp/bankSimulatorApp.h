//
// Created by User on 1/9/2025.
//

#ifndef bankSimulatorAPP_H
#define bankSimulatorAPP_H

/**
 * @brief Global counter to add unique IDs to a client
 *
 * It is incremented when a new client is enqueued
 * When loading clients from the file, it is updated to avoid duplicates.
 *
 */
extern int N_NOTE;

/**
 * @struct ClientNode
 * @brief structure for the queue that represent a client. It contains information related to a bank
 *
 * Contains all the abstraction for the bank simulator planned and a pointer to the next node
 *
 */
struct ClientNode {
    int id = N_NOTE;
    std::string name;
    std::string serviceType;
    std::string arrivalTime;
    ClientNode* next;

};

/**
 * @struct ClientQueue
 * @brief structure to represent the queue of clients
 * It contains a pointer to the first and to the last pointer to guarantee a O(1) complexity in both enqueue and dequeue operations.
 */
struct ClientQueue {
    ClientNode* head = nullptr;
    ClientNode* tail = nullptr;
};

/**
 * @brief prints a menu on screen with the options available for the menuBankApp
 */
void menuBankApp();

/**
 * @brief calls all the functions of the bank simulator app and is the one who is called in the main file
 */
void runBankApp();

bool isEmpty(ClientQueue *&queue);
void queueClient(ClientQueue *&queue);
void dequeue(ClientQueue *&queue);

#endif