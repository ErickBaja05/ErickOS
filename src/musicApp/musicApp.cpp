//
// Created by User on 5/9/2025.
//
#include <iostream>
#include <fstream>
#include "musicApp/musicApp.h"
#include <thread>
#include <chrono>

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
    std::cout << "9. Vaciar la lista de reproduccion " <<std::endl;
    std::cout << "10. Guardar y volver al menu principal " <<std::endl;
    std::cout << "Ingrese una opcion: ";

}

SongNode* buildSong() {
    SongNode* song = new SongNode();
    std::cout << "Ingrese el titulo de la cancion: " << std::endl;
    getline(std::cin, song->title);
    std::cout << "Ingrese el autor de la cancion: " << std::endl;
    getline(std::cin, song->artist);
    std::cout << "Ingrese la duracion de la cancion en segundos: " << std::endl;
    std::cin >> song->durationSeconds;
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
    if (index > playlist->length) {
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


}

void showSong(SongNode *song) {
    std:: cout << "TITULO: "<<song->title << std::endl;
    std::cout << "AUTOR: " << song->artist <<std::endl;
    std::cout << "DURACION: " << getDuration(song->durationSeconds) << std::endl;
    std::cout << "------------------------------------" << std::endl;

}
std::string getDuration(int segsDuration) {
    int minutes = segsDuration / 60;
    int seconds = segsDuration % 60;
    return std::to_string(minutes) + ":" + std::to_string(seconds);
}
void playFromBeggining(PlayList* playlist) {
    if (isPlayListEmpty(playlist)) {
        return;
    }
    SongNode *song = playlist->head;
    for (int i = 0; i < playlist->length; i++) {
        showSong(song);
        std::this_thread::sleep_for(std::chrono::seconds(8));
        song = song->next;
    }
}

void playFromEnd(PlayList* playlist) {
    if (isPlayListEmpty(playlist)) {
        return;
    }
    SongNode *song = playlist->tail;
    for (int i = 0; i < playlist->length; i++) {
        showSong(song);
        std::this_thread::sleep_for(std::chrono::seconds(8));
        song = song->previous;
    }
}

void playSong(PlayList* playlist) {
    SongNode* song = goToSong(playlist, playlist->current);
    showSong(song);
}

void showPlaylist(PlayList* playlist) {
    if (isPlayListEmpty(playlist)) {
        return;
    }
    SongNode *song = playlist->head;
    for (int i = 0; i < playlist->length; i++) {
        showSong(song);
        song = song->next;
    }
}



SongNode* goToSong(PlayList* playlist, int index) {
    /*IF INDEX IS GREATER THAN THE MIDDLE, START FROM THE END, ELSE FROM THE HEAD*/
    SongNode* current;
    int fromBeggining = index - 1;
    int fromEnd = playlist->length - index;
    if (fromBeggining < fromEnd) {
        current = playlist->head;
        for (int i = 0; i < fromBeggining; i++) {
            current = current->next;
        }
        return current;
    }

    current = playlist->tail;
    for (int i = 0; i < fromEnd; i++) {
        current = current->previous;
    }
    return current;
}


bool isPlayListEmpty(PlayList* playlist) {
    return playlist->head == nullptr;
}

void runMusicApp(PlayList *playlist) {
    int option = -1 ;
    int index;
    while (option < 0 || option > 10) {
        musicAppMenu();
        std::cin >> option;
        switch (option) {
            case 1: {
                std::cin.ignore();
                SongNode* song = buildSong();
                if (isPlayListEmpty(playlist)) {
                    addSong(playlist, song, 0);

                }else {
                    std:: cout << "Ingrese la posicion a ingresar (negativos o 1 se insertara al inicio, un numero muy grande insertar al final):";
                    std::cin >> index;
                    addSong(playlist, song, index);
                }
                std::cout << "Cancion agregada exitosamente!!!" << std::endl;
                std::cout << "Presione una tecla para continuar..." << std::endl;
                std::cin.ignore(); std::cin.get();
                option = -1;
                break;
            }

            case 2: {
                char confirmation;
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;

                }else {
                    std:: cout << "Ingrese la posicion de la cancion a eliminar (negativos o 1 se eliminara la primera cancion, un numero muy grande eliminara la ultima:";
                    std::cin >> index;
                    SongNode* song = goToSong(playlist, index);
                    showSong(song);
                    std::cout << "Se eliminara esta cancion, desea continuar? (Y/n): " << std::endl;
                    std::cin >> confirmation;
                    confirmation = toupper(confirmation);
                    if (confirmation != 'N') {
                        deleteSong(playlist, index);
                        std::cout << "Cancion eliminada exitosamente!!!" << std::endl;
                    }else {
                        std::cout << "Operacion cancelada...." <<std::endl;
                    }

                }
                std::cout << "Presione una tecla para continuar..." << std::endl;
                std::cin.ignore(); std::cin.get();
                option = -1;
                break;
            }

            case 3:
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;

                }else{

                std::cout << "CANCIONES EN LA PLAYLIST: " <<std::endl;
                showPlaylist(playlist);
                std::cout << "Presione una tecla para continuar..." << std::endl;
                std::cin.get();

                }
                option = -1;
                break;
            case 4:{
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;

                }else {
                    std::cout << "REPRODUCIENDO....: " <<std::endl;
                    playSong(playlist);
                    std::this_thread::sleep_for(std::chrono::seconds(8));

                }
                option = -1;
                break;
               }
            case 5:
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;

                }else {
                    playlist->current++;
                    if (playlist->current > playlist->length) {
                        playlist->current = 1;
                    }
                    std::cout << "REPRODUCIENDO....: " <<std::endl;
                    playSong(playlist);
                    std::this_thread::sleep_for(std::chrono::seconds(8));
                }

                option = -1;
                break;
            case 6:
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;

                }else{
                    playlist->current--;
                    if (playlist->current <= 0) {
                        playlist->current = playlist->length;
                    }
                    std::cout << "REPRODUCIENDO....: " <<std::endl;
                    playSong(playlist);
                    std::this_thread::sleep_for(std::chrono::seconds(8));}

                option = -1;
                break;
            case 7:
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;

                }else{ std::cout << "INICIANDO RADIO DESDE EL INICIO: " <<std::endl;
                    playFromBeggining(playlist);}


                option = -1;
                break;
            case 8:
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;

                }else {
                    std::cout << "INICIANDO RADIO DESDE EL FINAL: " <<std::endl;
                    playFromBeggining(playlist);
                }

                option = -1;
                break;
            case 9:
                std::cout << "STILL BEING DEVELOPED: " <<std::endl;
                option = -1;
                break;
            case 10:
                std::cout << "Hasta pronto: " <<std::endl;
                break;
            default:
                std::cout << "Opcion invalida" <<std::endl;
                break;
        }
    }
}