#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED

#define TAILLE_SPRITE 16
#define NB_SPRITES_LARGEUR 10
#define NB_SPRITES_HAUTEUR 10
#define LARGEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_LARGEUR
#define HAUTEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_HAUTEUR

enum {CHEMIN,HERBE};
SDL_Surface *ecran,*sprites;
SDL_Rect positionChemin,positionHerbe,PosFinal,positionPerso,posPerso;
int carre[10][10];

void formationCarte();
void chargementCarte();
void initilisationPositions();

#endif // CARTE_H_INCLUDED
