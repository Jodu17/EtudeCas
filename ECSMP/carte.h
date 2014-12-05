#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED

#define TAILLE_SPRITE 32
#define NB_SPRITES_LARGEUR 20
#define NB_SPRITES_HAUTEUR 20
#define LARGEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_LARGEUR
#define HAUTEUR_FENETRE TAILLE_SPRITE*NB_SPRITES_HAUTEUR

enum {CHEMIN,HERBE};
SDL_Surface *ecran,*sprites,*perso,*gland;
SDL_Rect positionChemin,positionHerbe,PosFinal,positionPerso,posPerso,positionObjet;

void formationCarte();
void chargementCarte();
void initilisationPositions();

#endif // CARTE_H_INCLUDED
