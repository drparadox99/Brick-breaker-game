#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/Init.h"
#include "headers/libPointeur.h"
#include "headers/erreurMessage.h"

int main(int agrc, char* arg[]){

	nbr_briques = 95;       //Nombre de Briques

	//Création d'un tableau de structure briques
	struct briques tab_briques[nbr_briques];

	//Variable booléenne pour état du jeu
	bool jeux_En_cours;
	jeux_En_cours = true ;
	//Le score
	int score = 0 ;
	//Création d'une Structure d'evenement
	SDL_Event event;

	//Positions initiales x,y de la raquette
	float x_pos = 260;
	float y_pos = 420;

	//Positions initailes x,y de la balle
	float x_pos_balle = 334;
	float y_pos_balle = 446;

	//velocité de la balle
	float x_vel_balle = 0;
	float y_vel_balle = 0;

	//Creation d'une strucure Rectangle pour pouvoir positionner le score à l'écran
	SDL_Rect rect_scoreMessage;
	rect_scoreMessage.x = 5;
	rect_scoreMessage.y = -3;

	//Creation d'une strucure Rectangle pour pouvoir positionner le chronomètre à l'écran
	SDL_Rect rect_chronometre;
	rect_chronometre.x = 400;
	rect_chronometre.y = -3;

	//Initialisation de la SDL et création d'un renderer
	initPrincipal();

	//Initialisation des surfaces nécessaires
	initSurface();

	//Initialisation des textures nécessaires
	initTexture();

	music = Mix_LoadMUS("assets/Coldplay.mp3"); //lance la musqique

	//Création d'un tableau de structure vie
	nbr_vie = 3	;
	struct vie tab_vie[nbr_vie];

	//Affiche les vies du joueur à l'écran
	afficherVies(tab_vie);

	//Intitialisation du tableau de structure briques  déterminination de leur états et attribution d'une couleur
	for(int i =0; i<nbr_briques;i++){
		tab_briques[i].couleur[0] = 100;
		tab_briques[i].couleur[1] = 250;
		tab_briques[i].couleur[2] = 50;
		tab_briques[i].couleur[3] = 120;
		tab_briques[i].cassee = false;
		tab_briques[i].existence = true;
		tab_briques[i].indestructible = false;
		tab_briques[i].frappee = 0;
	}

	//Permet de connaître les attributs d'une texture
	queryTexture();
	Mix_PlayMusic(music,-1) ;   ///Lance la musique

	//Variables Booléennes pour le déplacement à gauche et a droite.
	droit = false;
	gauche = false;

	//Etat du jeux
	finDeJeu =true;
	victoire = false ;
	bool init = true;
	bool fin = false;
	bool vie_perdue = false;
	int nbr_briques_cassees = 0;
	bool niveau_deux  = false;
	bool detection_De_Colision = false;
	bool deuxieme_essai = false;	 //
	//La grande boucle de jeux
	
	while (jeux_En_cours){
		//On entre dans cette boucle si le jeux est fini ou si le jeux vient  d'être commencé
		while(finDeJeu){
			
			while(SDL_PollEvent(&event)){

				if (event.type == SDL_QUIT) {
					jeux_En_cours = false ;
					finDeJeu = false;
					init = false;
					victoire = false;
				}
				if (fin == false){
					if (event.type == SDL_KEYDOWN){
						if (event.key.keysym.scancode == SDL_SCANCODE_Y){
							finDeJeu = false;
							victoire = false;
							niveau_deux = true;
							init = false;
							break;
						}
						if (event.key.keysym.scancode == SDL_SCANCODE_R){  ///???????
							init = false;
							victoire = true;
							//finDeJeu = false;
							break;
						}
						if (event.key.keysym.scancode == SDL_SCANCODE_S){  //On sort du while interne pour entre dans la grande boucle de jeu
							init = false;
							finDeJeu =false;
							break;
						}
						if (event.key.keysym.scancode == SDL_SCANCODE_N){  //si le joueur ne veut pas passer au niveau deux, sort du programme
						victoire = false;
						init = false;
						jeux_En_cours = false;
						finDeJeu = false;
						victoire = false;
						init = false;;
						fin = false;
						break;
						}
					}
				}
			}
			//Si le joueur a gagné
			if(victoire && deuxieme_essai!=true){
				textFinDeJeu("Victoire, Bravo, Continue y?n");
			}	

			if(fin || deuxieme_essai ){
				gameInit("assets/images/n4.png");
				init = false;
				victoire = false;
			}

			if(init){
				gameInit("assets/images/n5.png");
				//textFinDeJeu("La FiN");
			}
			init = false;
		}


		//Détermination des évenements pour le déplacement de la raquette
		while(SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT) jeux_En_cours = false;
			vie_perdue = false;
			if (event.type == SDL_KEYDOWN){
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
					droit = true;
					break;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
					gauche = true;
					break;
				}
			}			
			if (event.type== SDL_KEYUP){
				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
					droit = false;
					break;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
					gauche = false;
					break;
				}
				if (event.key.keysym.scancode == SDL_SCANCODE_R){ //POUR PASSER DIRECTEMENT AU NINEAU 2				
					niveau_deux = true;
					break;
				}				
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE){
						// x_vel_balle = VITESSE ;
						 y_vel_balle = VITESSE ;
						 break;
				}
			}		
		}
		//POUR PASSER AU NIVEAU DEUX ON MET NIVEAU_DEUX A VRAI
		//Passage au niveau suivant par changement de la disposition des briques
		if (niveau_deux){	
					briquesConfig(tab_briques);
					nbr_vie = 3	;						//On remet à trois les vies du joueur
					nbr_briques_cassees = 0; 		//On remet le nbr de briques cassées à 0
					niveau_deux = false;
					deuxieme_essai = true;  //Pour marquer qu'une partie de jeu a été realisée
					score = 0;
		}

		//Détection de collision entre la balle et les briques
		for (int i = 0; i < nbr_briques; i++){
			if (rect_ball.x >= tab_briques[i].brique.x-12 && rect_ball.x <= tab_briques[i].brique.x+36){
				if (rect_ball.y >= tab_briques[i].brique.y && rect_ball.y <= tab_briques[i].brique.y+20){
					if(tab_briques[i].cassee != true && tab_briques[i].existence == true){
							if (detection_De_Colision == false){ 		 //sert à éviter les multiples collisions
								if(tab_briques[i].indestructible == true && tab_briques[i].frappee < 2){
									tab_briques[i].frappee++;	
									y_vel_balle = -y_vel_balle;
									detection_De_Colision = true;  //pour éviter les multiples collision entre la balle et les briques 							
								}else{				
									tab_briques[i].cassee = true;			
									nbr_briques_cassees++;					//comptage de nombre de briques casées
									score+=10;								//incrémentation du score								
									printf("Le nombre de briques casées: %d\n",nbr_briques_cassees );
									y_vel_balle = -y_vel_balle;
									detection_De_Colision = true;  //pour éviter les multiples collision entre la balle et les briques 
								}
							}						
				  	}
				}
			}
		}

		//Detection de collision entre la balle et la raquette
		//Surface de la raquette entre 4 partie et redirection de la balle en fonction du contact avec sur 4 surfaces.
		for (int i = 0; i < nbr_briques ; i++){
			if (rect_ball.x >= rect_raquette.x && rect_ball.x <= rect_raquette.x+40){
				if (rect_ball.y >= rect_raquette.y+50 ){
					x_vel_balle = VITESSE;
					y_vel_balle = VITESSE;
					y_vel_balle = -y_vel_balle;
					x_vel_balle = -x_vel_balle;
					detection_De_Colision = false;
					break;
				}
			}
			if (rect_ball.x >= rect_raquette.x+41 && rect_ball.x <= rect_raquette.x+65){
				if (rect_ball.y >= rect_raquette.y+50){
					y_vel_balle = -y_vel_balle;
					x_vel_balle = 0;
					x_vel_balle = -10;
					detection_De_Colision = false;
					break;
				}
			}
			if (rect_ball.x >= rect_raquette.x+66 && rect_ball.x <= rect_raquette.x+95){
				if (rect_ball.y >= rect_raquette.y+55){
					y_vel_balle = -y_vel_balle;
					x_vel_balle = 0;
					x_vel_balle = 10;
					detection_De_Colision = false;
					break;
				}
			}
			if (rect_ball.x >= rect_raquette.x+96 && rect_ball.x <= rect_raquette.x+150){
				if (rect_ball.y >= rect_raquette.y+50){
					x_vel_balle = VITESSE;
					y_vel_balle = VITESSE;
					y_vel_balle = -y_vel_balle;
					x_vel_balle = +x_vel_balle;
					detection_De_Colision = false;					
					break;
				}
			}
			
			//Verification du cas où le hauteur de la balle dépasserait la hauteur de la raquette
			if(rect_ball.y > rect_raquette.y+55){
				if (vie_perdue == false){
					nbr_vie--;
					vie_perdue = true;
					x_pos_balle	= 334;
					y_pos_balle = 445;
					x_vel_balle = 0;
					y_vel_balle = 0;
					x_pos = 260;
					y_pos = 420;
				}
			}
		}

		//Detection de la fin de jeu au cas de défaite
		if(nbr_vie < 1  ){
			finDeJeu = true;
			fin = true;
		}
		//Detection de la fin de jeu au cas de victoire
		if(nbr_briques_cassees == nbr_briques){

			finDeJeu = true;
			victoire = true;
		}


		//détection de collision entre la balle et les cotés de l'écran
		if(x_pos_balle <= 0){
			x_pos_balle = 0;
			x_vel_balle = -x_vel_balle;
		}
		if(y_pos_balle <= 0){
			y_pos_balle = 0;
			y_vel_balle = -y_vel_balle;
		}
		if(x_pos_balle >= ecran_LARGREUR - rect_ball.w){
			x_pos_balle = ecran_LARGREUR - rect_ball.w;
			x_vel_balle = -x_vel_balle;
		}

		//Réapparition de la raqette à l'autre extemité de l'écran
		if(rect_raquette.x>=ecran_LARGREUR){
			x_pos = 0;
		}
		if(rect_raquette.x +90 <=0){
			x_pos = ecran_LARGREUR;
		}

		//mise à jour de la position balle
		x_pos_balle += x_vel_balle / 60;
		y_pos_balle += y_vel_balle / 60;


		//modification de la position dans la structure rectangle de la balle
		//On fait le cast, car on travaille avec des pixels
		rect_ball.x = (int) x_pos_balle;
		rect_ball.y = (int) y_pos_balle;


		//Mise à jour de la position de la raquette
		if(droit) x_pos += VITESSE/50;
		if(gauche) x_pos += -VITESSE/50;
		rect_raquette.x = (int) x_pos;

		//affichage à l'écran
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer,texture_de_font,NULL,&rect_image_De_Fond);
		SDL_RenderCopy(renderer,texture_raquette,NULL,&rect_raquette);
		SDL_RenderCopy(renderer,texture_de_balle,NULL,&rect_ball);
        SDL_RenderCopy(renderer,texture_de_message,NULL,&rect_scoreMessage);

		//Affichage des vies à l'écran
		for (int i = 0 ; i < nbr_vie ; i++){
			SDL_RenderCopy(renderer,texture_de_vie,NULL,&tab_vie[i].rect_vie);
	   	 }

		//Initialisation du tableau de structure briques et leur affichage à l'écran
		int espace_x = 0 ;
		int espace_y = 5 ;
		int plus = 0;
		int count = 0;
		for (int i = 0; i<nbr_briques;i++){
			count ++;
			tab_briques[i].brique.x = 0 + espace_x;
			tab_briques[i].brique.y = 13 + espace_y;
			tab_briques[i].brique.w = 36;
			tab_briques[i].brique.h = 20;
			SDL_SetRenderDrawColor(renderer,
						tab_briques[i].couleur[0] ,
						tab_briques[i].couleur[1] ,
						tab_briques[i].couleur[2] ,
						tab_briques[i].couleur[3]
			);
			//On demande les états des briques avant de les afficher à l'écran
			if(tab_briques[i].cassee != true){
				if(tab_briques[i].existence == true){
					SDL_RenderFillRect(renderer,&tab_briques[i].brique);
				}
			}
			espace_x += 37;	  //increamentation de la position x des briques pendant la construction
			if ((count  % 19 == 0)){
				espace_x = 0;
				espace_y +=30;     //increamentation de la position y des briques pendant la construction
			}
		}


	//Affichage du score
	afficherScore(score);

	//SDL_Query permet de connaitre les attributs d'une structure Rect
	SDL_QueryTexture(texture_de_message,NULL,NULL,&rect_scoreMessage.w,&rect_scoreMessage.h);

	SDL_RenderPresent(renderer);    //Pour tout afficher à l'écran
	SDL_RenderClear(renderer);
	}

	//Libération des pointeurs
	libPointeur();
}
