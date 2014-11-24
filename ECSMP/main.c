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
#include "personnage.h"

//#include "include\Astar.c"

//Constantes sur les caractéristiques des sprites

#define TAILLE_SPRITE 16
#define NB_SPRITES_LARGEUR 10
#define NB_SPRITES_HAUTEUR 10
#define LARGEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_LARGEUR
#define HAUTEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_HAUTEUR

// Enumération globale qui permettra de faire une correspondance entre un nombre et un type de sprite
enum {CHEMIN,HERBE};

SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Surface *sprites = NULL; // Le pointeur qui va stocker l'image de fond
    SDL_Rect positionChemin,positionHerbe,PosFinal,positionPerso,posPerso;
    SDL_Event event;
    struct personnage thePerso;
    int i,j;
    bool exec = true;
    int carte[10][10]= {{1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {0,0,0,0,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,0,0,0,0,0},
                        {1,1,1,1,0,1,1,1,1,1},
                        {1,1,1,1,0,1,1,1,1,1}};

void formationCarte();

int main(int argc, char *argv[])
{


    positionChemin.x = TAILLE_SPRITE*2;
    positionChemin.y = TAILLE_SPRITE;
    positionChemin.h = TAILLE_SPRITE;
    positionChemin.w = TAILLE_SPRITE;

    positionHerbe.x = TAILLE_SPRITE;
    positionHerbe.y = TAILLE_SPRITE*8;
    positionHerbe.w = TAILLE_SPRITE;
    positionHerbe.h = TAILLE_SPRITE;

    positionPerso.x = TAILLE_SPRITE*4;
    positionPerso.y = TAILLE_SPRITE*9;
    positionPerso.w = TAILLE_SPRITE;
    positionPerso.h = TAILLE_SPRITE;

    PosFinal.x = 0;
    PosFinal.y = 0;
    PosFinal.w = TAILLE_SPRITE;
    PosFinal.h = TAILLE_SPRITE;

    posPerso.x = 0;
    posPerso.y = 0;

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, TAILLE_SPRITE, SDL_HWSURFACE); // Ouverture de la fenêtre
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("ECSMP - Etude de Cas", NULL);

    sprites = IMG_Load("images/sprites.bmp");

    for(i = 0;i<NB_SPRITES_LARGEUR;i++)
    {
        for(j=0;j<NB_SPRITES_HAUTEUR;j++)
        {

            PosFinal.x = i*TAILLE_SPRITE;
            PosFinal.y = j*TAILLE_SPRITE;

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
                    if(posPerso.y>0)
                    posPerso.y-=TAILLE_SPRITE;
                    break;
                case SDLK_DOWN:
                    if(posPerso.y<HAUTEUR_FENETRE-TAILLE_SPRITE)
                    posPerso.y+=TAILLE_SPRITE;
                    break;
                case SDLK_RIGHT:
                    if(posPerso.x<LARGEUR_FENETRE-TAILLE_SPRITE)
                    posPerso.x+=TAILLE_SPRITE;
                    break;
                case SDLK_LEFT:
                    if(posPerso.x>0)
                    posPerso.x-=TAILLE_SPRITE;
                    break;
            }
            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
            formationCarte();
            SDL_BlitSurface(sprites, &positionPerso, ecran, &posPerso);
            SDL_Flip(ecran);
            break;
        }
    }

    SDL_FreeSurface(sprites); // On libère la surface

    SDL_Quit();

    return EXIT_SUCCESS; // Fermeture du programme
}

void formationCarte()
{
    for(i = 0;i<NB_SPRITES_LARGEUR;i++)
    {
        for(j=0;j<NB_SPRITES_HAUTEUR;j++)
        {

            PosFinal.x = i*TAILLE_SPRITE;
            PosFinal.y = j*TAILLE_SPRITE;

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
