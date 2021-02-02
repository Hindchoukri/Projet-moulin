#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include"menu.h"


int main(int argc, char *argv[])
{
    int continuer =1 ;

       /*chargement des images */
    SDL_Surface* ecran = NULL ;
    SDL_Surface* homepage = IMG_Load("images/homepage.png");
    SDL_Surface* menu  = IMG_Load("images/menu.png");
    SDL_Surface* jouerbouton = IMG_Load("images/jouerbouton.png");
    SDL_Surface* reglesbouton = IMG_Load("images/reglesbouton.png");
    SDL_Surface* quitterbouton = IMG_Load("images/quitterbouton.png");
    SDL_Surface* joueurs = IMG_Load("images/joueurs.png");
    SDL_Surface* regles = IMG_Load("images/regles.png");

       /*chargement des positions */
    SDL_Rect position ;


    position.x=0;
    position.y=0;

      /* Initialistaion de la SDL  */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

       /* affichage dans l'icone  */
    SDL_WM_SetIcon(IMG_Load("images/moulin.png"), NULL);
    SDL_WM_SetCaption("JEU DU MOULIN ", NULL);


      /*initialisation de l'ecran */
    ecran = SDL_SetVideoMode(1006,543, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);

       /*affichage du menu du jeu*/
    menujeu(ecran);


    return EXIT_SUCCESS;
}
