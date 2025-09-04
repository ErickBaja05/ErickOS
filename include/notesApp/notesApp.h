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
    NoteNode* next = nullptr;
};

/**
 * @struct NoteStack
 * @brief Struct which represents the STACK
 * Contains only a pointer to the top element initially being a null pointer
 */
struct NoteStack {
    NoteNode* top = nullptr;
};

/**
 * @brief calls all the functions of the notesApp program
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void runNotesApp(NoteStack *& stack);

/**
 * @brief menu to show all the options availabe for the NotesApp program.
 */
void menuNotesApp();
/**
 * @brief verify if the stack is empty
 * @param stack is the pointer to the stack where all the notes are being entered.
 */

bool isStackEmpty(NoteStack *& stack);
/**
 * @brief push a note into the stack
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void pushNote(NoteStack *& stack);
/**
 * @brief peek the last node added (LIFO STRUCTURE) without eliminating it
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void peekNote(NoteStack *& stack);
/**
 * @brief shows all the notes in the stack starting till the last one added (LIFO)
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void showStackNotes(NoteStack *& stack) ;
/**
 * @brief shows the last node added and after confirmation of the user the note is popped
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void popNote(NoteStack *& stack) ;
/**
 * @brief shows notes which content contains one instance of a keyword given. Case un-sensitive function.
 * @param stack is the pointer to the stack where all the notes are being entered.
 * @param keyword is the string to be evaluated. It will be transformed to uppercase
 */
void lookForNote(NoteStack *& stack , std::string keyword );

/**
 * @brief empty the stack realising all the memory previously located
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void emptyStack(NoteStack *& stack);

/**
 * @brief save the stack in the txt file.
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void saveNotes(NoteStack *& stack);

/**
 * @brief retrive all notes from the txt file , the stack is reversed due to LIFO structure
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void loadNotes(NoteStack *& stack);
/**
 * @brief reverse the stack to have the data exactly as it was
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void reverseStack(NoteStack *&stack);
#endif