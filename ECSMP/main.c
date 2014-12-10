/*
Nom du Projet : ECSMP
Objectif : Realiser un "jeu" qui permet a un personnage de trouver le plus court chemin dans un environnement definie
Developpeur(se): Sarta Seydi, Loic & Phan Joseph
Date : Octobre/Novembre 2014
Annee Universitaire : 3ème Annee - Licence Informatique a La Rochelle
*/

/**
 * \file      main.c
 * \author    PHAN Joseph, SEYDI Sarta, MONCAYO Loïc
 * \version   1.1
 * \date      10 Decembre 2014
 * \brief     Cree et lance un jeu de collecte de ressources sur une carte 2D grace a un algorithem de plus court chemin.
 *
 * \details   Fichier main du projet (definition de la carte, de l'emplacement des ressources)
 */

#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "carte.c"
#include "personnage.c"



//Prototype de fonction(s)
void gestionRamassage();
void rafraichissementPositionPerso();

    int score; // Variable pour le nombre de deplacements
    SDL_Event event;
    int i,j;
    bool exec = true;

// Carte de fond du jeu
int carte[NB_SPRITES_LARGEUR][NB_SPRITES_HAUTEUR]=
   {{0,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,3,3,1,1,1,1,1,1,2,2,1,1,1,1,1,1,3,3,1},
    {2,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,2},
    {2,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,2},
    {1,3,3,1,1,1,1,1,1,2,2,1,1,1,1,1,1,3,3,1},
    {1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,0}};

// Carte pour ajout des arbres sur l'herbe
int carte2[NB_SPRITES_LARGEUR][NB_SPRITES_HAUTEUR]=
   {{0,1,1,1,1,1,1,1,4,2,2,4,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,4,2,2,4,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {4,3,3,4,4,4,4,4,4,2,2,4,4,4,4,4,4,3,3,4},
    {2,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,2},
    {2,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,2},
    {4,3,3,4,4,4,4,4,4,2,2,4,4,4,4,4,4,3,3,4},
    {1,1,1,1,1,1,1,1,4,2,2,4,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,4,2,2,4,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,4,2,2,4,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,4,2,2,4,4,4,4,4,4,4,4,4},
    {1,1,1,1,1,1,1,1,4,2,2,2,2,2,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,4,2,2,2,2,2,2,2,2,2,2,2},
    {1,1,1,1,1,1,1,1,4,2,2,4,4,4,4,4,4,4,4,4},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,3,3,3,3,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,4,2,2,4,1,1,1,1,1,1,1,0}};

