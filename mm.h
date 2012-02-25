#ifndef __MM_H
#define __MM_H

#include "const.h"

//type "combinaison"
typedef int combinaison[NB_POSITIONS];

//initialisation aléatoire de la combianison à deviner
void comb_init_rand();

//initialisation à 1 de la combianison du joueur
void comb_init();

//boucle de jeu
int main_game();

//test des combinaisons
int comb_test(int tour);

#endif
