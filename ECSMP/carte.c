#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "carte.h"

void initilisationPositions()
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