// Carte pour placements des ressources
int objet[NB_SPRITES_LARGEUR][NB_SPRITES_HAUTEUR]=
                       {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

/**
 * \brief      Main pour lancer le jeu
 * \details    Gestion des evenements (clavier) de l'utilisateur pour lancer le jeu
 */
int main(int argc, char *argv[])
{
    score=0;

    // Variables pour ecriture avec TTF
    TTF_Font *police, *police2, *police3 = NULL;
    SDL_Color couleurBlanche = {255, 255, 255};
    SDL_Color couleurScore = {0, 0, 0};
    SDL_Surface *texteP1, *texteP2, *texteP3, *texteScore, *texteScore2 = NULL;

    TTF_Init();

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    /* Chargement des polices */
    police = TTF_OpenFont("ARCHRISTY.ttf", 65);
    police2 = TTF_OpenFont("ARCHRISTY.ttf", 35);
    police3 = TTF_OpenFont("ARCHRISTY.ttf", 26);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texteP1 = TTF_RenderText_Blended(police2, "HOW PLAY TO SQUIRREL ACORN : ", couleurBlanche);
    texteP2 = TTF_RenderText_Blended(police3, "PRESS 1 : NORMAL MODE", couleurBlanche);
    texteP3 = TTF_RenderText_Blended(police3, "PRESS 2 : NO CONSTRAINTS MODE (without obstacles)", couleurBlanche);
    // Init des positions des cases et du personnage
    initilisationPositions();

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, TAILLE_SPRITE, SDL_HWSURFACE); // Ouverture de la fenêtre
    if (ecran == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode video : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("2D GAME | SQUIRREL ACORN", NULL);

    // Autres variables pour les positions des ecritures
    SDL_Rect positionT;
    SDL_Rect positionT2;
    SDL_Rect positionT3;
    SDL_Rect positionT4;
    SDL_Rect positionT5;
    SDL_Rect positionT6;
    SDL_Rect positionScore;
    SDL_Rect positionScore2;
    positionT.x = 70;
    positionT.y = 185;
    positionT2.x = 45;
    positionT2.y = 265;
    positionT3.x = 27;
    positionT3.y = 365;
    positionT4.x = 70;
    positionT4.y = 215;
    positionT5.x = 170;
    positionT5.y = 275;
    positionT6.x = 20;
    positionT6.y = 330;
    positionScore.x = 75;
    positionScore.y = 265;
    positionScore2.x = 150;
    positionScore2.y = 345;

    // Affichage du texte
    SDL_BlitSurface(texteP1, NULL, ecran, &positionT4); /* Blit du texte */
    SDL_BlitSurface(texteP2, NULL, ecran, &positionT5); /* Blit du texte */
    SDL_BlitSurface(texteP3, NULL, ecran, &positionT6); /* Blit du texte */

    // Initialisation du tableau avec la position des ressources
    int tabR[4];
    tabR[0]=14;
    tabR[1]=138;
    tabR[2]=242;
    tabR[3]=359;

    SDL_Flip(ecran);

    //Gestion des evèvements ( inputs )
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
                    versHaut();
                    break;
                case SDLK_DOWN:
                    versBas();
                    break;
                case SDLK_RIGHT:
                    versDroite();
                    break;
                case SDLK_LEFT:
                    versGauche();
                    break;
                case SDLK_1:
                    // Affichage de la carte ...
                    formationCarte();
                    // ... et des objets.
                    placementObjets(1);
                    SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
                    SDL_Flip(ecran);
                    SDL_Delay(2000);
                    // Lancement de l'algo
                    score=dijkstra1(tabR,score);
                    if(score!=0){
                        // Affichage du score
                        char sc[13];
                        char sco[3];
                        strcat(sc,"You win ! Score : ");
                        sprintf(sco, "%d", score);
                        strcat(sc,sco);
                        /* Écriture du texte dans la SDL_Surface texte en mode Solid (rapide) */
                        texteScore = TTF_RenderText_Solid(police, sc, couleurScore);
                        SDL_BlitSurface(texteScore, NULL, ecran, &positionScore); /* Blit du texte */;
                        texteScore2 = TTF_RenderText_Solid(police2, "(PRESS ESCAPE TO QUIT)", couleurScore);
                        SDL_BlitSurface(texteScore2, NULL, ecran, &positionScore2); /* Blit du texte */;
                        SDL_Flip(ecran);}
                    break;
                case SDLK_KP1:
                    // Affichage de la carte ...
                    formationCarte();
                    // ... et des objets.
                    placementObjets(1);
                    SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
                    SDL_Flip(ecran);
                    SDL_Delay(2000);
                    // Lancement de l'algo
                    score=dijkstra1(tabR,score);
                    if(score!=0){
                        // Affichage du score
                        char sc[13];
                        char sco[3];
                        strcat(sc,"You win ! Score : ");
                        sprintf(sco, "%d", score);
                        strcat(sc,sco);
                        /* Écriture du texte dans la SDL_Surface texte en mode Solid (rapide) */
                        texteScore = TTF_RenderText_Solid(police, sc, couleurScore);
                        SDL_BlitSurface(texteScore, NULL, ecran, &positionScore); /* Blit du texte */;
                        texteScore2 = TTF_RenderText_Solid(police2, "(PRESS ESCAPE TO QUIT)", couleurScore);
                        SDL_BlitSurface(texteScore2, NULL, ecran, &positionScore2); /* Blit du texte */;
                        SDL_Flip(ecran);}
                    break;
                case SDLK_2:
                    // Affichage de la carte ...
                    formationCarte();
                    // ... et des objets.
                    placementObjets(1);
                    SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
                    SDL_Flip(ecran);
                    SDL_Delay(2000);
                    // Lancement de l'algo
                    score=dijkstra2(tabR,score);
                    if(score!=0){
                        // Affichage du score
                        char sc[13];
                        char sco[3];
                        strcat(sc,"You win ! Score : ");
                        sprintf(sco, "%d", score);
                        strcat(sc,sco);
                        /* Écriture du texte dans la SDL_Surface texte en mode Solid (rapide) */
                        texteScore = TTF_RenderText_Solid(police, sc, couleurScore);
                        SDL_BlitSurface(texteScore, NULL, ecran, &positionScore); /* Blit du texte */;
                        texteScore2 = TTF_RenderText_Solid(police2, "(PRESS ESCAPE TO QUIT)", couleurScore);
                        SDL_BlitSurface(texteScore2, NULL, ecran, &positionScore2); /* Blit du texte */;
                        SDL_Flip(ecran);}
                    break;
                case SDLK_KP2:
                    // Affichage de la carte ...
                    formationCarte();
                    // ... et des objets.
                    placementObjets(1);
                    SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
                    SDL_Flip(ecran);
                    SDL_Delay(2000);
                    // Lancement de l'algo
                    score=dijkstra2(tabR,score);
                    if(score!=0){
                        // Affichage du score
                        char sc[13];
                        char sco[3];
                        strcat(sc,"You win ! Score : ");
                        sprintf(sco, "%d", score);
                        strcat(sc,sco);
                        /* Écriture du texte dans la SDL_Surface texte en mode Solid (rapide) */
                        texteScore = TTF_RenderText_Solid(police, sc, couleurScore);
                        SDL_BlitSurface(texteScore, NULL, ecran, &positionScore); /* Blit du texte */;
                        texteScore2 = TTF_RenderText_Solid(police2, "(PRESS ESCAPE TO QUIT)", couleurScore);
                        SDL_BlitSurface(texteScore2, NULL, ecran, &positionScore2); /* Blit du texte */;
                        SDL_Flip(ecran);}
                    break;
                    case SDLK_ESCAPE:
                        // Pour quitter le jeu
                        exit(0);
                    break;
            }
            break;
        }
    }

    // Liberation de la surface
    SDL_FreeSurface(sprites);

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_Quit();


    return EXIT_SUCCESS; // Fermeture du programme
}

