#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

typedef struct personnage{
    int orientation;//0:N, 1:E, 2:S, 3:O
    int positionHorizontalPrec;//Position n-1 pour l'orientation du personnage à l'instant n
    int positionVerticalPrec;//Position n-1
    int positionHorizontal;
    int positionVertical;

}personnage;


#endif // PERSONNAGE_H_INCLUDED
