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
    ClientNode* next = nullptr;

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
 * @param queue is a pointer to the queue structure used for all the operations along the program
 */
void runBankApp(ClientQueue* queue);
/***
 * @brief verifies if the queue is empty or not by verifying if the head is a null pointer
 * @param queue is a pointer to the queue where all data is being saved
 * @return bool to know if the queue is empty, true if it is, false if not
 */
bool isQueueEmpty(ClientQueue *queue);

/**
 * @brief enqueue a cliente making the new node the new tail of the queue (FIFO)
 * @param queue is a pointer to the queue where all data is stored
 * @param client is a ClientNode previously built to be enqueued
 */
void enqueueClient(ClientQueue *queue, ClientNode *client);
/**
 * @brief build a ClientNode with all the information needed
 * @return ClientNode* pointer to a ClientNode which contains all the information of a client, ready to be enqueued
 */
ClientNode* buildClient();

/**
 * @brief makes the dequeue operation and adjust references inside the queue and dequeind the head (FIFO)
 * @param queue is a pointer to the queue where all data is stored
 */
void dequeueClient(ClientQueue *queue);

/**
 * @brief allows to retrieve the information of the head of the queue
 * @param queue is a pointer to the queue where all data is stored
 * @return ClientNode* pointer to the head of the queue
 */
ClientNode* peekClient(ClientQueue *queue);

/**
 * @brief prints all the information of a specific client
 * @param client pointer to a NodeClient which information is going to be printed
 */
void showClient(ClientNode *client);

/**
 * @brief calls the showClient function to print on screen the information of all clients in queue in order
 * @param queue pointer to the queue where all data is stored
 */
void showClients(ClientQueue *queue);

/**
 * @brief calls the dequeue function to delete all the nodes in the queue
 * @param queue pointer to the queue where all data is stored
 */
void emptyClientQueue(ClientQueue *queue);

/**
 * @brief saves all the clients in a txt file.
 * @param queue pointer to the queue where all data is stored
 * @return int Status code indicating the result of the operation:
*          - 0: Success — notes saved correctly.
 *         - 1: Error — failed to open the file.
 *         - 2: Warning — queue is empty, nothing to save.
 */
int saveQueue(ClientQueue *queue);
/**
 * @brief retrieves all the clients in a txt file into the queue of the program
 * @param queue pointer to the queue where all data is stored
 * @return int Status code indicating the result of the operation:
*          - 0: Success — notes load correctly.
 *         - 1: Error — failed to open the file.
 *         - 2: Warning — file is empty, nothing to load
 */
int loadQueue(ClientQueue *queue);

#endif