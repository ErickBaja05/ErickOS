//
// Created by User on 18/8/2025.
//

#ifndef notesAPP_H
#define notesAPP_H

/**
 * @struct NoteNode
 * @brief Node of the STACK which represents each note
 * Contains all the for the abstraction of a Note and pointer to the next node
 */
struct NoteNode {
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
#endif