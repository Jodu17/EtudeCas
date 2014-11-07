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

//Constantes sur les caractéristiques des sprites

#define TAILLE_SPRITE 16
#define NB_SPRITES_LARGEUR 10
#define NB_SPRITES_HAUTEUR 10
#define LARGEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_LARGEUR
#define HAUTEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_HAUTEUR

// Enumération globale qui permettra de faire une correspondance entre un nombre et un type de sprite
enum {CHEMIN,HERBE};

void pause();

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Surface *sprites = NULL; // Le pointeur qui va stocker l'image de fond
    SDL_Rect positionChemin,positionHerbe,PosFinal;
    int i,j;
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

    positionChemin.x = 16*2;
    positionChemin.y = 16;
    positionChemin.h = TAILLE_SPRITE;
    positionChemin.w = TAILLE_SPRITE;

    positionHerbe.x = 16;
    positionHerbe.y = 16*8;
    positionHerbe.w = 16;
    positionHerbe.h = 16;

    PosFinal.x = 0;
    PosFinal.y = 0;
    PosFinal.w = 16;
    PosFinal.h = 16;

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

    pause(); // Mise en pause du programme

    SDL_FreeSurface(sprites); /* On libère la surface */

    SDL_Quit(); // Arrêt de la SDL

    return EXIT_SUCCESS; // Fermeture du programme
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
