#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "personnage.h"

void versHaut()
{
    if(posPerso.y>0)
        posPerso.y-=TAILLE_SPRITE;
}

void versBas()
{
    if(posPerso.y<HAUTEUR_FENETRE-TAILLE_SPRITE)
        posPerso.y+=TAILLE_SPRITE;
}

void versGauche()
{
    if(posPerso.x>0)
        posPerso.x-=TAILLE_SPRITE;
}

void versDroite()
{
    if(posPerso.x<LARGEUR_FENETRE-TAILLE_SPRITE)
        posPerso.x+=TAILLE_SPRITE;
}
