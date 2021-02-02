#include <stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include"menu.h"
#include"Ia_fonction.h"
#include"partie_joueur.h"
#include"partie_machine.h"

extern int  taille;

int etatsolution(Etat e)
{
      if(e.jeton_b==0) /*element vide */
      {
        if(e.j_b_pose==2 || (e.j_r_pose==2)) return 1;
        if(  (e.j_r_pose>3 && nombre_coup(e,1)==0) || (e.j_b_pose>3 && nombre_coup(e,-1)==0) )  return 1;
      }
    return 0;
}


void f_etatinitial(Etat *E)
{
   Etat e;
   int j,i;


    e.jeton_b=9;
    e.jeton_r=9;
    e.j_b_pose=0;
    e.j_r_pose=0;

    for(i=0;i<8;i++)
        for(j=0;j<8;j++)
            e.tableau[i][j]=0; /* vider la case d'indice de ligne i et d'indice de colonne j */

    for(j=1;j<=7;j++)
    {
        if(j!=1&&j!=4&&j!=7)
        {
            e.tableau[1][j]=2;
            e.tableau[7][j]=2;
        }
        if(j!=2&&j!=4&&j!=6)
        {
            e.tableau[2][j]=2;
            e.tableau[6][j]=2;
        }
        if(j!=3&&j!=4&&j!=5)
        {
            e.tableau[3][j]=2;
            e.tableau[5][j]=2;
        }
     }
    e.tableau[4][4]=2; /*pose interdit */
    *E=e;
    }

void inserer(Etat e,liste** N)
{
    liste* nouveau_noeud=NULL;
    int i,j;
    nouveau_noeud=(liste*)malloc(sizeof(liste));

    for (i=1;i<8;i++)
        for(j=1;j<8;j++)
        {
           nouveau_noeud->etat.tableau[i][j]=e.tableau[i][j];
        }
    nouveau_noeud->etat.jeton_b=e.jeton_b;
    nouveau_noeud->etat.jeton_r=e.jeton_r;
    nouveau_noeud->etat.j_r_pose=e.j_r_pose;
    nouveau_noeud->etat.j_b_pose=e.j_b_pose;
    nouveau_noeud->suivant=*N;
    *N=nouveau_noeud;
}


Etat extraire(liste *listenoeuds,int maxplayer)
{
    Etat E;
    int i,j,hval,hmin,hmax;
    liste*p,*temp;
    p=listenoeuds;
    int alpha=-10000,beta=10000;
    temp=listenoeuds->suivant;

    if(maxplayer==1)
    {
        hmax=alphabeta(listenoeuds->etat,3,alpha,beta,-1);
        while(temp!=NULL)
        {
             hval=alphabeta(temp->etat,3,alpha,beta,-1);
            if(hval > hmax)
                   {
                       hmax=hval;
                       p=temp;

                   }
           temp=temp->suivant;
        }
        }
    else if(maxplayer==-1) {
            hmin=alphabeta(listenoeuds->etat,3,alpha,beta,1);
             while(temp!=NULL)
        {
            hval=alphabeta(temp->etat,3,alpha,beta,1);
            if(hval<hmin)
               {
                   hmin=hval;
                    p=temp;
               }

            temp=temp->suivant;
        }

    }
   //extraire l'etat ayant le h convenable
    for (i=1;i<8;i++)
        for(j=1;j<8;j++)
        {
           E.tableau[i][j]=p->etat.tableau[i][j];
        }
    E.jeton_b=p->etat.jeton_b;
    E.jeton_r=p->etat.jeton_r;
    E.j_r_pose=p->etat.j_r_pose;
    E.j_b_pose=p->etat.j_b_pose;
    //liberer de l'espace de la liste listenoeuds

    while(listenoeuds!=NULL)
    {
        p=listenoeuds;
        listenoeuds=listenoeuds->suivant;
        free(p);

    }
return E;
}

