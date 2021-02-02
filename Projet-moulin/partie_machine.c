#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"menu.h"
#include"partie_joueur.h"
#include"partie_machine.h"

       /*fonction pour alphabeta */
int alphabeta(Etat e,int p,int a,int b, int maxplayer)
{

    if(p == 0) return h(e); //feuille
    else if(etatsolution(e)==1) utilitee(e); //le jeu a terminee
    else
    {
        liste *l,*L;
        int vals,v=0;
        if(maxplayer==1) //tour de max
            {
            liste *lesfilsMAX=NULL;
              lesfilsMAX=generesuccesseur(e,1,lesfilsMAX);
                v=-10000;
                for(l=lesfilsMAX;l!=NULL;l=l->suivant)
                   {
                     vals=alphabeta(l->etat,p-1,a,b,-1);
                       v=max(v,vals);
                       if(v>b) return v;
                       a=max(a,v);
                   }
            }
        else if(maxplayer==-1) //tour min
        {

             v=10000;
            liste *lesfilsMIN=NULL;
             lesfilsMIN=generesuccesseur(e,-1,lesfilsMIN);
             for(L=lesfilsMIN;L!=NULL;L=L->suivant)
                   {

                       vals=alphabeta(L->etat,p-1,a,b,1);
                       v=min(v,vals);
                       if(a>v) return v;
                       b=min(b,v);
                   }
        }
    return v;
    }

return 0;}



void machine_alphabeta(SDL_Surface *ecran)
{
    liste*listenoeuds;
    Etat etatcourant;
    f_etatinitial(&etatcourant);
    int player=1;
    affiche_ecran(ecran,etatcourant);
    while (!etatsolution(etatcourant))
    {

        if(player==1) //TOUR joueur
            {
                if(etatcourant.jeton_r>0) etatcourant=J_placer(etatcourant,player);

                else if(etatcourant.j_r_pose>3) etatcourant=J_glisser(etatcourant,player);

               else if(etatcourant.j_r_pose==3) etatcourant=J_sauter(etatcourant,player);
            }
       else //TOUR CPU
           {
              listenoeuds = NULL;
             listenoeuds=generesuccesseur(etatcourant,-1,listenoeuds);
             etatcourant=extraire(listenoeuds,-1);
           }

        if( etatsolution(etatcourant) == 1)
        {
            break;
        }
        affiche_ecran(ecran,etatcourant);
        player=(-1)*player;
    }
}
void partie_machine(SDL_Surface* ecran)
{

   SDL_Rect position ;
   SDL_Event event;
    position.x=0;
    position.y=0;
    int continuer=1;

       /*chargement des images */
    SDL_Surface* joueurs = IMG_Load("images/joueurs.png");

       /*on dessine l'arriere plan*/
    SDL_BlitSurface(joueurs,NULL,ecran,&position);
    SDL_Flip(ecran);

    /*machine_alphabeta(ecran);*/

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
                         machine_minimax(ecran);
                    }
                    else if(236<event.button.x && event.button.x<710 && 312<event.button.y && event.button.y<405)
                          {
                           machine_alphabeta(ecran);
                          }
                    else if(236<event.button.x && event.button.x<710 && 451<event.button.y && event.button.y<543)
                              continuer =0 ; //pr return

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


