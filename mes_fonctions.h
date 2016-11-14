#include "GfxLib.h"

// Largeur et hauteur par defaut de notre fenetre
#define LargeurFenetre 1000  
#define HauteurFenetre 650   
   

typedef struct
{
	int largeurImage;
	int hauteurImage;
	unsigned char *donneesRGB;/* Tableau de characteres qui recupere les données des pixels dans l'ordre bleu vert rouge*/ 
} DonneesImageRGB;

typedef struct Noeud 
{
    unsigned char*** tab;
    struct Noeud *droite;
    struct Noeud *gauche;
    int largeur;
    int hauteur;
}Noeud;

/* Fonction s'occupant de la liberation complete d'une structure DonneesImageRGB */
void libereDonneesImageRGB(DonneesImageRGB **structure);

/* Fonction essayant de lire le fichier passe en parametre, et renvoyant une structure
	contenant les informations de l'image en cas de succes, NULL sinon */
DonneesImageRGB *lisBMPRGB(char *nom);

/* Fonction ecrivant les informations de l'image dans le fichier passe en parametre.
	Renvoie faux en cas de probleme, vrai sinon */
bool ecrisBMPRGB_Dans(DonneesImageRGB *donneesImage, char *nom);


//Fonctions affichage Gfxlib (interface graphique):
void Accueil(); // Premiere page
void interfacePhoto(); // Image avec boutons

//Fonction d'evenement:
void gestionEvenement(EvenementGfx evenement); // Fonction qui gere appelle les fonctions selon les evenements (clic, etc...)

//Fonctions de l'image:
unsigned char*** cree3Matrices(DonneesImageRGB *monImage);  // Fonction qui recupere l'image et la range dans le tableau 3D
DonneesImageRGB* creeImage(unsigned char*** tableau3D, int largeur, int hauteur); // Fonction qui recupere le tableau 3D et renvoie le tout en une image

//Fonctions de filtres:
unsigned char*** effetNegatif(unsigned char*** tableau3D, int largeur, int hauteur); // Fonction qui recupere le tableau 3D et modifie l'image (les valeurs du tableau) => (Effet Negatif)
 unsigned char*** couleur2NG(unsigned char*** tableau3D, int largeur, int hauteur); // Fonction qui recupere le tableau 3D et modifie l'image (les valeurs du tableau) => (Effet Noir et Blanc)
unsigned char*** seuillageNG(int seuil, unsigned char*** tableau3D, int largeur, int hauteur); // Fonction qui recupere le tableau 3D et modifie l'image (les valeurs du tableau) => (Seuillage)

//Fonctions de compressions:
Noeud* createArbre(unsigned char*** tableau3D,int largeurImage,int hauteurImage); //Fonction qui crée l'arbre binaire
unsigned char*** ReduceL(unsigned char *** tableau,int largeur,int hauteur); // Fonction qui réduit l'image en largeur
unsigned char*** DiffH(unsigned char *** tableau,int largeur,int hauteur);  // Fonction qui fait la diff des pixels (voir pdf).
unsigned char*** ReduceH(unsigned char *** tableau,int largeur,int hauteur); // Fonction qui réduit l'image en hauteur
unsigned char*** DiffV(unsigned char*** tableau,int largeur,int hauteur); 
Noeud* decomposeImage(Noeud* Racine); // Décompose l'image en arbre binaire (défini dans cette fonction)
Noeud* decomposeNniveau(Noeud* Racine,int K); // Rappel de la fonction decomposeImage selon le niveau 
Noeud* sauveArbreImage(Noeud* Racine, int level) ; // Sauvegarde 
unsigned char*** montreImages(Noeud* Racine,int largeur,int hauteur); // Montre l'image a chaque niveau différent (

