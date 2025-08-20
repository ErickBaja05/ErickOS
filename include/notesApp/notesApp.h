//
// Created by User on 18/8/2025.
//

#ifndef notesAPP_H
#define notesAPP_H

/**
 * @brief Global counter to add unique IDs to a note
 *
 * It is incremented when a new note is saved
 * When loading notes from the file, it is updated to avoid duplicates.
 *
 */
extern int N_NOTE;
/**
 * @struct NoteNode
 * @brief Node of the STACK which represents each note
 * Contains all the for the abstraction of a Note and pointer to the next node
 */
struct NoteNode {
    int id = N_NOTE;
    std::string content;
    std::string creationDate;
    NoteNode* next;
};

/**
 * @struct NodeStack
 * @brief Struct which represents the STACK
 * Contains only a pointer to the top element initially being a null pointer
 */
struct NodeStack {
    NoteNode* top = nullptr;
};

/**
 * @brief calls all the functions of the notesApp program
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void runNotesApp(NodeStack *& stack);

/**
 * @brief menu to show all the options availabe for the NotesApp program.
 */
void menuNotesApp();
/**
 * @brief verify if the stack is empty
 * @param stack is the pointer to the stack where all the notes are being entered.
 */

bool isEmpty(NodeStack *& stack);
/**
 * @brief push a note into the stack
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void writeNote(NodeStack *& stack);
#endif