#ifndef Erreur
#define Erreur

#include "Init.h"
//Fonction qui qui affiche  à l'écran les érreurs liées à la création des Surfaces
void erreurMessageSurface(SDL_Surface *pointeurSurface,char *nomPointeurSurface);
//Fonction qui qui affiche  à l'écran les érreurs liées à la création des Textures
void erreurMessageTexture(SDL_Texture *pointeurTexture,char *nomPointeurTexture);
//Fonction qui qui affiche  à l'écran les érreurs liées à la création du Font
void erreurMessageFont(TTF_Font *font,char *nomPointeurFont );
//Fonction qui qui affiche  à l'écran le score
void afficherScore(int score);
//Fonction qui qui affiche du texte à l'écran 
void textFinDeJeu(char *text);
//Fonction qui qui affiche le chronomètre à l'écran le score
void chronometre(int countDown);
//Fonction qui affiche l'image de la fin et début du jeux 
void gameInit(char * path_image);


#endif