
#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "mes_fonctions.h"

// Cette fonction permet de creer un arbre (elle initialise toutes les valeurs de la structure noeud.
Noeud* createArbre(unsigned char*** tableau3D,int largeurImage,int hauteurImage)
{
    Noeud* Racine = malloc(sizeof(Noeud));
    Racine->tab=tableau3D;
    Racine->droite=NULL;
    Racine->gauche=NULL;
    Racine->largeur=largeurImage;
    Racine->hauteur=hauteurImage;

    return Racine;
}

// Cette fonction permet de réduire la largeur de l'image en changeant la valeur des pixels en faisant la moyenne de deux  pixels cote a cote  ce qui reduit la largeur. Elle est appelée quand on va dans le fils Droit dans decomposeImage (voir pdf).
unsigned char*** ReduceL(unsigned char*** tableau,int largeur,int hauteur)
{
    int i,j;
    unsigned char*** tableau2;

    tableau2=malloc(3*sizeof(*tableau2));

    for(i=0 ; i < 3 ; i++)
    {
        tableau2[i] = malloc(largeur * sizeof(**tableau2));
    }
    
    for(i=0 ; i < 3 ; i++)
    {
        for(j=0 ; j < largeur ; j++)
        {
            tableau2[i][j] = malloc(hauteur * sizeof(***tableau2));
        }
    }

    for ( i = 0; i < hauteur; i++ )
    {
        for ( j = 0 ; j < largeur; j++)
        {
            tableau2[0][j][i] = ( tableau[0][(j*2)][i] + tableau[0][(j*2)+1][i] ) / 2 ;
            tableau2[1][j][i] = ( tableau[1][(j*2)][i] + tableau[1][(j*2)+1][i] ) / 2;
            tableau2[2][j][i] = ( tableau[2][(j*2)][i] + tableau[2][(j*2)+1][i] ) / 2;
        }
    }
    return tableau2;
}

// Cette fonction permet de faire la différence entre les valeurs de 2 pixels cote a cote horizontalement, elle est appelée quand on va dans le fils gauche dans decomposeImage (voir pdf). 
unsigned char*** DiffH(unsigned char *** tableau,int largeur,int hauteur)
{
    int i,j;
    unsigned char*** tableau2;

    tableau2=malloc(3*sizeof(*tableau2));

    for(i=0 ; i < 3 ; i++)
    {
        tableau2[i] = malloc(largeur * sizeof(**tableau2));

    }
    for(i=0 ; i < 3 ; i++)
    {
        for(j=0 ; j < largeur ; j++)
        {
            tableau2[i][j] = malloc(hauteur * sizeof(***tableau2));
        }
    }

    for ( i = 0; i < hauteur; i++ )
    {
        for ( j = 0 ; j < largeur; j++)
        {
            tableau2[0][j][i] = ( tableau[0][j*2][i] - tableau[0][j*2+1][i] );
            tableau2[1][j][i] = ( tableau[1][j*2][i] - tableau[1][j*2+1][i] );
            tableau2[2][j][i] = ( tableau[2][j*2][i] - tableau[2][j*2+1][i] );
        }
    }
    return tableau2;
}

// Cette fonction permet de réduire la hauteur de l'image en changeant la valeur des pixels en faisant la moyenne de deux pixels cote a cote ce qui réduit la hauteur. Elle est appelée quand on va dans le fils droit du fils droit dans decomposeImage (voir pdf).
unsigned char*** ReduceH(unsigned char *** tableau,int largeur,int hauteur)
{
    int i,j;
    unsigned char*** tableau2;

    tableau2=malloc(3*sizeof(*tableau2));

    for(i=0 ; i < 3 ; i++)
    {
        tableau2[i] = malloc(largeur * sizeof(**tableau2));
    }
    for(i=0 ; i < 3 ; i++)
    {
        for(j=0 ; j < largeur ; j++)
        {
            tableau2[i][j] = malloc(hauteur * sizeof(***tableau2));
        }
    }

    for ( i = 0; i < hauteur; i++ )
    {
        for ( j = 0 ; j < largeur; j++)
        {
            tableau2[0][j][i] = ( tableau[0][j][i*2] + tableau[0][j][i*2+1] ) / 2 ;
            tableau2[1][j][i] = ( tableau[1][j][i*2] + tableau[1][j][i*2+1] ) / 2;
            tableau2[2][j][i] = ( tableau[2][j][i*2] + tableau[2][j][i*2+1] ) / 2;
        }
    }

    return tableau2;
}

