#ifndef TODO_H
#define TODO_H
#include <string>

/**
 * @brief Global counter to add unique IDs to task
 * 
 * It is incremented when a new task is added
 * When loading tasks from the file, it is updated to avoid duplicates.
 *
 */
extern int N_TASK;
/**
 * @struct TasKNode
 * @brief Node of the linkedList that represents a task to do
 * Contains all the  information required for a task and a pointer to the next Node
 */
struct TasKNode {
    int id = N_TASK;
    std::string description;
    std::string dateCreated;
    bool status = false;
    TasKNode *next = nullptr;

};
/**
 * @struct TaskList
 * @brief Structure that represent the LinkedList of task to do
 * It only contains the Node head initialized as a null pointer.
 */
struct TaskList {
    TasKNode *head = nullptr;
};
/**
 * @brief Menu to indicate the user the funcionalities of the program
 */
void menuToDo();
/**
 * @brief Function to add a new task to the list
 * @details It creates nodes in heap memory and are linked trough the head
 * @param list pointer to the list where the task will be added.
 * @param description a string representing the description of the task to be saved
 */
void addTask(TaskList *& list ,std::string description);

/**
 * @brief prints on screen all the task and show if they are completed or not yet
 * @param list pointer to the list where the task are stored
 */
void showTasks(TaskList *&list);
/**
 * @brief deletes a task from the list and releases its memory
 * Looks for a task by the ID provided
 * @param list pointer to the list where task are stored
 * @param id identifier of the task to be deleted, it is given by the user
 * @details if there is not a task with the id provided, the function does nothing and shows a message on screen stating this.
 */
void deleteTask(TaskList *& list, int ID);
/**
 * @brief allows to change the value of the status field of the Node structure from false to true, meaning a task was completed
 * @param list  pointer to the list where the task are stored
 * @param id identifier or the task to be updated, it is given by the user
 * @details if there is not a task with the id provided, function does nothing and shows a message on screen stating this.
 */
void completeTask(TaskList *&list, int id);
/**
 * @brief delete all nodes and releases all the memory used by them
 * @param list pointer to the list where the task are stored
 */
void emptyList(TaskList *&list);
/**
 * @brief look and print on the screen all the task whose description contains a word or string given
 * @param list pointer to the list where task are saved
 * @param keyword string to be searched onto the description of all nodes
 * @details it is not case-sensitive, "PLAY" and "play" are treated the same. The conversion of the strings to uppercase is done with the help of auxiliaries variables to do not modify the original content.

 */
void lookForTask(TaskList *list, std::string &keyword);
/**
 * @brief store all the uncompleted task in a txt file. 
 * @param list pointer to the list where task are saved
 * @details it only stores task which has not been completed yet. Completed task are completely ignored
 */
void saveTasks(TaskList *&list);

/**
 * @brief load all the task stored in the txt filed to the list of the program.
 * @param list pointer to the list where task will be saved
 * @details it increments the N_TASK variable to do not allow duplicated ids for the tasks at the end of the load process
 * 
 */
void loadTasks(TaskList *&list);

/**
 * @brief function to call all the funcionalities of the program
 * @param list pointer to the list where the program will work
 * @details when the program is about to get closed, it automatically calls saveTask funtion, completed task are deleted.
 * At the end of the execution of this module, the list is deleted and its memory released.
 */
void runToDo(TaskList *&list);



#endif