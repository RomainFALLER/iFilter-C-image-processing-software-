#include  <stdlib.h>		// Pour pouvoir utiliser void exit(int)
#include "GfxLib.h"		// Seul cet include est necessaire pour faire du graphique
#include "mes_fonctions.h"
#include <stdio.h>			// Inclusion classique
#include <stdbool.h>


int i;
static char PAGE;

int main(int argc, char **argv)
{
	// Initialisation de l'acceleration graphique si elle existe
	initialiseGfx(argc, argv);

	// On ouvre la fenetre de notre application
	prepareFenetreGraphique("iFilter ", LargeurFenetre, HauteurFenetre);

	// Lance la boucle GLUT et aiguille les evenements sur la fonction gestionEvenements ci-apres,
	//	qui elle-meme utilise fonctionAffichage ci-dessous
	lanceBoucleEvenements();
	// On ne sort jamais de la fonction lanceBoucleEvenements, c'est pourquoi tout ce qui est
	// ecrit ci-apres ne sera jamais execute
	// Jamais execute, le programme se terminera ailleurs
	return 0;
}


// La fonction de gestion des evenements, appelee automatiquement par le systeme
// des qu'une evenement survient.
// Le but est que ce soit le systeme qui gere quand il est necessaire de faire un trace,
// qui suive les actions sur la souris et le clavier, etc.
// Il ne nous reste plus qu'a reagir en fonction de ces evenements
void gestionEvenement(EvenementGfx evenement)
{
	static unsigned char*** tableau3D;
    static DonneesImageRGB *monImage = NULL; // L'image a afficher au centre de l'ecran ( image de base )
    static DonneesImageRGB *maNouvelleImage = NULL; // la nouvelle image a afficher au centre de l'ecran après passage par les fonctions
    Noeud* RACINE;
    int seuil=0;   
    
	// En fonction de l'evenement envoye par le systeme...
	switch (evenement)
	{
			 // Le message "Initialisation" est envoye une seule fois, au debut du programme
			// Il faut y placer tout ce qui permet d'initialiser le programme
		case Initialisation:
			PAGE='A';
			monImage = lisBMPRGB("landscape.bmp");
            demandeAnimation_ips(50);
			break;
			// Le systeme demande au programme de dessiner le fenetre
		case Affichage:
			if(PAGE=='A'){
							Accueil();
						}
			if(PAGE=='B'){
							interfacePhoto();						
		if (monImage != NULL) // Si l'image a pu etre lue
        {
            // On affiche l'image
            ecrisImage((largeurFenetre()-monImage->largeurImage)/2, (hauteurFenetre()-monImage->hauteurImage+80)/2, monImage->largeurImage, monImage->hauteurImage, monImage->donneesRGB);
        }
					    }                
			break;
		case Clavier: // Une touche du clavier a ete pressee
			switch (caractereClavier())
			{
				case 'Q': // Pour sortir quelque peu proprement du programme
				case 'q':
					exit(0);
					printf("df");
					break;
				case 'R':
				case 'r':
					rafraichisFenetre(); // Demande explicite de reaffichage
					break;
			}
			break;

		case BoutonSouris: // Un bouton de la souris a ete appuye
		
			if ((PAGE=='A') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>200) && (abscisseSouris()<800) && (ordonneeSouris()>250) && (ordonneeSouris()<310))
			{
				rafraichisFenetre();
				PAGE='B';
			}			
			if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>20) && (abscisseSouris()<135) && (ordonneeSouris()>350) && (ordonneeSouris()<450))
			{
			monImage = lisBMPRGB("landscape.bmp");
            ecrisImage((largeurFenetre()-monImage->largeurImage)/2, (hauteurFenetre()-monImage->hauteurImage)/2, monImage->largeurImage, monImage->hauteurImage, monImage->donneesRGB);
			}
			if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>20) && (abscisseSouris()<135) && (ordonneeSouris()>200) && (ordonneeSouris()<300))
			{
			monImage = lisBMPRGB("oiseau.bmp");
            ecrisImage((largeurFenetre()-monImage->largeurImage)/2, (hauteurFenetre()-monImage->hauteurImage)/2, monImage->largeurImage, monImage->hauteurImage, monImage->donneesRGB);
			}

			if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>940) && (abscisseSouris()<980) && (ordonneeSouris()>590) && (ordonneeSouris()<630) )
			{
				exit(0);
			}
						if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>20) && (abscisseSouris()<323) && (ordonneeSouris()>40) && (ordonneeSouris()<110) )
			{
				printf("Négatif");
				tableau3D = cree3Matrices(monImage); 
				tableau3D=effetNegatif(tableau3D,monImage->largeurImage,monImage->hauteurImage);
				maNouvelleImage=creeImage(tableau3D,monImage->largeurImage,monImage->hauteurImage);
				monImage = maNouvelleImage;
			}

			if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>350) && (abscisseSouris()<653) && (ordonneeSouris()>40) && (ordonneeSouris()<110) )
			{
				printf("Nuances de gris");
				tableau3D = cree3Matrices(monImage); 
				tableau3D=couleur2NG(tableau3D,monImage->largeurImage,monImage->hauteurImage);
				maNouvelleImage=creeImage(tableau3D,monImage->largeurImage,monImage->hauteurImage);
				monImage = maNouvelleImage;
			}
			if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>680) && (abscisseSouris()<983) && (ordonneeSouris()>40) && (ordonneeSouris()<110) )
			{
				  printf("\n Seuil choisi:   ");
				  int test=scanf("%d",&seuil);
                  test++;              
                  tableau3D = cree3Matrices(monImage); 
                  tableau3D=seuillageNG(seuil,tableau3D,monImage->largeurImage,monImage->hauteurImage);
				  maNouvelleImage=creeImage(tableau3D,monImage->largeurImage,monImage->hauteurImage);
                  monImage = maNouvelleImage;
			}
				if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>20) && (abscisseSouris()<160) && (ordonneeSouris()>550) && (ordonneeSouris()<640) )
			{
				                			    printf("dfsfd");
                tableau3D = cree3Matrices(monImage); 
			    RACINE = createArbre(tableau3D, monImage->largeurImage, monImage->hauteurImage);
                decomposeNniveau(RACINE,10);
                sauveArbreImage(RACINE,10); 
				maNouvelleImage=creeImage(RACINE->droite->droite->tab,RACINE->droite->droite->largeur,RACINE->droite->droite->hauteur);
                 monImage = maNouvelleImage;			
                  }
                 if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>860) && (abscisseSouris()<970) && (ordonneeSouris()>350) && (ordonneeSouris()<450) )
			{
				printf("Aff total");				
				tableau3D = cree3Matrices(monImage);
                RACINE = createArbre(tableau3D, monImage->largeurImage, monImage->hauteurImage);
                decomposeNniveau(RACINE,10);
                sauveArbreImage(RACINE,10); 
                tableau3D=montreImages(RACINE,monImage->largeurImage,monImage->hauteurImage);
                maNouvelleImage=creeImage(tableau3D,monImage->largeurImage,monImage->hauteurImage);
                monImage=maNouvelleImage;
			}
			if ((PAGE=='B') && (etatBoutonSouris() == GaucheAppuye) && (abscisseSouris()>160) && (abscisseSouris()<848) && (ordonneeSouris()>140) && (ordonneeSouris()<560) )
			{
			monImage = lisBMPRGB("landscape.bmp");
            ecrisImage((largeurFenetre()-monImage->largeurImage)/2, (hauteurFenetre()-monImage->hauteurImage)/2, monImage->largeurImage, monImage->hauteurImage, monImage->donneesRGB);	
			}
			break;
		// Les messages suivants ne sont pas traites ici, mais existent
		case Inactivite:
        	case ClavierSpecial:
		case Souris:
		case Redimensionnement:
	 		 break;
	}
}