// Cette fonction permet faire la différence entre les valeurs de 2 pixels cote a cote verticalement, elle est appelée quand on va dans le fils gauche du fils gauche et le fils gauche du fils droit (voir pdf).
unsigned char*** DiffV(unsigned char*** tableau,int largeur,int hauteur)
{
    int i,j;
    unsigned char*** tableau2;
    tableau2=malloc(3*sizeof(*tableau2));

    for(i=0 ; i < 3 ; i++)
    {
        tableau2[i] = malloc(largeur * sizeof(**tableau2));
    }
    for(i=0 ; i < 3 ; i++)
    {
        for(j=0 ; j < largeur ; j++)
        {
            tableau2[i][j] = malloc(hauteur * sizeof(***tableau2));
        }
    }

    for ( i = 0; i < hauteur; i++ )
    {
        for ( j = 0 ; j < largeur; j++)
        {
            tableau2[0][j][i] = ( tableau[0][j][i*2] - tableau[0][j][i*2+1] );
            tableau2[1][j][i] = ( tableau[1][j][i*2] - tableau[1][j][i*2+1] );
            tableau2[2][j][i] = ( tableau[2][j][i*2] - tableau[2][j][i*2+1] );
        }
    }
    return tableau2;
}

// Cette fonction permet de décomposer l'image en arbre binaire et appelle les différentes fonctions nécessaires a la decomposition de l'image (et pour la retrecir).
Noeud* decomposeImage(Noeud* Racine)
{
    Noeud* filsDroit = (Noeud*)malloc(sizeof(Noeud));
    Noeud* filsGauche = (Noeud*)malloc(sizeof(Noeud));
    Noeud* filsGaucheG = (Noeud*)malloc(sizeof(Noeud));
    Noeud* filsGaucheD = (Noeud*)malloc(sizeof(Noeud));
    Noeud* filsDroitG = (Noeud*)malloc(sizeof(Noeud));
    Noeud* filsDroitD = (Noeud*)malloc(sizeof(Noeud));

    Racine->droite=filsDroit;
    Racine->gauche=filsGauche;

    filsDroit->hauteur=Racine->hauteur;
    filsDroit->largeur=Racine->largeur/2;
    filsDroit->tab=ReduceL(Racine->tab,filsDroit->largeur,filsDroit->hauteur); 
    filsDroit->droite=filsDroitD;
    filsDroit->gauche=filsDroitG;

    filsGauche->hauteur=Racine->hauteur;
    filsGauche->largeur=Racine->largeur/2;
    filsGauche->tab=DiffH(Racine->tab,filsGauche->largeur,filsGauche->hauteur);
    filsGauche->droite=filsGaucheD;
    filsGauche->gauche=filsGaucheG;
    
    filsDroitG->hauteur=filsDroit->hauteur/2;
    filsDroitG->largeur=filsDroit->largeur;
    filsDroitG->tab=DiffV(filsDroit->tab,filsDroitG->largeur,filsDroitG->hauteur);
    filsDroitG->droite=NULL;
    filsDroitG->gauche=NULL;

    filsGaucheG->hauteur=filsGauche->hauteur/2;
    filsGaucheG->largeur=filsGauche->largeur;
    filsGaucheG->tab=DiffV(filsGauche->tab,filsGaucheG->largeur,filsGaucheG->hauteur);
    filsGaucheG->droite=NULL;
    filsGaucheG->gauche=NULL;

    filsDroitD->hauteur=filsGauche->hauteur/2;
    filsDroitD->largeur=filsDroit->largeur;
    filsDroitD->tab=ReduceH(filsDroit->tab,filsDroitD->largeur,filsDroitD->hauteur);
    filsDroitD->droite=NULL;
    filsDroitD->gauche=NULL;
    
    filsGaucheD->hauteur=filsGauche->hauteur/2;
    filsGaucheD->largeur=filsGauche->largeur;
    filsGaucheD->tab=ReduceH(filsGauche->tab,filsGaucheD->largeur,filsGaucheD->hauteur);
    filsGaucheD->droite=NULL;
    filsGaucheD->gauche=NULL;
    
    return filsDroitD; // Retourne l'image plus petite (rétrecie en 2).
}