int  est_un_moulin(int posi,int posj,int br,Etat e)
{
    int c=0;
    //pour les lignes
    if(e.tableau[posi][posj]==br)
    {
    if(posi==1||posi==7)
    {
         if(posj-3>0 && e.tableau[posi][posj-3]==br)
        { if(posj-6>0&&e.tableau[posi][posj-6]==br) c=1;
            else if(posj+3<8 &&e.tableau[posi][posj+3]==br) c=1;
        }
         else if(posj+3<8 && e.tableau[posi][posj+3]==br&&posj+6<8&&e.tableau[posi][posj+6]==br)  c=1;
    }

    if(posi==2||posi==6)
    {
         if(posj-2>0 && e.tableau[posi][posj-2]==br)
        { if(posj-4>0&&e.tableau[posi][posj-4]==br) c=1;
            else if(posj+2<8&&e.tableau[posi][posj+2]==br) c=1;
        }
         else if(posj+2<8 && e.tableau[posi][posj+2]==br&& posj+4<8 && e.tableau[posi][posj+4]==br)  c=1;
    }

    if(posi==3||posi==5||posi==4)
    {
         if(posj-1>0 && e.tableau[posi][posj-1]==br)
        { if(posj-2>0&&e.tableau[posi][posj-2]==br) c=1;
            else if(posj+1<8&&e.tableau[posi][posj+1]==br) c=1;
        }
         else if(posj+1<8 && e.tableau[posi][posj+1]==br&&posj+2<8&&e.tableau[posi][posj+2]==br)  c=1;
    }

    //pour les colonnes

        if(posj==1||posj==7)
    {
         if(posi-3>0 && e.tableau[posi-3][posj]==br)
        { if(posi-6>0&&e.tableau[posi-6][posj]==br) c=1;
            else if(posi+3<8&&e.tableau[posi+3][posj]==br) c=1;
        }
         else if(posi+3<8 && e.tableau[posi+3][posj]==br&&posi+6<8&&e.tableau[posi+6][posj]==br)  c=1;
    }

    if(posj==2||posj==6)
    {
         if(posi-2>0 && e.tableau[posi-2][posj]==br)
        { if(posi-4>0&&e.tableau[posi-4][posj]==br) c=1;
            else if(posi+2<8&&e.tableau[posi+2][posj]==br) c=1;
        }
         else if(posi+2<8 && e.tableau[posi+2][posj]==br&& posi+4<8 && e.tableau[posi+4][posj]==br)  c=1;
    }

    if(posj==3||posj==5||posj==4)
    {
         if(posi-1>0 && e.tableau[posi-1][posj]==br)
            { if(posi-2>0&&e.tableau[posi-2][posj]==br) c=1;
            else if(posi+1<8&&e.tableau[posi+1][posj]==br) c=1;
          }
         else if(posi+1<8 && e.tableau[posi+1][posj]==br&&posi+2<8&&e.tableau[posi+2][posj]==br)  c=1;
    }
    }

        return c;
}

int test_glisser(int posi_a,int posj_a,int posi_n,int posj_n)
{
    int permission=0;
    //pour les lignes
    if(posi_a==posi_n)
    {
        if((posi_a==1||posi_a==7) && (posj_a==posj_n-3||posj_a==posj_n+3))
                    permission=1;
       else if( (posi_a==2||posi_a==6) && (posj_a==posj_n-2||posj_a==posj_n+2))
                    permission=1;

      else if( (posi_a==3||posi_a==5||posi_a==4) && (posj_a==posj_n-1||posj_a==posj_n+1))
                    permission=1;

    }
    else if(posj_a==posj_n)//pour les colonnes
    {
        if( (posj_a==1||posj_a==7) && (posi_a == posj_n-3||posi_a==posi_n+3))
                    permission=1;

        else if((posj_a==2||posj_a==6) && (posi_a==posi_n-2||posi_a==posi_n+2))
                    permission=1;
         else if((posj_a==3||posj_a==5||posj_a==4) && (posi_a==posi_n-1||posi_a==posi_n+1))
                    permission=1;
    }

    return permission;
}


