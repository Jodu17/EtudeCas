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

#define TAILLE_SPRITE 34
#define NB_SPRITES_LARGEUR 12
#define NB_SPRITES_HAUTEUR 12
#define LARGEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_LARGEUR
#define HAUTEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_HAUTEUR

// Enumération globale qui permettra de faire une correspondance entre un nombre et un type de sprite
enum {CHEMIN,HERBE};

void pause();

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
    SDL_Surface *imageDeFond = NULL; // Le pointeur qui va stocker l'image de fond
    //SDL_Event event;
    SDL_Rect positionFond,srcrect,dstrect;

    positionFond.x = 0;
    positionFond.y = 0;
    positionFond.h = TAILLE_SPRITE;
    positionFond.w = TAILLE_SPRITE;

    /*srcrect.x = 0;
    srcrect.y = 0;

    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = 32;
    dstrect.h = 32;*/

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

    ecran = SDL_SetVideoMode(1200, 600, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("ECSMP - Etude de Cas", NULL);

    /* Chargement d'une image Bitmap dans une surface */
    imageDeFond = IMG_Load("images/Lenna.png");
//SDL_FillRect (ecran, NULL, SDL_MapRGB(ecran->format, 20, 50, 120));
    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    //SDL_BlitSurface(imageDeFond, NULL, ecran, &dstrect);
    SDL_Flip(ecran);

    pause(); // Mise en pause du programme

    SDL_FreeSurface(imageDeFond); /* On libère la surface */

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
