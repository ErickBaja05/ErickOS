#ifndef TODO_H
#define TODO_H
#include <string>

struct List;
struct Node;
void mainMenu();
void addTask(List *& list ,std::string description);
std::string getTimeCustom();
void showTasks(List *&list);
void runToDo(List *&list);
void deleteTask(List *& list, int ID);
void completeTask(List *&list, int id);
void emptyList(List *&list);
void lookForTask(List *list, std::string &keyword);

#endif