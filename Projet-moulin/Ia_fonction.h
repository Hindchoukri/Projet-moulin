#ifndef IA_FONCTION_H_INCLUDED
#define IA_FONCTION_H_INCLUDED


       /*type structure qui définit les jetons */
typedef struct Etat
{
 int tableau[8][8];
 int jeton_b,jeton_r;
 int j_b_pose,j_r_pose;

}Etat;

typedef struct Noeud
{
 Etat  etat;
struct Noeud* suivant;
}Noeud;

typedef struct Noeud liste;

void f_etatinitial(Etat *e);
liste* generesuccesseur(Etat etatcourant,int maxplayer,liste *l);
liste *glisser(Etat etatcourant,int maxplayer, liste *l ); /*regle 2 */
liste* poser(Etat etatcourant,int maxplayer, liste *l );  /*regle 1 */
liste* sauter(Etat etatcourant,int maxplayer, liste *l );  /*regle 3 */
liste* enlevercase(Etat etatcourant,int maxplayer,liste *l); /* realisation du moulin */
void inserer(Etat etatinitial,liste** listenoeud);
Etat extraire(liste* l,int maxplayer);
int etatsolution(Etat );
int h(Etat);
int nombre_coup(Etat e,int maxplayer);
int nombre_moulin(Etat e, int maxplayer);
int utilitee(Etat);
int test_glisser(int posi_a,int posj_a,int posi_n,int posj_n);
int est_un_moulin(int posi,int posj,int br,Etat e);

#endif // IA_FONCTION_H_INCLUDED
