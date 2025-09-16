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

/**
 * @brief verifies if the head of the playlist is a null pointer to know if the playlist is empty.
 * @param playlist pointer to the playlist structure where all nodes are being saved
 * @return bool which indicates if the list is empty (true) or has elements (false)
 */
bool isPlayListEmpty(PlayList* playlist);

/**
 * @brief allocates a Node in memory and ask the user to fill the information needed.
 * @return SongNode* a pointer to a new song allocated in memory with all the information given
 */
SongNode* buildSong();

/**
 *
 * @param playlist pointer to the playlist structure where all the nodes are being stored
 * @param index position previously given by the user which represent the node to be deleted or the position where a new Node is goint to be added
 * @return pointer to the Node in the specified index.
 * @details it calculates if the path to reach the node if shorter starting from the end or from the start by calculating the number of "jumps" needed.
 * If there are 5000 SongNodes in the playlist and the user needs to access to the 3256 node, this function will iterate from the end.
 * If there are 5000 SongNodes in the playlist and the user needs to access to the 2225 node, this function will interate from the start.
 */
SongNode* goToSong(PlayList* playlist, int index);

/**
 * @brief adds a song in a specific position to the linked list.
 * @param playlist pointer to the playlist structure where all the nodes are being stored
 * @param song pointer to a Node to be added in the playlist
 * @param index position previously given by the user where song is going to be added.
 * @details If index is 4 for example, the new Node will be the fourth node in the list.
 * If a huge number is given as the index, Node is placed at the end and becomes the new tail
 * If a negative number is given as the index, Node is placed at the beginning and becomes the new head
 * It uses the goToSong function to be more efficient when a lot of data is linked and user.
 */
void addSong(PlayList* playlist, SongNode* song, int index);

/**
 * @brief allows to transform seconds into minutes and seconds to get the duration time of the song with an attractive format.
 * @param segsDuration time duration of the song expressed in seconds
 * @return string which represents the duration time of the song in minutes and second.
 */
std::string getDuration(int segsDuration);

/**
 * @brief deletes a song from any position indicated by the user.
 * @param playlist pointer to the playlist structure where all nodes are stored.
 * @param index osition previously given by the user representing the position of the song to be deleted.
*   @details If index is 4 for example, the Node to be deleted will be the fourth node in the list.
 * If a huge number is given as the index, the tail of the playlist is deleted and updated.
 * If a negative number is given as the index, the head of the playlist is deleted and updated.
 * It uses the goToSong function to be more efficient when a lot of data is linked and user.
 */
void deleteSong(PlayList* playlist, int index);

/**
 * @brief prints on screen the information of the song
 * @param song pointer to the Node which information is going to be printed
 */
void showSong(SongNode *song);

/**
 * @brief iterate over all the list from the head until the end and uses the ShowSong information to show which song is being played.
 * @param playlist pointer to the playlist structure where all date is being stored
 * @details It uses the length property of the playlist structure to know when the final have been reached.
 * it "freezes" the program for 8 seconds to simulate that a song is being played.
 */
void playFromBeginning(PlayList* playlist) ;
/**
 * @brief iterate over all the list from the tail until the head and uses the ShowSong information to show which song is being played.
 * @param playlist pointer to the playlist structure where all date is being stored
 * @details It uses the length property of the playlist structure to know when the final have been reached.
 * it "freezes" the program for 8 seconds to simulate that a song is being played.
 */
void playFromEnd(PlayList* playlist);

/**
 * @brief iterate over all the list from the head until the end and uses the ShowSong information to show which song is being played.
 * @param playlist pointer to the playlist structure where all date is being stored
 * @details is different from the playFromEnd and playFromBeginning functions cause it just show the songs information, it does not freeze the program.
 */
void showPlaylist(PlayList* playlist) ;

/**
 * @brief releases the memory allocated to all the nodes in the structure starting from the head.
 * @param playlist pointer to the playlist structure where all date is being stored
 */
void emptyPlaylist(PlayList* playlist);

/**
 * @brief allows to manipulate the position of the Nodes through the linked list.
 * @param playlist pointer to the playlist structure where all date is being stored
 * @param index position of the song to be moved.
 * @param index2 new position for the song.
 * @details this function follows the principles of the add and delete song previously explained to the index, it it is a huge number, tail will be selected and so on.
 * this functions works in two steps:
 * 1.- Simulates a deletion from the list by selecting a node in the index position and adjusting all the links, like a deletion but without realising memory.
 * 2.- Calls the addSong function to add the song in the index2 position
 */
void changePlaylistOrder(PlayList* playlist, int index, int index2);
/**
 * @brief saves the linkedList in the txt file.
 * @param playlist pointer to the playlist structure where all date is being stored
 * @return int The function returns a numeric value to indicate how the process went
*           - 0: Success — songs saved correctly.
 *         - 1: Error — failed to open the file.
 *         - 2: Warning — playlist is empty, nothing to save.
 * @details it types a "1" value just to control the reading.
 */
int savePlaylist(PlayList* playlist);
/**
 * @brief retrieves all song from the txt file. When a "-1" value is read, it stopped reading the file.
 * @param playlist pointer to the playlist structure where all date is being stored
 * @return int The function returns a numeric value to indicate how the process went
*          - 0: Success — songs loaded correctly.
 *         - 1: Error — failed to open the file.
 *         - 2: Warning — file is empty, nothing to load.

 */
int loadPlayList(PlayList* playlist);

#endif