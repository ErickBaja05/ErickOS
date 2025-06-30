#ifndef TODO_H
#define TODO_H
#include <string>

struct Node;

void mainMenu();

void addTask(Node *& list);

std::string getTimeCustom();

void showTasks(Node *&list);

void runToDo(Node *&list);

#endif