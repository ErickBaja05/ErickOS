//
// Created by User on 5/9/2025.
//

#ifndef musicAPP_H
#define musicAPP_H
#include <string>

/**
 * @struct SongNode
 * @brief structure for the Double Circular Linked List which contains all the information for a song
 * Contains all the information for the abstraction of a song and pointers to the prev and next Node
 */
struct SongNode {
    std::string title;
    std::string artist;
    int durationSeconds;
    SongNode* previous;
    SongNode* next;

};

/**
 * @struct PlayList
 * @brief Doubly Circular Linked List with pointers to the beginning and to the end of the list
 * Represents a playlist of songs. Contains also a counter of how many songs are in the structure to allow insertion in any position
 */
struct PlayList {
    SongNode* head = nullptr;
    SongNode* tail = nullptr;
    int length = 0;
    int current = 0;
};

/**
 * @brief prints a Menu on the screen showing all the functions of the program available to do.
 */
void musicAppMenu();

/**
 * @brief calls all the functions of the program
 * @param playlist is the doubly circular linked list used by the program
 */
void runMusicApp(PlayList *playlist);

bool isPlayListEmpty(PlayList* playlist);
SongNode* buildSong();
void addSong(PlayList* playlist, SongNode* song, int index);
std::string getDuration(int segsDuration);
void deleteSong(PlayList* playlist, int index);
void showSong(SongNode *song);
void playFromBeggining(PlayList* playlist) ;
void playFromEnd(PlayList* playlist);
void showPlaylist(PlayList* playlist) ;
SongNode* goToSong(PlayList* playlist, int index);


#endif