#include "mm.h"
#include "const.h"
#include <math.h>
#include <time.h>
#include <stdio.h>

//variables de jeu
combinaison comb_nj;
combinaison comb_j;

//initialisation aléatoire d'une combinaison
void comb_init_rand()
{
	int i;
	
	//initialisation du générateur
	srand(time(NULL));
    
	//affectation des valeurs
	for (i = 0; i < NB_POSITIONS; i++)
		comb_nj[i] = (rand() % NB_COULEURS) + 1;
	
	for (i = 0; i < NB_POSITIONS; i++)
		comb_j[i] = comb_nj[i];
}

//initialisation à 1 de la combianison du joueur
void comb_init()
{
	int i;
	
	//affectation des valeurs
	for (i = 0; i < NB_POSITIONS; i++)
		comb_j[i] = 1;
}

//boucle de jeu
int main_game()
{
	int gagne = 0;
	int tour = 0;
	
	do
	{
		tour++;
		comb_saisie(&comb_j, tour);
		gagne = comb_test(tour);
	}
	while ((tour < TOURS) && (gagne < 1));
		
	msg_end(gagne, tour, comb_nj);
	
	if (!gagne) tour = TOURS + 1;
	
	return tour;
}

int comb_test(int tour)
{
	int i, j;			//variables de boucles
	int ok = 0, in = 0;	//compeurs de caracteres bon ou mal placés
	
	int done_j[NB_POSITIONS], done_nj[NB_POSITIONS];
	
	for (i = 0; i < NB_POSITIONS; i++)
	{
		done_j[i]  = 0;
		done_nj[i] = 0;
	}
	
	//contrôle de correspondence
	for (i = 0; i < NB_POSITIONS; i++)
		if (comb_nj[i] == comb_j[i])
		{
			done_j[i]  = 1;
			done_nj[i] = 1;
			ok ++;
		}

	//contrôle de présence
	for (i = 0; i < NB_POSITIONS; i++)
		for (j = 0; j < NB_POSITIONS; j++)
			if ((comb_nj[j] == comb_j[i]) &&
				(done_nj[j] == 0) && (done_j[i] == 0))
			{
				done_j[i]  = 1;
				done_nj[j] = 1;
				in ++;
			}
	
	//affichage des caractères bon ou mal placée
	diag_affiche(tour, ok, in);
	
	return (ok >= NB_POSITIONS);
}