liste* enlevercase(Etat etatcourant,int maxplayer,liste *l)
{
    int i,j,c=0;
     if(maxplayer==1) etatcourant.j_b_pose--;
    else etatcourant.j_r_pose--;
    for(i=1;i<8;i++)
        for(j=1;j<8;j++)
          if(etatcourant.tableau[i][j]==(-1)*maxplayer && est_un_moulin(i,j,(-1)*maxplayer,etatcourant)==0)
            {
                etatcourant.tableau[i][j]=0;
                inserer(etatcourant,&l);
                etatcourant.tableau[i][j]=(-1)*maxplayer;
                c=1;
            }
       if(c==0)
        {
            for(i=1;i<8;i++)
            for(j=1;j<8;j++)
          if(etatcourant.tableau[i][j]==(-1)*maxplayer )
            {
                etatcourant.tableau[i][j]=0;
                inserer(etatcourant,&l);
                etatcourant.tableau[i][j]=(-1)*maxplayer;
            }
        }
    return l;
}
liste* poser(Etat etatcourant,int maxplayer, liste *l )
{
    int i,j;
    for(i=1;i<8;i++)
                    for(j=1;j<8;j++)
                        if(etatcourant.tableau[i][j]==0)
                            {
                                etatcourant.tableau[i][j]=maxplayer;
                                if(est_un_moulin(i,j,maxplayer,etatcourant)==1) l=enlevercase(etatcourant,maxplayer,l);
                                 else    inserer(etatcourant,&l);
                                etatcourant.tableau[i][j]=0;
                            }
    return l;
}
liste* glisser(Etat etatcourant,int maxplayer, liste *l )
{
    int i,j,k,m;
    for(i=1;i<8;i++)
                    for(j=1;j<8;j++)
                        if(etatcourant.tableau[i][j]==maxplayer)
                            {
                                for(k=1;k<8;k++)
                                    for(m=1;m<8;m++)
                                        if(etatcourant.tableau[k][m]==0 && test_glisser(i,j,k,m)==1)
                                            {
                                            etatcourant.tableau[i][j]=0;
                                            etatcourant.tableau[k][m]=maxplayer;
                                            if(est_un_moulin(k,m,maxplayer,etatcourant)==1) l=enlevercase(etatcourant,maxplayer,l);
                                            else inserer(etatcourant,&l);
                                             etatcourant.tableau[i][j]=maxplayer;
                                            etatcourant.tableau[k][m]=0;
                                            }


                            }


    return l;
}
liste* sauter(Etat etatcourant,int maxplayer, liste *l )
{
    int i,j,k,m;
    for(i=1;i<8;i++)
                    for(j=1;j<8;j++)
                        if(etatcourant.tableau[i][j]==maxplayer)
                            {
                                for(k=1;k<8;k++)
                                    for(m=1;m<8;m++)
                                        if(etatcourant.tableau[k][m]==0)
                                            {
                                            etatcourant.tableau[i][j]=0;
                                            etatcourant.tableau[k][m]=maxplayer;
                                            if(est_un_moulin(k,m,maxplayer,etatcourant)==1) l=enlevercase(etatcourant,maxplayer,l);
                                             else  inserer(etatcourant,&l);
                                             etatcourant.tableau[i][j]=maxplayer;
                                            etatcourant.tableau[k][m]=0;
                                            }
                            }
return l;}
liste* generesuccesseur(Etat etatcourant,int maxplayer,liste *l)
{
      if(maxplayer==1) //TOUR MAX
            {if(etatcourant.jeton_r>0)
            {
                etatcourant.jeton_r--;
                etatcourant.j_r_pose++;
                l=poser(etatcourant,1,l);
            }

           else if(etatcourant.j_r_pose>3) l=glisser(etatcourant,1,l );
           else if(etatcourant.j_r_pose==3) l=sauter(etatcourant,1,l);
            }
      else //TOUR MIN
      {
          if(etatcourant.jeton_b>0)
            {
                etatcourant.jeton_b--;
                etatcourant.j_b_pose++;
                l=poser(etatcourant,-1,l);
            }
         else if(etatcourant.j_b_pose>3)
                l=glisser(etatcourant,-1,l);
         else if(etatcourant.j_b_pose==3) l=sauter(etatcourant,-1,l);
    }

return l;
}

