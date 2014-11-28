#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "carte.h"

void initilisationPositions()
{
//    positionChemin.x = TAILLE_SPRITE*2;
//    positionChemin.y = TAILLE_SPRITE;
//    positionChemin.h = TAILLE_SPRITE;
//    positionChemin.w = TAILLE_SPRITE;

    positionChemin.x = TAILLE_SPRITE*2;
    positionChemin.y = 0;
    positionChemin.h = TAILLE_SPRITE;
    positionChemin.w = TAILLE_SPRITE;

//    positionHerbe.x = TAILLE_SPRITE;
//    positionHerbe.y = TAILLE_SPRITE*8;
//    positionHerbe.w = TAILLE_SPRITE;
//    positionHerbe.h = TAILLE_SPRITE;

    positionHerbe.x = TAILLE_SPRITE*3;
    positionHerbe.y = 0;
    positionHerbe.w = TAILLE_SPRITE;
    positionHerbe.h = TAILLE_SPRITE;

//    positionPerso.x = TAILLE_SPRITE*4;
//    positionPerso.y = TAILLE_SPRITE*9;
//    positionPerso.w = TAILLE_SPRITE;
//    positionPerso.h = TAILLE_SPRITE;

    positionPerso.x = 0;
    positionPerso.y = 0;
    positionPerso.w = TAILLE_SPRITE;
    positionPerso.h = TAILLE_SPRITE;

    PosFinal.x = 0;
    PosFinal.y = 0;
    PosFinal.w = TAILLE_SPRITE;
    PosFinal.h = TAILLE_SPRITE;

    posPerso.x = 0;
    posPerso.y = 0;

    sprites = IMG_Load("images/sprites1.bmp");
    perso = IMG_Load("images/perso.bmp");
    gland = IMG_Load("images/gland.bmp");

    SDL_SetColorKey(perso, SDL_SRCCOLORKEY, SDL_MapRGB(perso->format, 255, 255, 255));
    SDL_SetColorKey(sprites, SDL_SRCCOLORKEY, SDL_MapRGB(sprites->format, 255, 255, 255));
    SDL_SetColorKey(gland, SDL_SRCCOLORKEY, SDL_MapRGB(gland->format, 255, 255, 255));

}


//void formationCarte()
//{
//    int i,j;
//    for(i = 0;i<NB_SPRITES_LARGEUR;i++)
//    {
//        for(j=0;j<NB_SPRITES_HAUTEUR;j++)
//        {
//
//            PosFinal.x = i*TAILLE_SPRITE;
//            PosFinal.y = j*TAILLE_SPRITE;
//
//            switch(carte[i][j])
//            {
//                case CHEMIN:
//                    SDL_BlitSurface(sprites, &positionChemin, ecran, &PosFinal);
//                    break;
//                case HERBE:
//                    SDL_BlitSurface(sprites, &positionHerbe, ecran, &PosFinal);
//                    break;
//            }
//        }
//    }
//}

