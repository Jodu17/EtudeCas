#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "personnage.h"

void versHaut()
{
    if(posPerso.y>0)
    {
        posPerso.y-=TAILLE_SPRITE;
        positionPerso.x = 0;
        positionPerso.y = TAILLE_SPRITE*2;
        positionPerso.w = TAILLE_SPRITE;
        positionPerso.h = TAILLE_SPRITE-1;
    }
}

void versBas()
{
    if(posPerso.y<HAUTEUR_FENETRE-TAILLE_SPRITE)
    {
        posPerso.y+=TAILLE_SPRITE;
        positionPerso.x = 0;
        positionPerso.y = TAILLE_SPRITE*3;
        positionPerso.w = TAILLE_SPRITE;
        positionPerso.h = TAILLE_SPRITE;
    }
}

void versGauche()
{
    if(posPerso.x>0)
    {
        posPerso.x-=TAILLE_SPRITE;
        positionPerso.x = 0;
        positionPerso.y = TAILLE_SPRITE;
        positionPerso.w = TAILLE_SPRITE;
        positionPerso.h = TAILLE_SPRITE;
    }
}

void versDroite()
{
    if(posPerso.x<LARGEUR_FENETRE-TAILLE_SPRITE)
    {
        posPerso.x+=TAILLE_SPRITE;
        positionPerso.x = 0;
        positionPerso.y = 0;
        positionPerso.w = TAILLE_SPRITE;
        positionPerso.h = TAILLE_SPRITE;
    }
}
