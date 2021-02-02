#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_ttf.h>
#include"menu.h"
#include"partie_joueur.h"
#include"partie_machine.h"
#include "Ia_fonction.h"

 SDL_Surface *ecran,*texte,*texte1 ;
 TTF_Font *police  ;
 SDL_Color couleurrouge ={110,2,2},couleurbleu ={2,2,110};


void affiche_ecran(SDL_Surface * ecran,Etat e)
{
    int i;

       /*Effacer l'ecran */
    SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));

       /*initialiser TTF */
    TTF_Init();

        /*charger les images*/
    SDL_Surface* plateau = IMG_Load("images/plateau.png");
    SDL_Surface* jetonrouge  = IMG_Load("images/jetonrouge.png");
    SDL_Surface* jetonbleu = IMG_Load("images/jetonbleu.png");
    SDL_Surface* retour = IMG_Load("images/retour.png");

       /*determine les positions */
    SDL_Rect position,posJetonR,posJetonB;

    position.x = 0;
    position.y = 0;

       /* ghargement de la police et du texte */
    police = TTF_OpenFont("vineritc.ttf",60);
    TTF_SetFontStyle(police, TTF_STYLE_ITALIC);



       /*affichagee du plateau */
    SDL_BlitSurface(plateau, NULL, ecran, &position);
    SDL_Flip(ecran);



       /*affichage du return */
    position.x=30;
    position.y=413;
    SDL_BlitSurface(retour, NULL, ecran, &position);
    SDL_Flip(ecran);


       /*affichage du texte du jeton rouge */
    position.x=100;
    position.y=50;
    texte = TTF_RenderText_Blended(police,"MAX",couleurrouge);
    SDL_BlitSurface(texte, NULL, ecran, &position);
    SDL_Flip(ecran);

       /*affichage du texte du jeton bleu */
    position.x=100;
    position.y=190;
    texte = TTF_RenderText_Blended(police,"MIN",couleurbleu);
    SDL_BlitSurface(texte, NULL, ecran, &position);
    SDL_Flip(ecran);

    position.x=120;
    position.y=250;

       /*affichage des jetons rouges */
     posJetonR.x = 50;
     posJetonR.y = 100;
     for(i=0;i<e.jeton_r;i++)
     {

        SDL_BlitSurface(jetonrouge, NULL, ecran, &posJetonR);
        posJetonR.x += 25;
        SDL_Flip(ecran);

     }

       /*affichage des jetons bleus */
    posJetonB.x =50;
    posJetonB.y =250;
    for(i=0;i<e.jeton_b;i++)
    {
        SDL_BlitSurface(jetonbleu, NULL, ecran, &posJetonB);
        posJetonB.x += 25;
        SDL_Flip(ecran);
    }

       /*l'affichage les pierrs posées sur le plateau */
    if(e.tableau[1][1]!=0)
    {
        position.x=430 ;
        position.y=65 ;
        if(e.tableau[1][1]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[1][4]!=0)
    {
        position.x=639;
        position.y=65;
        if(e.tableau[1][4]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[1][7]!=0)
    {
        position.x=851;
        position.y=65;
        if(e.tableau[1][7]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[2][2]!=0)
    {
        position.x=495;
        position.y=126;
        if(e.tableau[2][2]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[2][4]!=0)
    {
        position.x=637;
        position.y=126;
        if(e.tableau[2][4]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
        if(e.tableau[2][6]!=0)
    {
        position.x=779;
        position.y=126;
        if(e.tableau[2][6]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
        if(e.tableau[3][3]!=0)
    {
        position.x=567;
        position.y=181;
        if(e.tableau[3][3]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
        if(e.tableau[3][4]!=0)
    {
        position.x=637;
        position.y=181;
        if(e.tableau[3][4]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[3][5]!=0)
    {
        position.x=707;
        position.y=181;
        if(e.tableau[3][5]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[4][1]!=0)
    {
        position.x=430 ;
        position.y=240;
        if(e.tableau[4][1]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[4][2]!=0)
    {
        position.x=495;
        position.y=240;
        if(e.tableau[4][2]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[4][3]!=0)
    {
        position.x=567;
        position.y=240;
        if(e.tableau[4][3]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[4][5]!=0)
    {
        position.x=707;
        position.y=240;
        if(e.tableau[4][5]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[4][6]!=0)
    {
        position.x=779;
        position.y=240;
        if(e.tableau[4][6]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[4][7]!=0)
    {
        position.x=855;
        position.y=240;
        if(e.tableau[4][7]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[5][3]!=0)
    {
        position.x=567;
        position.y=300;
        if(e.tableau[5][3]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[5][4]!=0)
    {
        position.x=639;
        position.y=300;
        if(e.tableau[5][4]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[5][5]!=0)
    {
        position.x=707;
        position.y=300;
        if(e.tableau[5][5]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else   SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[6][2]!=0)
    {
        position.x=495;
        position.y=359;
        if(e.tableau[6][2]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[6][4]!=0)
    {
        position.x=639;
        position.y=359;
        if(e.tableau[6][4]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[6][6]!=0)
    {
        position.x=779;
        position.y=359;
        if(e.tableau[6][6]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[7][1]!=0)
    {
        position.x=430 ;
        position.y=417;
        if(e.tableau[7][1]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[7][4]!=0)
    {
        position.x=637;
        position.y=417;
        if(e.tableau[7][4]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }
    if(e.tableau[7][7]!=0)
    {
        position.x=855;
        position.y=417;
        if(e.tableau[7][7]==1) SDL_BlitSurface(jetonrouge, NULL, ecran, &position);
        else SDL_BlitSurface(jetonbleu, NULL, ecran, &position);
    }

    SDL_Flip(ecran);
    TTF_CloseFont(police);
    TTF_Quit();
       /*liberer la memoire */
    SDL_FreeSurface(texte);
    SDL_FreeSurface(texte1);
}

       /*placer un jeton sur le plateau */
Etat J_placer(Etat etatcourant,int player )
{
    int i,j,k,m;


     if(player==1)  /*placer une jeton rouge */
     {
        etatcourant.jeton_r--;
        etatcourant.j_r_pose++;
     }
     else  /*placer une jeton bleu  */
     {
        etatcourant.jeton_b--;
        etatcourant.j_b_pose++;
     }
    l1: choix_joueur(&i,&j);
    if(i==0 && j==0)  jouer(ecran);
    if(etatcourant.tableau[i][j]==0)
    {
        etatcourant.tableau[i][j]=player;
        if(est_un_moulin(i,j,player,etatcourant)==1)
        {
            affiche_ecran(ecran,etatcourant);
            l2: choix_joueur(&k,&m);
            if(est_un_moulin(k,m,(-1)*player,etatcourant)==0 && etatcourant.tableau[k][m]== (-1)*player)
            {
                etatcourant.tableau[k][m]=0;
                if(player==1) etatcourant.j_b_pose--;
                else etatcourant.j_r_pose--;
            }
            else
                goto l2;
        }
    }
    else goto l1;
return etatcourant;
}

       /* glisser un jeton  */
Etat J_glisser(Etat etatcourant,int player)
{
    int i,j,k,m;
    l1: choix_joueur(&i,&j);
    if(etatcourant.tableau[i][j]==player)
    {
        l2: choix_joueur(&k,&m);
        if( etatcourant.tableau[k][m]==0 && test_glisser(i,j,k,m)==1)
        {
            etatcourant.tableau[i][j]=0;
            etatcourant.tableau[k][m]=player;
            if(est_un_moulin(k,m,player,etatcourant)==1)
            {
                affiche_ecran(ecran,etatcourant);
                l3: choix_joueur(&k,&m);
                if(est_un_moulin(k,m,(-1)*player,etatcourant)!=1 && etatcourant.tableau[k][m]== (-1)*player)
                {
                            etatcourant.tableau[k][m]=0;
                            if(player==1) etatcourant.j_b_pose--;
                            else etatcourant.j_r_pose--;
                }
                else goto l3;
            }
        }
        else goto l2; //J'ai pas le droit de glisser

    }
    else goto l1;
    return etatcourant;
}

       /*quand le joueur possede que 3 jtons au plus il peut sauter avec le jeton */
Etat J_sauter(Etat etatcourant,int player)
{
    int i,j,k,m;
   l1:choix_joueur(&i,&j);
   if(etatcourant.tableau[i][j]==1)
       {
        l2:choix_joueur(&k,&m);
        if( etatcourant.tableau[k][m]==0)
            {
            etatcourant.tableau[i][j]=0;
            etatcourant.tableau[k][m]=1;
             if(est_un_moulin(k,m,player,etatcourant)==1)
                 {
                      affiche_ecran(ecran,etatcourant);
                    l3: choix_joueur(&k,&m);
                   if(est_un_moulin(k,m,(-1)*player,etatcourant)==0 && etatcourant.tableau[k][m]== (-1)*player)
                        {
                            etatcourant.tableau[k][m]=0;
                            if(player==1) etatcourant.j_b_pose--;
                            else etatcourant.j_r_pose--;
                        }
                else goto l3;
                }
            }
        else goto l2; //il faut afficher message d'erreur
        }
    else goto l1;
return etatcourant;
}

       /*joueur contre joueur */
void partie_joueur(SDL_Surface* ecran)
{

 Etat etatcourant;
 int player=1;


    f_etatinitial(&etatcourant);
    affiche_ecran(ecran,etatcourant);

     while (!etatsolution(etatcourant))
    {
        if(player ==1) //TOUR rouge
        {
           if(etatcourant.jeton_r>0)
                etatcourant=J_placer(etatcourant,player);
           else if(etatcourant.j_r_pose>3)
                etatcourant=J_glisser(etatcourant,player);
           else if(etatcourant.j_r_pose==3)
                etatcourant= J_sauter(etatcourant,player);
        }
       else //TOUR bleu
           {
              if(etatcourant.jeton_b>0)
              etatcourant= J_placer(etatcourant,player);

           else if(etatcourant.j_b_pose>3)
                  etatcourant= J_glisser(etatcourant,player);
           else if(etatcourant.j_b_pose==3)
                  etatcourant=J_sauter(etatcourant,player);
            }

        if( etatsolution(etatcourant) == 1)
        {
            //
            printf("\n succes ARRET SUR LE  nbre de noeuds  Etats traitees\n ");
            break;
        }
        affiche_ecran(ecran,etatcourant);
        player=(-1)*player;

    }
}

       /* enregistrer le choix du joueur */
void choix_joueur(int *i,int *j)
{
    int continuer=1;
    SDL_Event event;
    while(continuer)
    {
      SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_MOUSEBUTTONDOWN :
                if((event.button.button == SDL_BUTTON_LEFT) || (event.button.button == SDL_BUTTON_MIDDLE))
                {
                    if(444<event.button.x && event.button.x<484 && 93<event.button.y && event.button.y<133)
                    {   *i=1;  *j=1;continuer=0; }
                    else if(659<event.button.x && event.button.x<699 && 93<event.button.y && event.button.y<133)
                    {   *i=1;  *j=4;continuer=0;   }
                    else  if(870<event.button.x && event.button.x<910 && 93<event.button.y && event.button.y<133)
                    {   *i=1;  *j=7; continuer=0;  }
                    else if(515<event.button.x && event.button.x<555 && 152<event.button.y && event.button.y<192)
                    {   *i=2;  *j=2; continuer=0;  }
                    else if(659<event.button.x && event.button.x<699&& 152<event.button.y && event.button.y<192)
                    {   *i=2;  *j=4;  continuer=0; }
                    else if(799<event.button.x && event.button.x<839 && 152<event.button.y && event.button.y<192)
                    {   *i=2;  *j=6;  continuer=0; }
                   else if(587<event.button.x && event.button.x<627 && 201<event.button.y && event.button.y<251)
                    {   *i=3;  *j=3;  continuer=0; }
                    else if(659<event.button.x && event.button.x<699 && 201<event.button.y && event.button.y<251)
                    {   *i=3;  *j=4;  continuer=0; }
                   else if(727<event.button.x && event.button.x<767 && 201<event.button.y && event.button.y<251)
                    {   *i=3;  *j=5; continuer=0;  }
                    else if(444<event.button.x && event.button.x<484 && 270<event.button.y && event.button.y<310)
                    {   *i=4;  *j=1; continuer=0;  }
                   else if(515<event.button.x && event.button.x<555 && 270<event.button.y && event.button.y<310)
                    {   *i=4;  *j=2; continuer=0;  }
                    else if(587<event.button.x && event.button.x<627 && 270<event.button.y && event.button.y<310)
                    {   *i=4;  *j=3;continuer=0;   }
                   else if(727<event.button.x && event.button.x<767 && 270<event.button.y && event.button.y<310)
                    {   *i=4;  *j=5; continuer=0;  }
                    else if(799<event.button.x && event.button.x<839 && 270<event.button.y && event.button.y<310)
                    {   *i=4;  *j=6; continuer=0;  }
                   else if(870<event.button.x && event.button.x<910 && 270<event.button.y && event.button.y<310)
                    {   *i=4;  *j=7;  continuer=0; }
                   else if(587<event.button.x && event.button.x<627 && 327<event.button.y && event.button.y<367)
                    {   *i=5;  *j=3; continuer=0;  }
                     else if(659<event.button.x && event.button.x<699 && 327<event.button.y && event.button.y<367)
                    {   *i=5;  *j=4; continuer=0;  }
                    else if(727<event.button.x && event.button.x<767 && 327<event.button.y && event.button.y<367)
                    {   *i=5;  *j=5; continuer=0;  }
                    else if(515<event.button.x && event.button.x<555 && 386<event.button.y && event.button.y<426)
                    {   *i=6;  *j=2; continuer=0;  }
                    else if(659<event.button.x && event.button.x<699 && 386<event.button.y && event.button.y<426)
                    {   *i=6;  *j=4; continuer=0;  }
                   else if(799<event.button.x && event.button.x<839 && 386<event.button.y && event.button.y<426)
                    {   *i=6;  *j=6; continuer=0;  }
                    else if(444<event.button.x && event.button.x<484 && 445<event.button.y && event.button.y<485)
                    {   *i=7;  *j=1; continuer=0;  }
                    else if(659<event.button.x && event.button.x<699 && 445<event.button.y && event.button.y<485)
                    {   *i=7;  *j=4; continuer=0;  }
                    else  if(870<event.button.x && event.button.x<910 && 445<event.button.y && event.button.y<485)
                    {   *i=7;  *j=7; continuer=0;  }
                    else if(32<event.button.x && event.button.x<146 && 354<event.button.y && event.button.y<460)
                    {
                         *i=0;  *j=0; continuer = 0;
                    }

                   break;
            case SDL_QUIT :
                 continuer =0 ;
                 break;

       }
    }
}
}
