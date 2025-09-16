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
    std::cout << "10. Cambiar el orden de la playlist  " <<std::endl;
    std::cout << "11. Guardar y volver al menu principal " <<std::endl;
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

    SongNode* songIndex = goToSong(playlist, index);
    songIndex->previous->next = song;
    song->next = songIndex;
    song->previous = songIndex->previous;
    songIndex->previous = song;
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
    SongNode* songIndex = goToSong(playlist, index);
    songIndex->previous->next = songIndex->next;
    songIndex->next->previous = songIndex->previous;
    playlist->length--;
    delete songIndex;
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
void playFromBeginning(PlayList* playlist) {
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

void emptyPlaylist(PlayList* playlist) {
    if (isPlayListEmpty(playlist)) {
        return;
    }
    SongNode* aux;
    SongNode* song = playlist->head;
    for (int i = 0; i < playlist->length; i++) {
        aux = song;
        song = song->next;
        delete aux;
    }
    playlist->head = nullptr;
    playlist->tail = nullptr;
    playlist->length = 0;
}

void changePlaylistOrder(PlayList* playlist, int index, int index2) {
    if (isPlayListEmpty(playlist)) {
        return;
    }
    if (playlist->length == 1) {
        return;
    }

    /*FIRST STEP, SIMULATE DELETION*/
    SongNode *nodeMoving = nullptr;
    /*CHANGE THE TAIL*/
    if (index >= playlist->length) {
        nodeMoving = playlist->tail;
        playlist->tail->previous->next = playlist->head;
        playlist->tail = playlist->tail->previous;
        playlist->head->previous = playlist->tail;
        /*CHANGE THE HEAD*/
    }else if (index <= 1) {
        nodeMoving = playlist->head;
        playlist->head->next->previous = playlist->tail;
        playlist->head = playlist->head->next;
        playlist->tail->next = playlist->head;
    }else {
        /*CHANGE A SPECIFIC NODE*/
        nodeMoving = goToSong(playlist, index);
        nodeMoving->previous->next = nodeMoving->next;
        nodeMoving->next->previous = nodeMoving->previous;
    }

    // SECOND STEP, ADD THE NODE INTO THE NEW POSITION
    addSong(playlist,nodeMoving, index2);
}


int savePlaylist(PlayList* playlist){

    std::ofstream file("data/musicApp/playlist.txt");
    if(!file){
         return 1;
    }

    if(isPlayListEmpty(playlist)){
        return 2;
    }

    int control = 1;

    SongNode *current = playlist->head;
    for (int i = 0; i < playlist->length; i++) {
        file << control << std::endl;
        file << current->title << std::endl;
        file << current->artist << std::endl;
        file << current->durationSeconds << std::endl;
        current = current->next;

    }

    file << -1;
    file.close();
    return 0;

}

int loadPlayList(PlayList* playlist) {
    std::string title;
    std::string artist;
    int durationSeconds;
    int control;
    std::ifstream file("data/musicApp/playlist.txt");
    if(!file) {
        return 1;
    }
    file.peek();
    if (file.eof()) {
        return 2;
    }
    file >> control;
    while (control != -1) {
        file.get();
        SongNode *song = new SongNode();
        std::getline(file , title);
        song->title = title;
        std::getline(file, artist);
        song->artist = artist;
        file >> durationSeconds;
        song->durationSeconds = durationSeconds;
        addSong(playlist,song,88);
        file >> control;
    }

    file.close();
    return 0;

}

void runMusicApp(PlayList *playlist) {
    if (loadPlayList(playlist) == 1){ std::cout << "Error al momento de acceder a los datos guardados" <<std::endl;};
    int option = -1 ;
    int index;
    int index2;
    char confirmation;
    while (option < 0 || option > 11) {
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
                    playFromBeginning(playlist);}


                option = -1;
                break;
            case 8:
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;

                }else {
                    std::cout << "INICIANDO RADIO DESDE EL FINAL: " <<std::endl;
                    playFromEnd(playlist);
                }

                option = -1;
                break;
            case 9:
                std::cin.ignore();
                std::cout << "Se eliminaran a todas las canciones de las playlist, desea continuar? [Y/n]" << std::endl;
                std::cin >> confirmation;
                confirmation = toupper(confirmation);
                if(confirmation != 'N'){
                    emptyPlaylist(playlist);
                    std::cout << "La playlist ha sido vaciada correctamente: " << std::endl;
                }else{
                    std::cout << "Operacion cancelada" << std::endl;
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore() ; std::cin.get();
                option = -1;
                break;
            case 10:
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA" << std::endl;
                }else if (playlist->length == 1) {
                    std::cout << "SOLO EXISTE UNA CANCION EN LA PLAYLIST, NO SE PUEDE MOVER NADA" <<std::endl;
                }else {
                    std:: cout << "Ingrese la posicion de la cancion a cambiar (negativos o 1 se escojera el inicio, un numero muy grande escojera el final):";
                    std::cin >> index;
                    std:: cout << "Ingrese la nueva posicion de la cancion (negativos o 1 se insertara al inicio, un numero muy grande insertara al final):";
                    std::cin >> index2;
                    changePlaylistOrder(playlist, index, index2);
                    std::cout << "PLAYLIST ACTUALIZADA, PUEDES VERLA CON LA OPCION 3" <<std::endl;
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore() ; std::cin.get();
                option = -1;
                break;
            case 11:
                if (isPlayListEmpty(playlist)) {
                    std::cout << "LA PLAYLIST ESTA VACIA, NO SE GUARDA NADA" << std::endl;
                }else if (savePlaylist(playlist) == 1) {
                    std::cout << "Error al abrir el archivo para guardar la playlist" << std::endl;
                }else {
                    std::cout << "Guardando playlist en el archivo playlist.txt..." <<std::endl;
                    std::cout << "CANCIONES GUARDADAS" << std::endl;
                    std::cout << "Hasta pronto" << std::endl;
                    emptyPlaylist(playlist);
                }
                std::cout << "PRESIONE UNA TECLA PARA CONTINUAR..." <<std::endl;
                std::cin.ignore(); std::cin.get();
                break;
            default:
                std::cout << "Opcion invalida" <<std::endl;
                break;
        }
    }
}