// Cette fonction rappelle la fonction decomposeImage autant de fois que le niveau passé en parametre 
Noeud* decomposeNniveau(Noeud* Racine,int n)
{
    Noeud* Fils=NULL;

    if (n>0)
    {
        Fils=decomposeImage(Racine);
        decomposeNniveau(Fils, n-1);
    }
    return Racine;
}

// Cette fonction permet sauvegarder chaque etage de l'arbre (chaque noeud et feuille) niveai apres niveau
Noeud* sauveArbreImage(Noeud* Racine, int level) 
{
    int k;
    Noeud** tableau2D;
    tableau2D = malloc(50 * sizeof(*tableau2D));
    
    for(k=0;k<level;k++)
    {
        Racine=Racine->droite->droite;
        tableau2D[k]=Racine;
    }
    return tableau2D;
}

// Cette fonction permet de montrer les 4 feuilles de notre arbre binaire 
unsigned char*** montreImages(Noeud* Racine,int largeur,int hauteur)
{
    unsigned char*** tableau3D;
    int i,j;
    tableau3D= malloc(3 * sizeof(*tableau3D));

    for(i=0 ; i < 3 ; i++)
    {
        tableau3D[i] = malloc(largeur * sizeof(**tableau3D));
    }

    for(i=0 ; i < 3 ; i++)
    {
        for(j=0 ; j < largeur ; j++)
        {
            tableau3D[i][j] = malloc(hauteur * sizeof(***tableau3D));

        }
    }

    for( i=0 ; i<Racine->droite->droite->hauteur ; i++)
    {
        for ( j=0 ; j<Racine->droite->droite->largeur ; j++)
        {
            tableau3D[0][j][i]=Racine->droite->droite->tab[0][j][i];
            tableau3D[1][j][i]=Racine->droite->droite->tab[1][j][i];
            tableau3D[2][j][i]=Racine->droite->droite->tab[2][j][i];

            tableau3D[0][j+Racine->droite->droite->largeur][i]=Racine->droite->gauche->tab[0][j][i];
            tableau3D[1][j+Racine->droite->droite->largeur][i]=Racine->droite->gauche->tab[1][j][i];
            tableau3D[2][j+Racine->droite->droite->largeur][i]=Racine->droite->gauche->tab[2][j][i];

            tableau3D[0][j][i+Racine->droite->droite->hauteur]=Racine->gauche->droite->tab[0][j][i];
            tableau3D[1][j][i+Racine->droite->droite->hauteur]=Racine->gauche->droite->tab[1][j][i];
            tableau3D[2][j][i+Racine->droite->droite->hauteur]=Racine->gauche->droite->tab[2][j][i];

            tableau3D[0][j+Racine->droite->droite->largeur][i+Racine->droite->droite->hauteur]=Racine->gauche->gauche->tab[0][j][i];
            tableau3D[1][j+Racine->droite->droite->largeur][i+Racine->droite->droite->hauteur]=Racine->gauche->gauche->tab[0][j][i];
            tableau3D[2][j+Racine->droite->droite->largeur][i+Racine->droite->droite->hauteur]=Racine->gauche->gauche->tab[0][j][i];
        }
    }
        return tableau3D;
}
