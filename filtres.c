#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "mes_fonctions.h" // Cet include permet de manipuler des fichiers BMP

/* Fonction qui prend en parametre le tableau 3D, la largeur , la hauteur et qui modifie les valeurs du tableau (on fait 255 - couleurActuel)
 * Elle permet de creer l'effet négatif.*/
unsigned char*** effetNegatif(unsigned char*** tableau3D, int largeur, int hauteur)
{
    int i,j;
    for ( i = 0;i < hauteur; i ++ )
    {
        for ( j = 0 ; j < largeur; j ++)
        {  
            tableau3D[0][j][i] = 255 - tableau3D[0][j][i];
            tableau3D[1][j][i] = 255 - tableau3D[1][j][i];
            tableau3D[2][j][i] = 255 - tableau3D[2][j][i];
        }
    }
    return tableau3D;
}

/* Fonction qui prend en parametre le tableau 3D, la largeur , la hauteur et qui modifie les valeurs du tableau (on fait 0.0721*bleu + 0.7154*vert + 0.2125*rouge).
 * Elle permet de creer l'effet Niveau de gris.*/
 unsigned char*** couleur2NG(unsigned char*** tableau3D, int largeur, int hauteur)
{
    int i,j;
    for ( i = 0 ; i < hauteur; i ++ )
    {
        for ( j = 0 ; j < largeur; j ++)
        {
            tableau3D[0][j][i] = 0.0721*tableau3D[0][j][i] + 0.7154*tableau3D[1][j][i] + 0.2125*tableau3D[2][j][i];
            tableau3D[1][j][i] = 0.0721*tableau3D[0][j][i] + 0.7154*tableau3D[1][j][i] + 0.2125*tableau3D[2][j][i];
            tableau3D[2][j][i] = 0.0721*tableau3D[0][j][i] + 0.7154*tableau3D[1][j][i] + 0.2125*tableau3D[2][j][i];
        }
    }
    return tableau3D;
}

/* Fonction qui prend en parametre le tableau 3D, la largeur , la hauteur et qui modifie les valeurs du tableau par rapport à la valeur du seuil.
 * Elle permet de creer l'effet de Seuillage.*/
unsigned char*** seuillageNG(int seuil, unsigned char*** tableau3D, int largeur, int hauteur)
{
    int i,j;
    for ( i = 0 ; i < hauteur; i ++ )
    {
        for ( j = 0 ; j < largeur; j ++)
        {
            if ( tableau3D[0][j][i] > seuil )
            {
                tableau3D[0][j][i]=255;
            }
            else{
                tableau3D[0][j][i]=0;
            }
            if ( tableau3D[1][j][i] > seuil )
            {
                tableau3D[1][j][i]=255;
            }
            else{
                tableau3D[1][j][i]=0;
            }
            if ( tableau3D[2][j][i] > seuil )
            {
                tableau3D[2][j][i]=255;
            }
            else{
                tableau3D[2][j][i]=0;
            }
        }
    }
    return tableau3D;
}