int h(Etat etatcourant)
{
    int nombre_pierre= etatcourant.j_r_pose-etatcourant.j_b_pose;
    int m=nombre_moulin(etatcourant,1)-nombre_moulin(etatcourant,-1);
    int n_coup=nombre_coup(etatcourant,1)-nombre_coup(etatcourant,-1);
    return m+nombre_pierre+10*n_coup;
}
int nombre_coup(Etat e,int maxplayer)
{

    int i,j,c=0,k,m;
   if( (e.j_r_pose==3 && e.jeton_r==0) || (e.j_b_pose==3 && e.jeton_b==0)) return 2;
         for(i=1;i<8;i++)
        for(j=1;j<8;j++)
            if(e.tableau[i][j]==maxplayer)
            {
                for(k=1;k<8;k++)
                    for(m=1;m<8;m++)
                        if(e.tableau[k][m]==0&& test_glisser(i,j,k,m)==1)
                            c++;
            }
    return c;
}
int nombre_moulin(Etat e, int maxplayer)
{
    int c=0;
    int b,v,i,j;
    //pour les lignes
    for(i=1;i<8;i++)
        {
        b=0;v=0;
            if(i==1||i==7)
               {
                for(j=1;j<8;j+=3)
                    {
                    if(e.tableau[i][j]==maxplayer) b++;
                    else if(e.tableau[i][j]==0) v++;
                    }
                if(b==3) c+=90;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=10;
                if(v==3) c+=1;
               }

           else if(i==2||i==6)
                {
                for(j=1;j<8;j+=2)
                    {
                    if(e.tableau[i][j]==maxplayer) b++;
                    else if(e.tableau[i][j]==0) v++;
                    }
                if(b==3) c+=90;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=20;
                }
         else if(i==3||i==5)
            {
                for(j=1;j<8;j+=1)
                    {
                    if(e.tableau[i][j]==maxplayer) b++;
                    else if(e.tableau[i][j]==0) v++;
                    }
                if(b==3) c+=70;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=10;
                }

       else {
        for(j=1;j<4;j+=1)
                  {
                    if(e.tableau[4][j]==maxplayer) b++;
                    else if(e.tableau[4][j]==0) v++;
                    }
                if(b==3) c+=70;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=20;
       b=0;v=0;
       for(j=5;j<8;j+=1)
                  {
                    if(e.tableau[4][j]==maxplayer) b++;
                    else if(e.tableau[4][j]==0) v++;
                    }
                if(b==3) c+=70;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=20;
       }
        }
    //pour les colonnes
    for(j=1;j<8;j++)
        {
        b=0;v=0;
            if(j==1||j==7)
               {
                for(i=1;i<8;i+=3)
                    {
                    if(e.tableau[i][j]==maxplayer) b++;
                    else if(e.tableau[i][j]==0) v++;
                    }
                if(b==3) c+=70;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=10;
               }
           else if(j==2||j==6)
                {
                for(i=1;i<8;i+=2)
                    {
                    if(e.tableau[i][j]==maxplayer) b++;
                    else if(e.tableau[i][j]==0) v++;
                    }
                if(b==3) c+=70;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=10;
                }
         else if(j==3||j==5)
            {
                for(i=1;i<8;i+=1)
                    {
                    if(e.tableau[i][j]==maxplayer) b++;
                    else if(e.tableau[i][j]==0) v++;
                    }
                if(b==3) c+=70;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=10;
                }
         else {
           for(i=1;i<4;i+=1)
                  {
                    if(e.tableau[i][4]==maxplayer) b++;
                    else if(e.tableau[i][4]==0) v++;
                    }
                if(b==3) c+=70;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=10;
    b=0;v=0;
    for(i=5;i<8;i+=1)
                  {
                    if(e.tableau[i][4]==maxplayer) b++;
                    else if(e.tableau[i][4]==0) v++;
                    }
                if(b==3) c+=70;
                else if(b==2 && v==1) c+=30;
                else if(v==2 && b==1 ) c+=20;
         }
    }


        return c;
}
int utilitee(Etat e)
{
    if(e.j_b_pose==2 || nombre_coup(e,-1)==0) return 1000;
    return -1000;
}