/**
 * \brief      Fonction d'affichage de la carte
 * \details    Affichage de la carte selon l'enum des cases (chemin, herbe...) et de la carte (tableau a 2 dimensions)
 */
void formationCarte()
{
    for(j = 0;j<NB_SPRITES_LARGEUR;j++)
    {
        for(i=0;i<NB_SPRITES_HAUTEUR;i++)
        {

            PosFinal.x = j*TAILLE_SPRITE;
            PosFinal.y = i*TAILLE_SPRITE;

            switch(carte[i][j])
            {
                case CHEMIN:
                    SDL_BlitSurface(sprites, &positionChemin, ecran, &PosFinal);
                    break;
                case HERBE:
                    SDL_BlitSurface(sprites, &positionHerbe, ecran, &PosFinal);
                    break;
                case EAU:
                    SDL_BlitSurface(sprites, &positionEau, ecran, &PosFinal);
                    break;
                case MUR:
                    SDL_BlitSurface(sprites, &positionMur, ecran, &PosFinal);
                    break;
            }

            switch(carte2[i][j])
            {
                case CHEMIN:
                    SDL_BlitSurface(sprites, &positionChemin, ecran, &PosFinal);
                    break;
                case HERBE:
                    SDL_BlitSurface(sprites, &positionHerbe, ecran, &PosFinal);
                    break;
                case EAU:
                    SDL_BlitSurface(sprites, &positionEau, ecran, &PosFinal);
                    break;
                case MUR:
                    SDL_BlitSurface(sprites, &positionMur, ecran, &PosFinal);
                    break;
                case ARBRE:
                    SDL_BlitSurface(sprites, &positionArbre, ecran, &PosFinal);
                    break;
            }
        }
    }
}

/**
 * \brief      Methode pour rafraichir l'ecran selon la position du personnage
 */
void rafraichissementPositionPerso()
{
            PosFinal.x = posPerso.x;
            PosFinal.y = posPerso.y;

            i=posPerso.y/TAILLE_SPRITE;
            j=posPerso.x/TAILLE_SPRITE;

            switch(carte[i][j])
            {
                case CHEMIN:
                    SDL_BlitSurface(sprites, &positionChemin, ecran, &PosFinal);
                    break;
                case HERBE:
                    SDL_BlitSurface(sprites, &positionHerbe, ecran, &PosFinal);
                    break;
                case EAU:
                    SDL_BlitSurface(sprites, &positionEau, ecran, &PosFinal);
                    break;
                case MUR:
                    SDL_BlitSurface(sprites, &positionMur, ecran, &PosFinal);
                    break;
            }
            switch(carte2[i][j])
            {
                case CHEMIN:
                    SDL_BlitSurface(sprites, &positionChemin, ecran, &PosFinal);
                    break;
                case HERBE:
                    SDL_BlitSurface(sprites, &positionHerbe, ecran, &PosFinal);
                    break;
                case EAU:
                    SDL_BlitSurface(sprites, &positionEau, ecran, &PosFinal);
                    break;
                case MUR:
                    SDL_BlitSurface(sprites, &positionMur, ecran, &PosFinal);
                    break;
                case ARBRE:
                    SDL_BlitSurface(sprites, &positionArbre, ecran, &PosFinal);
                    break;
            }
}

/**
 * \brief      Placement des ressources sur la carte
 */
void placementObjets(int t)
{
    if(t==1)
    {
        for(j = 0;j<NB_SPRITES_LARGEUR;j++)
        {
            for(i=0;i<NB_SPRITES_HAUTEUR;i++)
            {

                PosFinal.x = j*TAILLE_SPRITE;
                PosFinal.y = i*TAILLE_SPRITE;

                positionObjet.x = 0;
                positionObjet.y = 0;
                positionObjet.w = TAILLE_SPRITE;
                positionObjet.h = TAILLE_SPRITE;

                if(objet[i][j]==1)
                {
                        SDL_BlitSurface(gland, &positionObjet, ecran, &PosFinal);
                        break;
                }
            }
        }
    }
}

/**
 * \brief      Methode de gestion du ramassage des ressources
 * \details    Gestion selon la position des ressources et du personnage
 */
void gestionRamassage()
{
    for(j = 0;j<NB_SPRITES_LARGEUR;j++)
    {
        for(i=0;i<NB_SPRITES_HAUTEUR;i++)
        {
            if(objet[i][j]==1)
            {
                if((posPerso.x/TAILLE_SPRITE==i)&&(posPerso.y/TAILLE_SPRITE==j))
                {
                    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                    formationCarte();
                    objet[i][j]=0;
                    placementObjets(1);
                    //SDL_BlitSurface(perso, &positionPerso, ecran, &posPerso);
                    //SDL_Flip(ecran);
                }
            }
        }
    }
}
