#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"menu.h"
#include"partie_joueur.h"
#include"partie_machine.h"



void menujeu(SDL_Surface* ecran)
{

    int continuer =1;


       /* Chargement des images */
    SDL_Surface* homepage = IMG_Load("images/homepage.png");
    SDL_Surface* menu  = IMG_Load("images/menu.png");
    SDL_Surface* jouerbouton = IMG_Load("images/jouerbouton.png");
    SDL_Surface* reglesbouton = IMG_Load("images/reglesbouton.png");
    SDL_Surface* quitterbouton = IMG_Load("images/quitterbouton.png");
    SDL_Surface* regles = IMG_Load("images/regles.png");


        /* Charger les positions des images */
    SDL_Rect position;

        /* Charger les evenements */
    SDL_Event event ;

       /* initialisation de la position sur toute l'ecran */
    position.x = 0;
    position.y = 0;

       /*affichage du homepage */
    SDL_BlitSurface(homepage, NULL, ecran, &position);
    SDL_Flip(ecran);    SDL_Delay(1500);


       /* affichage du menu */
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
    SDL_BlitSurface(menu, NULL, ecran, &position);
    SDL_Flip(ecran);
    while(continuer)
    {
        /*on efface l'ecran pour afficher une autre image */
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_WaitEvent(&event);
        switch(event.type)
        {
          case SDL_MOUSEMOTION :
                     if(236<event.button.x && event.button.x<710 && 223<event.button.y && event.button.y<295)
                      {
                         SDL_BlitSurface(jouerbouton,NULL,ecran,&position);
                         SDL_Flip(ecran);

                      }
                      else if(236<event.button.x && event.button.x<710 && 312<event.button.y && event.button.y<405)
                          {
                           SDL_BlitSurface(reglesbouton,NULL,ecran,&position);
                           SDL_Flip(ecran);
                          }
                      else if(236<event.button.x && event.button.x<710 && 451<event.button.y && event.button.y<543)
                            {
                             SDL_BlitSurface(quitterbouton,NULL,ecran,&position);
                             SDL_Flip(ecran);
                            }
                     break;
            case SDL_MOUSEBUTTONDOWN :
                     if((event.button.button == SDL_BUTTON_LEFT) || (event.button.button == SDL_BUTTON_MIDDLE))
                     {
                        if(236<event.button.x && event.button.x<710 && 223<event.button.y && event.button.y<295)
                        {      jouer(ecran);
                               SDL_BlitSurface(menu, NULL, ecran, &position);
                               SDL_Flip(ecran);
                        }
                        else if(236<event.button.x && event.button.x<710 && 312<event.button.y && event.button.y<405)
                              {
                               SDL_BlitSurface(regles,NULL,ecran,&position);
                               SDL_Flip(ecran);
                              }
                        else if(236<event.button.x && event.button.x<710 && 451<event.button.y && event.button.y<543)
                                  continuer =0 ; //pr quitter
                     }
                     break;
            case SDL_QUIT :
                 continuer=0;
                 break;
       }
    }

       /* Libération d'espace mémoire */
    SDL_FreeSurface(homepage);
    SDL_FreeSurface(menu);
    SDL_FreeSurface(jouerbouton);
    SDL_FreeSurface(reglesbouton);
    SDL_FreeSurface(quitterbouton);
    SDL_FreeSurface(regles);
}

void jouer(SDL_Surface* ecran)
{
   SDL_Rect position ;
   SDL_Event event;
   int continuer=1;

       /*chargement des images */
    SDL_Surface* joueurs = IMG_Load("images/joueurs.png");

       /* initialisation de la position */
    position.x=0;
    position.y=0;

       /*on dessine l'arriere plan*/
    SDL_BlitSurface(joueurs,NULL,ecran,&position);
    SDL_Flip(ecran);
    while(continuer)
    {
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_MOUSEBUTTONDOWN :
                    if((event.button.button == SDL_BUTTON_LEFT) || (event.button.button == SDL_BUTTON_MIDDLE))
                    {
                        if(236<event.button.x && event.button.x<710 && 223<event.button.y && event.button.y<295)
                        {
                             partie_joueur(ecran);
                        }
                        else
                        {
                            if(236<event.button.x && event.button.x<710 && 312<event.button.y && event.button.y<405)
                               partie_machine(ecran);
                            else
                               if(236<event.button.x && event.button.x<710 && 451<event.button.y && event.button.y<543)
                               continuer =0 ; //pr return
                        }
                    }
                    break;
            case SDL_QUIT :
                 continuer=0;
                 break;

       }
    }

       /*Liberation d'espace mémoire */
    SDL_FreeSurface(joueurs);

}

void pause()
{
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            continuer = 0;
        }
    }
}
