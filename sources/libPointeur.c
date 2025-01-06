

#include "../headers/libPointeur.h"
//Fonction qui liberer les pointeurs
int libPointeur(){
    SDL_DestroyRenderer(renderer);
    //SDL_FreeSurface() est utilisé pour libérer la surface que nous avons chargé et que nous n'utiliserons plus.
    SDL_FreeSurface(score_surf_message); //libération de la surface	

	SDL_DestroyTexture(texture_de_font);
	SDL_DestroyTexture(texture_raquette);
	SDL_DestroyTexture(texture_de_balle);
	SDL_DestroyTexture(texture_de_vie);
	SDL_DestroyTexture(texture_de_message);
	
	SDL_DestroyTexture(texture_imgDF);


    SDL_FreeSurface(textSurface); //libération de la surface	
	SDL_DestroyTexture(messageTexture);
	
	TTF_CloseFont(font); 
	Mix_FreeMusic(music);  
	Mix_Quit();
	TTF_Quit(); 	
	IMG_Quit();
	SDL_DestroyWindow(ecran);
	SDL_Quit();  //Appel de la fonction SDL_Quit() pour quitter SDL.
	return 0;
}


