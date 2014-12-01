/*
Nom du Projet : ECSMP
Objectif : Réaliser un "jeu" qui permet à un personnage de trouver le plus court chemin dans un environnement définie
Développeur(se): Sarta Seydi, Loic & Phan Joseph
Date : Octobre/Novembre 2014
Année Universitaire : 3ème Année - Licence Informatique à La Rochelle
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include "carte.c"
#include "personnage.c"


//Prototype de fonction(s)
void gestionRamassage();
void rafraichissementPositionPerso();

    SDL_Event event;
    int i,j;
    bool exec = true;
    int carte[10][10]=  {{1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {0,0,0,0,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,0,0,0,0,0},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1}};

    int objet[10][10]=  {{0,1,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0}};

int main(int argc, char *argv[])
{
    initilisationPositions();

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, TAILLE_SPRITE, SDL_HWSURFACE); // Ouverture de la fenêtre
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("ECSMP - Etude de Cas", NULL);

    //Seulement au début
    formationCarte();
    placementObjets(1);
    SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);

    SDL_Flip(ecran);

    //Gestion des évèvements ( inputs )
    while (exec)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                exec=false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_UP:
                    versHaut();
                    break;
                case SDLK_DOWN:
                    versBas();
                    break;
                case SDLK_RIGHT:
                    versDroite();
                    break;
                case SDLK_LEFT:
                    versGauche();
                    break;
            }
            //SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
            //formationCarte();
            //placementObjets(1);
            //gestionRamassage();
            //SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
            //SDL_Flip(ecran);
            break;
        }
    }

    SDL_FreeSurface(sprites); // On libère la surface

    SDL_Quit();

    return EXIT_SUCCESS; // Fermeture du programme
}

void formationCarte()
{
    for(j = 0;j<NB_SPRITES_LARGEUR;j++)
    {
        for(i=0;i<NB_SPRITES_HAUTEUR;i++)
        {

            PosFinal.x = j*TAILLE_SPRITE;
            PosFinal.y = i*TAILLE_SPRITE;

            switch(carte[i][j])
            {
                case CHEMIN:
                    SDL_BlitSurface(sprites, &positionChemin, ecran, &PosFinal);
                    break;
                case HERBE:
                    SDL_BlitSurface(sprites, &positionHerbe, ecran, &PosFinal);
                    break;
            }
        }
    }
}
void rafraichissementPositionPerso()
{
            PosFinal.x = posPerso.x;
            PosFinal.y = posPerso.y;

            i=posPerso.y/TAILLE_SPRITE;
            j=posPerso.x/TAILLE_SPRITE;

            switch(carte[i][j])
            {
                case CHEMIN:
                    SDL_BlitSurface(sprites, &positionChemin, ecran, &PosFinal);
                    break;
                case HERBE:
                    SDL_BlitSurface(sprites, &positionHerbe, ecran, &PosFinal);
                    break;
            }
}

void placementObjets(int t)
{
    if(t==1)
    {
        for(j = 0;j<NB_SPRITES_LARGEUR;j++)
        {
            for(i=0;i<NB_SPRITES_HAUTEUR;i++)
            {

                PosFinal.x = j*TAILLE_SPRITE;
                PosFinal.y = i*TAILLE_SPRITE;

                positionObjet.x = 0;
                positionObjet.y = 0;
                positionObjet.w = TAILLE_SPRITE;
                positionObjet.h = TAILLE_SPRITE;

                if(objet[i][j]==1)
                {
                        SDL_BlitSurface(gland, &positionObjet, ecran, &PosFinal);
                        break;
                }
            }
        }
    }
}
void gestionRamassage()
{
    for(j = 0;j<NB_SPRITES_LARGEUR;j++)
    {
        for(i=0;i<NB_SPRITES_HAUTEUR;i++)
        {
            if(objet[i][j]==1)
            {
                if((posPerso.x/TAILLE_SPRITE==i)&&(posPerso.y/TAILLE_SPRITE==j))
                {
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                    formationCarte();
                    objet[i][j]=0;
                    placementObjets(1);
                    //SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
                    //SDL_Flip(ecran);
                }
            }
        }
    }
}
