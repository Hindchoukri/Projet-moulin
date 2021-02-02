#ifndef PARTIE_JOUEUR_H_INCLUDED
#define PARTIE_JOUEUR_H_INCLUDED
#include "Ia_fonction.h"

void partie_joueur(SDL_Surface* ecran);
void affiche_ecran(SDL_Surface * ecran,Etat e);
void choix_joueur(int *i ,int *j);
Etat J_placer(Etat etatcourant,int player );
Etat J_glisser(Etat etatcourant,int player );
Etat J_sauter(Etat etatcourant,int player );


#endif // PARTIE_JOUEUR_H_INCLUDED
