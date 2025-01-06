#ifndef Initialisation    //Au cas ou cette init.h serait déja défini
#define Initialisation

#include <stdio.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <SDL_mixer.h>   




SDL_Window *ecran;

//Les Surface tampon qui nous servira pour charger l'image 
SDL_Surface *image_De_Fond;
SDL_Surface *surf_raquette;
SDL_Surface *surf_balle;
SDL_Surface *surf_vie ;
SDL_Surface *score_surf_message;
//Creation d'un renderer 
SDL_Renderer * renderer;
//Création des textures necessaires
SDL_Texture *texture_de_font;
SDL_Texture *texture_raquette;
SDL_Texture *texture_de_balle;
SDL_Texture *texture_de_vie;
SDL_Texture *texture_de_message;
TTF_Font *font ;
	
//Création des structures Rect nécessaires
SDL_Rect rect_image_De_Fond;      //rectangle de l'image de font
SDL_Rect rect_raquette;			//rectangle de l'image de la raquette
SDL_Rect rect_ball; 			//rectangle de la balle 
SDL_Rect rect_scoreMessage;      //rectangle pour le score ou les messages de l'écran



//Pour l'affichage des messages à l'écran
SDL_Rect rect_TextMessage; 
SDL_Surface  *textSurface ;
SDL_Texture *messageTexture;
SDL_Rect rect_img;

//Pour l'image de de fin de jeu ou de début de jeu
SDL_Surface *surf_imgDF;
SDL_Texture *texture_imgDF;
SDL_Rect rect_imgDF;      

//Pour le score
char scoreArray[50] ;

//Pour la music
Mix_Music *music;

//Variables booléennes pour gérer les déplacemets de la raquettes
bool droit ;
bool gauche ;
bool finDeJeu ;
bool victoire ;

//Defintiion de la structure de briques et creation d'un tableau de la structure brique
struct briques{
	SDL_Rect brique;
	bool cassee ;
	bool existence;
	int couleur [4];
	bool indestructible;
	int frappee;
};
int nbr_briques;

//Création d'une structure vie pour gerer les vies du joueur
struct vie{
	SDL_Rect rect_vie;
};
int nbr_vie;



//Fonction qui initailise le jeux 
int initPrincipal();    
//Definition de la largeur et la longeur de la fenêtre/ecran principale
#define ecran_LARGREUR (700) 
#define ecran_LONGEUR  (500) 
//Defintion d'une vitesse pour le déplacement de la balle
#define VITESSE (300)
//Fonction qui intitiailse les textures nécessaires au jeux
void initTexture();
//Fonction qui intitialise les surface nécassaires au jeux
void initSurface();
//Foncton qui permet de connaître les attributs d'une structure
void queryTexture();

//Affichage des vies à l'écran
void afficherVies(struct vie *tab_vie);

//Change la configuration des briques
void briquesConfig(struct briques *tab_briques);
#endif