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
 * @struct TaskNode
 * @brief Node of the linkedList that represents a task to do
 * Contains all the  information required for a task and a pointer to the next Node
 */
struct TaskNode {
    int id = N_TASK;
    std::string description;
    std::string dateCreated;
    bool status = false;
    TaskNode *next = nullptr;
};
/**
 * @struct TaskList
 * @brief Structure that represent the LinkedList of task to do
 * It only contains the Node head initialized as a null pointer.
 */
struct TaskList {
    TaskNode *head = nullptr;
};
/**
 * @brief Menu to indicate the user the funcionalities of the program
 */
void menuToDo();
/**
 * @brief Function to add a new task to the list
 * @param list pointer to the list where the task will be added.
 * @param task is a pointer to a TaskNode which represents the task to be added
 */

/**
 *@brief verifies if the list is empty or not
 *@return bool which indicates if the list is empty or not
 *@param list is the list to be evaluated
 *
*/
bool isListEmpty(TaskList * list);

/**
 * @brief function to add a Node to the list at the end of the list
 * @param list is the list where the TaskNode is going to be added
 * @param task is a previously built TaskNode to be added
 */
void addTask(TaskList * list, TaskNode* task);

/**
 *
 * @brief Function to collect data from console and store it in a TaskNode
 * @return TaskNode* pointer to the node which all the information of the task to be added
 */
TaskNode* buildTask();

/**
 * @brief print the information of an individual task.
 * @param task is the task whose information is going to be printed
 */
void showTask(const TaskNode* task);
/**
 * @brief prints on screen all the task and show if they are completed or not yet
 * @param list pointer to the list where the task are stored
 */
void showTasks(TaskList *list);

/**
 * @brief iterate over all the list until it finds a TaskNode whose id value is equal to the value given
 * @param list is the list where all TaskNodes are stored
 * @param id is the identifier to be compared with each TaskNodes id values
 * @return TaskNode* pointer the Node whose value where equals to the id given
 * if the functions returns a nullptr it means a node with the value given was not founded
 */
TaskNode* lookTaskId(const TaskList * list, int id);
/**
 * @brief deletes a task from the list and releases its memory
 * @param list pointer to the list where task are stored
 * @param task node to be eliminated
 * @details node must be part of the list for the function to work, links will work correctly
 */
void deleteTask(TaskList * list, TaskNode* task);
/**
 * @brief allows to change the value of the status field of the Node structure from false to true, meaning a task was completed
 * @param task node whose value is going to be modified previously looked by id
 */
void completeTask(TaskNode* task);
/**
 * @brief delete all nodes and releases all the memory used by them
 * @param list pointer to the list where the task are stored
 */
void emptyList(TaskList *list);
/**
 * @brief look for TaskNode whose description contains a keyword or a phrase
 * @param list pointer to the list where task are saved
 * @param keyword string to be searched onto the description of all nodes
 * @details it is not case-sensitive, "PLAY" and "play" are treated the same. The conversion of the strings to uppercase is done with the help of auxiliaries variables to do not modify the original content.
 * It stores all the coincidences in an auxiliar list
 * @return TaskList* is the auxiliar list where all nodes which coincidences where added

 */
TaskList* lookForTasks(const TaskList *list , const std::string &keyword);
/**
 * @brief store all the uncompleted task in a txt file. 
 * @param list pointer to the list where task are saved
 * @details it only stores task which has not been completed yet. Completed task are completely ignored
 * @return int which indicates if process ended well of there were mistakes
 *          - 0: Success — notes saved correctly.
 *         - 1: Error — failed to open the file.
 *         - 2: Warning — List is empty, nothing to save.

 */
int saveTasks(TaskList *list);

/**
 * @brief load all the task stored in the txt filed to the list of the program.
 * @param list pointer to the list where task will be saved
 * @details it increments the N_TASK variable to do not allow duplicated ids for the tasks at the end of the load process
 * @return int which indicates if process ended well of there were mistakes
 *          - 0: Success — task loaded correctly.
 *         - 1: Error — failed to open the file.
 *         - 2: Warning — file is empty, nothing to load.

 */
int loadTasks(TaskList *list);

/**
 * @brief function to call all the funcionalities of the program
 * @param list pointer to the list where the program will work
 * @details when the program is about to get closed, it automatically calls saveTask funtion, completed task are deleted.
 * At the end of the execution of this module, the list is deleted and its memory released.
 */
void runToDo(TaskList *list);



#endif