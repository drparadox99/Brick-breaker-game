#include <stdio.h>
#include <stdlib.h>
#include "../headers/erreurMessage.h"



//Fonction qui affiche l'erreur à l'écran si le chargement de la surface ne s'est pas bien passé.
//SDL_Get Error est une fonction qui renvoie l'erreur en question dans la console
void erreurMessageSurface(SDL_Surface *pointeurSurface,char *nomPointeurSurface){
if(!pointeurSurface){
  	printf("La %s n'a pas pue être chargée en mémoire  %s\n",nomPointeurSurface,SDL_GetError());
			SDL_DestroyWindow(ecran);
			SDL_Quit();
		}  
	 }

//Fonction qui affiche l'erreur à l'écran si le chargement de la texrure ne s'est pas bien passé.
void erreurMessageTexture(SDL_Texture *pointeurTexture,char *nomPointeurTexture){
if(!pointeurTexture){
  	printf("La %s n'a pas pue être chargée en mémoire  %s\n",nomPointeurTexture,SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(ecran);
		IMG_Quit();
		SDL_Quit(); 
		}  
	 }

//Fonction qui affiche l'erreur à l'écran si le chargement de la font ne s'est pas bien passé.
void erreurMessageFont(TTF_Font *font,char *nomPointeurFont ){ 
	if(!font){		
	  	printf("La %s n'a pas pue être chargée en mémoire  %s\n",nomPointeurFont,SDL_GetError());
		IMG_Quit();
		SDL_Quit(); 
	}
}

//Fonction qui affiche le score à l'écran
void afficherScore(int score){
	 snprintf(scoreArray,10,"%d",score); //convertit to type int en type string
	 SDL_Color couleur_score = { 255, 0, 250 };
	 char scoreString[40];
	 strcpy(scoreString, "SCORE: ");
	 strcat(scoreString,scoreArray);  //Concatenation de deux tableaux
	 score_surf_message = TTF_RenderText_Solid(font,scoreString,couleur_score);
	 texture_de_message = SDL_CreateTextureFromSurface(renderer,score_surf_message);
	 erreurMessageSurface(score_surf_message,"score_surf_message");	 	 
	 erreurMessageTexture(texture_de_message,"texture_de_message");	//Message d'erreur, au cas où la texture ne serait pas crée
}
//Fonction que afffiche du texte à l'écran
void textFinDeJeu(char *text){
		rect_TextMessage.x = 200;
		rect_TextMessage.y = 200;
		SDL_Color couleur_text = {100, 200, 250};
		textSurface = TTF_RenderText_Solid(font,text,couleur_text);   //Mise en place du texte sur la surface textmessage 
		messageTexture = SDL_CreateTextureFromSurface(renderer,textSurface);
		SDL_QueryTexture(messageTexture,NULL,NULL,&rect_TextMessage.w,&rect_TextMessage.h);		
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer,0,0,0,0); //setting a color for the renderer
		SDL_RenderCopy(renderer,messageTexture,NULL,&rect_TextMessage);				
        SDL_RenderPresent(renderer);  //draws on the screen the content of the renderer backbuffer
}


//Affiche des messages à l'écran
void gameInit(char *path_imgage){
	SDL_SetRenderDrawColor(renderer,0,0,0,0); //setting a color for the renderer
	surf_imgDF = IMG_Load(path_imgage);
	erreurMessageSurface(surf_imgDF, "surf_imgDF");	//Affichage du message d'erreur, si il y en a une
	texture_imgDF = SDL_CreateTextureFromSurface(renderer,surf_imgDF);
	erreurMessageTexture(texture_imgDF,"texture_imgDF");					//Message d'erreur, au cas où la texture ne serait pas crée
	rect_imgDF.x = 180;
	rect_imgDF.y = 30;
	rect_imgDF.h = 400;
	rect_imgDF.w = 400;
	SDL_RenderClear(renderer);		
	SDL_RenderCopy(renderer,texture_imgDF,NULL,&rect_imgDF);				
  	SDL_RenderPresent(renderer);  //draws on the screen the content of the renderer backbuffer	
	SDL_FreeSurface(surf_imgDF); //libération 	
}