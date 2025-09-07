//
// Created by User on 5/9/2025.
//
#include <iostream>
#include <fstream>
#include "musicApp/musicApp.h"

void musicAppMenu() {
    std::cout << "***** Simulador Reproductor de musica *********" <<std::endl;
    std::cout << "1. Agregar una cancion a la lista de reproduccion" <<std::endl;
    std:: cout <<"2. Eliminar una cancion de la lista de reproduccion" <<std::endl;
    std::cout << "3. Mostrar canciones en la lista de reproduccion" <<std::endl;
    std::cout << "4. Reproducir cancion actual" <<std::endl;
    std::cout << "5. Siguiente cancion" <<std::endl;
    std::cout << "6. Cancion anterior" <<std::endl;
    std::cout << "7. Reproducir toda la lista de reproduccion " <<std::endl;
    std::cout << "8. Reproducir toda la lista de reproduccion desde el final " <<std::endl;
    std::cout << "10. Vaciar la lista de reproduccion " <<std::endl;
    std::cout << "11. Guardar y volver al menu principal " <<std::endl;
    std::cout << "Ingrese una opcion: ";

}

SongNode* buildSong() {
    SongNode* song = new SongNode();
    std::cout << "Ingrese el titulo de la cancion: " << std::endl;
    getline(std::cin, song->title);
    std::cout << "Ingrese el autor de la cancion: " << std::endl;
    getline(std::cin, song->title);
    std::cout << "Ingrese la duracion de la cancion en minutos: " << std::endl;
    std::cin >> song->durationMinutes;
    return song;
}

void addSong(PlayList* playlist, SongNode* song, int index) {
    /*FIRST SONG ADDED TO PLAYLIST*/
    if (isPlayListEmpty(playlist)) {
        playlist->head = song;
        playlist->tail = song;
        song->next = song;
        song->previous = song;
        playlist->length++;
        playlist->current = 1;
        return;
    }
    /*ADITTION TO A SONG AT THE END OF THE PLAYLIST*/
    if (index >= playlist->length) {
        playlist->tail->next = song;
        song->previous = playlist->tail;
        song->next = playlist->head;
        playlist->head->previous = song;
        playlist->tail = song;
        playlist->length++;
        playlist->current = 1;
        return;
    }
    /*ADITION TO THE BEGINNING OF THE PLAYLIST*/

    if (index <= 1) {
        song->next = playlist->head;
        playlist->head->previous = song;
        song->previous = playlist->tail;
        playlist->tail->next = song;
        playlist->head = song;
        playlist->length++;
        playlist->current = 1;
        return;
    }

    /*ADDITION IN A SPECIFIC POSITION*/
    int jumps = 0;
    SongNode *current = playlist->head;
    while (jumps < index - 1) {
        current = current->next;
        jumps++;
    }
   current->previous->next = song;
    song->previous = current->previous;
    song->next = current;
    current->previous = song;
    playlist->length++;
    playlist->current = 1;

}

void deleteSong(PlayList* playlist, int index) {
    SongNode *temp = nullptr;
    if (isPlayListEmpty(playlist)) {
        return;
    }
    /*JUST ONE ELEMENT TO DELETE*/
    if (playlist->head == playlist->tail) {
        delete playlist->head;
        playlist->head = nullptr;
        playlist->tail = nullptr;
        playlist->length--;
        return;
    }
    /*DELETE THE TAIL*/
    if (index >= playlist->length) {
        temp = playlist->tail;
        playlist->tail->previous->next = playlist->head;
        playlist->tail = playlist->tail->previous;
        playlist->head->previous = playlist->tail;
        playlist->length--;
        delete temp;
        return;
    }
    /*DELETE THE HEAD*/
    if (index <= 1) {
        temp = playlist->head;
        playlist->head->next->previous = playlist->tail;
        playlist->head = playlist->head->next;
        playlist->tail->next = playlist->head;
        playlist->length--;
        delete temp;
        return;
    }

    /*DELETE A NODE IN AN SPECIFIC POSITION*/
    int jumps = 0;
    SongNode *current = playlist->head;
    while (jumps < index - 1) {

        current = current->next;
        jumps++;
    }
    current->previous->next = current->next;
    current->next->previous = current->previous;
    playlist->length--;
    delete current;
    playlist->length--;

}

bool isPlayListEmpty(PlayList* playlist) {
    return playlist->head == nullptr;
}

void runMusicApp(PlayList *playlist) {
    int option = -1 ;
    while (option < 0 || option > 11) {
        musicAppMenu();
        std::cin >> option;
        switch (option) {
            case 1:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 2:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 3:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 4:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 5:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 6:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 7:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 8:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 9:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 10:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 11:
                std::cout << "Hasta pronto: " <<std::endl;
                break;
            default:
                std::cout << "Opcion invalida" <<std::endl;
                break;
        }
    }
}