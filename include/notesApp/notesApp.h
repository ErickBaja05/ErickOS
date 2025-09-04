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
void runNotesApp(NoteStack * stack);

/**
 * @brief menu to show all the options availabe for the NotesApp program.
 */
void menuNotesApp();
/**
 * @brief verify if the stack is empty
 * @param stack is the pointer to the stack where all the notes are being entered.
 * @return bool depending on the stack if is empty or not. True if it is, false otherwise
 */

bool isStackEmpty(NoteStack * stack);

/**
 * @brief create a NoteNode to be stored in the stack
 * @return NoteNode* is a pointer to the new node to be added
 */
NoteNode* buildNote();
/**
 * @brief push a note into the stack
 * @param stack is the pointer to the stack where all the notes are being entered.
 * @param newNote is a noteNode which stores all the information of the Node. NoteNode previously built.
 */
void pushNote(NoteStack * stack, NoteNode * newNote);
/**
 * @brief peek the last node added (LIFO STRUCTURE) without eliminating it
 * @param stack is the pointer to the stack where all the notes are being entered.
 * @return NoteNode* the pointer to the top of the stack without elimintating it
 */
NoteNode* peekNote(NoteStack * stack) ;
/**
 * @brief shows all the notes in the stack starting till the last one added (LIFO)
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void showStackNotes(NoteStack * stack) ;
/**
 * @brief delete the top of the stack (LIFO)
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void popNote(NoteStack * stack) ;
/**
 * @brief generate a new stack with all the NoteNodes which contains a keyword or a phrase (keysensitive).
 * The stack is reversed to guarantee that data is correctly shown when needed (LIFO)
 * @param stack is the pointer to the stack where all the notes are being entered.
 * @param keyword is the string to be evaluated. It will be transformed to uppercase
 * @return NoteStacl* returns an auxiliar stack with the notes that math.
 */
NoteStack* lookForNotes(NoteStack *stack, std::string keyword) ;

/**
 * @brief empty the stack realising all the memory previously located
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void emptyStack(NoteStack * stack);

/**
 * @brief save the stack in the txt file.
 * @param stack is the pointer to the stack where all the notes are being entered.
 * @return int The function returns a numeric value to indicate who the process went
 * if function returns 0, everything went correctly
 * if function returns 1, there was an error when trying to open the file to store the data
 * if function returns 2, the stack is empty and there is nothing to save.
 */
int saveNotes(NoteStack * stack);

/**
 * @brief retrive all notes from the txt file , the stack is reversed due to LIFO structure
 * @param stack is the pointer to the stack where all the notes are being entered.
 * @return int The function returns a numeric value to indicate who the process went
 * if function returns 0, everything went correctly
 * if function returns 1, there was an error when trying to open the file to load the data
 * if function returns 2, the stack is empty and there is nothing to load
 */
int loadNotes(NoteStack * stack);
/**
 * @brief reverse the stack to have the data exactly as it was
 * @param stack is the pointer to the stack where all the notes are being entered.
 */
void reverseStack(NoteStack *stack);
#endif