#include <stdio.h>
#include <stdlib.h>
#include "GfxLib.h"
#include "mes_fonctions.h"

//
//  graphique.c
//  Projet Jeu de la vie
//
//  Created by FALLER Romain, LO PINTO Tomas, LAVALL Philippe on 19/06/2014.
// 
//

/* Tout ce qui concerne le graphique de l'interface (boutons, ecritures, etc...) */
void interfacePhoto() 
{
			effaceFenetre(255,255,255);
			// On affiche du texte, mais cette fois en graphique
			epaisseurDeTrait(5);
			couleurCourante(0, 0, 0); // Choix de la couleur noire
			afficheChaine("iFilter", 50, 440, 600);


			// ******************* NOUS C'EST LIMAGE ICI *******************************************
			// On affiche le cadre
			couleurCourante(0,0,0);
			rectangle(158,138,850,562);

			// On affiche le cadre
			couleurCourante(255,255,255);
			rectangle(160,140,848,560);

			// On affiche la case négatif
			couleurCourante(137, 0, 0); 
			rectangle(20, 40, 323, 110);
			
			couleurCourante(0,0,0);
			epaisseurDeTrait(2);
			afficheChaine("Cliquez dans le cadre pour revenir a l'originale !",22,230,150);
			
			//Case
			couleurCourante(255,255,255);
			epaisseurDeTrait(2);
			afficheChaine("Negatif",22,130,65);

			// On affiche la case Gris
			couleurCourante(137,0,0);
			rectangle(350, 40, 653, 110);
			
			couleurCourante(255,255,255);
			epaisseurDeTrait(2);
			afficheChaine("Nuance de gris",22,410,65);
			
			//On affiche la case Seuillage
			couleurCourante(137,0,0);
			rectangle(680, 40, 983,110);
			couleurCourante(255,255,255);
			epaisseurDeTrait(2);
			afficheChaine("Seuilage",22,790,65);

			// On crée la case et affiche les traits sur la case Quitter
			couleurCourante(255,0,0);
			rectangle(940,590,980,630);
			couleurCourante(0,0,0);
			ligne(945,595,975,625);
			ligne(975,595,945,625);
			
			//Bouton Affichage niveau + 1	
			couleurCourante(71,71,71);
			rectangle(20,560,160,640);
			couleurCourante(255,255,255);
			epaisseurDeTrait(2);
			afficheChaine("Affichage niveau++",14,21,595);
			
			//Bouton Affichage complet
			couleurCourante(71,71,71);
			rectangle(860,350,970,450);
			couleurCourante(255,255,255);
			epaisseurDeTrait(2);
			afficheChaine("Affichage tot.",14,870,395);
			
			couleurCourante(137,0,0);
			rectangle(20,200,135,300);
			couleurCourante(255,255,255);
			afficheChaine("Oiseau",20,45,245);
			
			couleurCourante(137,0,0);
			rectangle(20,350,135,450);
			couleurCourante(255,255,255);
			afficheChaine("Paysage",20,40,395);
}

/*Tout ce qui concerne le graphique de l'accueil*/
void Accueil()
{
			effaceFenetre(255, 255, 255);

			//On affiche le cadre de lancement
			couleurCourante(0,0,0);
			rectangle(200,250,800,310);

			// On affiche la case de lancement
			couleurCourante(137,0,0);
			rectangle(210,260,790,300);
			couleurCourante(0,0,0);
			epaisseurDeTrait(9);
			afficheChaine("i F i l t e r", 50, 310,500);
			epaisseurDeTrait(3);
			afficheChaine("Commencer",30,420,270);
			epaisseurDeTrait(4);
			afficheChaine("By FALLER Romain", 20, 385,350);
			couleurCourante(137,0,0);
			epaisseurDeTrait(4);
			afficheChaine("ISEN TOULON", 20, 840,30);			
}



