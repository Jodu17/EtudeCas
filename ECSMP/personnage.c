/**
 * \file      personnage.c
 * \author    PHAN Joseph, SEYDI Sarta, MONCAYO Lo�c
 * \version   1.1
 * \date      10 D�cembre 2014
 * \brief     Contient le fonctions permettant le d�placement du personnage � l'�cran, sur la carte.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "personnage.h"

/**
 * \brief      D�placement du personnage vers le haut
 * \details    Rafraichissement de la position et choix du sprite personnage tourn� vers le haut
 */
void versHaut()
{
    if(posPerso.y>0)
    {
        rafraichissementPositionPerso();

        posPerso.y-=TAILLE_SPRITE;
        positionPerso.x = 0;
        positionPerso.y = TAILLE_SPRITE*2;
        positionPerso.w = TAILLE_SPRITE;
        positionPerso.h = TAILLE_SPRITE-1;
        gestionRamassage();
        SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
        SDL_Flip(ecran);
    }
}

/**
 * \brief      D�placement du personnage vers le bas
 * \details    Rafraichissement de la position et choix du sprite personnage tourn� vers le bas
 */
void versBas()
{
    if(posPerso.y<HAUTEUR_FENETRE-TAILLE_SPRITE)
    {
        rafraichissementPositionPerso();

        posPerso.y+=TAILLE_SPRITE;
        positionPerso.x = 0;
        positionPerso.y = TAILLE_SPRITE*3;
        positionPerso.w = TAILLE_SPRITE;
        positionPerso.h = TAILLE_SPRITE;
        gestionRamassage();
        SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
        SDL_Flip(ecran);
    }
}

/**
 * \brief      D�placement du personnage vers la gauche
 * \details    Rafraichissement de la position et choix du sprite personnage tourn� vers la gauche
 */
void versGauche()
{
    if(posPerso.x>0)
    {
        rafraichissementPositionPerso();

        posPerso.x-=TAILLE_SPRITE;
        positionPerso.x = 0;
        positionPerso.y = TAILLE_SPRITE;
        positionPerso.w = TAILLE_SPRITE;
        positionPerso.h = TAILLE_SPRITE;
        gestionRamassage();
        SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
        SDL_Flip(ecran);
    }
}


/**
 * \brief      D�placement du personnage vers la droite
 * \details    Rafraichissement de la position et choix du sprite personnage tourn� vers la droite
 */
void versDroite()
{
    if(posPerso.x<LARGEUR_FENETRE-TAILLE_SPRITE)
    {
        rafraichissementPositionPerso();

        posPerso.x+=TAILLE_SPRITE;
        positionPerso.x = 0;
        positionPerso.y = 0;
        positionPerso.w = TAILLE_SPRITE;
        positionPerso.h = TAILLE_SPRITE;
        gestionRamassage();
        SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
        SDL_Flip(ecran);
    }
}
