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