#include <stdio.h>
#include <stdlib.h>
#include "../headers/Init.h"
#include "../headers/erreurMessage.h"

int initPrincipal(){
	//Initialisation des sous-systèmes nécessaires aux jeux
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 ){
		printf("Erreur d'initialisation de la INIT(): %s\n",SDL_GetError());
		return 1;
	}
	//Mise en place de l'écran
	ecran = SDL_CreateWindow(
		"Brick Breaker Game",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		ecran_LARGREUR,
		ecran_LONGEUR,
		SDL_WINDOW_SHOWN
	);
	//Création d'un renderer qui nous permettra de afficher/dessiner à l'écran
	renderer = SDL_CreateRenderer(ecran, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!ecran && !renderer){ //if window happens to be null
		printf("La fênètre principale n' a pu être créé %s\n",SDL_GetError());

		printf("Erreur en essayant de creer le renderer: %s\n",SDL_GetError());
		SDL_DestroyWindow(ecran);
		SDL_Quit();
		return 1;
	}

	//Initialisation de la librairie image
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	//Initialisation de SDL_TTF
	//TTF_init() retourne -1 quand il y a une erreur.
	 TTF_Init();
	 //Appel de la fonction TTF_OpenFont qui prend deux arguments:
	 //1: *.ttf que nous avons besoin d'ouvrir,
	 //2: la taille à laquelle vous souhaitez initialiser le Font quand vous l'ouvrez.
	 font = TTF_OpenFont("assets/myfont.ttf",20);
	 erreurMessageFont(font,"font");

	 //Initialisation de la musqique
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096)<0){
		 printf("The Mix function was not sucessfully initiated %s\n",Mix_GetError());
		 return 1;
	}
	return 0;
}

//creation de la fenêtre pricipale et d'un renderer

void initSurface(){
	//Chargement de l'image de font
	 image_De_Fond = IMG_Load("assets/images/image_De_Font.jpg");
	 erreurMessageSurface(image_De_Fond, "image_De_Fond");	//Affichage du message d'erreur, si il y en a une

	//Chargement de l'image de la raquette
	 surf_raquette = IMG_Load("assets/images/paddle1.png");
	erreurMessageSurface(surf_raquette,"surf_raquette");	//Affichage du message d'erreur, si il y en a une

	//Chargement de l'image de la balle
	 surf_balle = IMG_Load("assets/images/ball_De_Jeux.png");
	 erreurMessageSurface(surf_balle,"surf_balle");		//Affichage du message d'erreur, si il y en a une

	//Chargement de l'image respesentant les vies du joueur
	 surf_vie = IMG_Load("assets/images/vie.jpg");
	 erreurMessageSurface(surf_vie,"surf_vie");		//Affichage du message d'erreur, si il y en a une
}

//Création des textures à partir des surfaces
void initTexture(){
	texture_de_font = SDL_CreateTextureFromSurface(renderer,image_De_Fond);
	erreurMessageTexture(texture_de_font,"texture_de_font");					//Message d'erreur, au cas où la texture ne serait pas crée
	SDL_FreeSurface(image_De_Fond); //libération de la surface

	texture_raquette = SDL_CreateTextureFromSurface(renderer,surf_raquette);
	erreurMessageTexture(texture_raquette,"texture_raquette");				  //Message d'erreur, au cas où la texture ne serait pas crée
	SDL_FreeSurface(surf_raquette); //we no longer neend the surface

	texture_de_balle = SDL_CreateTextureFromSurface(renderer,surf_balle);
	erreurMessageTexture(texture_de_balle,"texture_de_balle");					//Message d'erreur, au cas où la texture ne serait pas crée
	SDL_FreeSurface(surf_balle); //libération de la surface

	texture_de_vie = SDL_CreateTextureFromSurface(renderer,surf_vie);
	erreurMessageTexture(texture_de_vie,"texture_de_vie");					//Message d'erreur, au cas où la texture ne serait pas crée
	SDL_FreeSurface(surf_vie); //libération de la surface
}

//Permet de connaître les attributs d'une texture et de remplir une structure rect avec ces attributs
void queryTexture(){
	SDL_QueryTexture(texture_de_balle,NULL,NULL,&rect_ball.w,&rect_ball.h);
	rect_ball.x = 334;
	rect_ball.y = 445;

	//creation de texture pour l'image de le fond
	SDL_QueryTexture(texture_de_font,NULL,NULL,&rect_image_De_Fond.w,&rect_image_De_Fond.h);
	rect_image_De_Fond.x = 0;
	rect_image_De_Fond.y = 0;
	rect_image_De_Fond.h = rect_image_De_Fond.h - 200; //diminuer la tailler de l'image de fond

	//creation de texture pour l'image de la raquette
	SDL_QueryTexture(texture_raquette,NULL,NULL,&rect_raquette.w,&rect_raquette.h);
	rect_raquette.x = 250;
	rect_raquette.y = 400;
}

// changer la disposition des briques à l'écran
	void briquesConfig(struct briques *tab_briques ){
		FILE *pointeurFichier;
		pointeurFichier = fopen("assets/config.txt","r");
		char ch;
		int l = 0;
		while(!feof(pointeurFichier)){
				ch = fgetc(pointeurFichier);
				if(ch == 'X'){
					tab_briques[l].existence = true;
					tab_briques[l].cassee = false; 
					printf("%c",ch );
				}
				if(ch == ' '){
					tab_briques[l].existence = false;
					tab_briques[l].cassee = false; 					
					printf("%c",ch );

				}
				if(ch == '\n'){
					printf("%c\n",ch );
					l--;
				}
				if(ch == 'Y'){
					tab_briques[l].couleur[0] = 10;
					tab_briques[l].couleur[1] = 20;
					tab_briques[l].couleur[2] = 250;
					tab_briques[l].couleur[3] = 200;
					tab_briques[l].existence = true;
					tab_briques[l].cassee = false; 
					tab_briques[l].indestructible = true;
					tab_briques[l].frappee = 0;
					printf("%c",ch );					
				}
				l++;
		}
	}

	//Afhiche les vies à l'écran
	void afficherVies(struct vie *tab_vie){
		//Positionne les vies sur l'écran
		int deplacement = 0;
		for (int i = 0 ; i < nbr_vie ; i++){
			SDL_QueryTexture(texture_de_vie,NULL,NULL,&tab_vie[i].rect_vie.w,&tab_vie[i].rect_vie.h);
			tab_vie[i].rect_vie.x = 250 + deplacement;
			tab_vie[i].rect_vie.y = 0;
			deplacement += 40;
		}
	}
