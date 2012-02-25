#ifndef __MM_H
#define __MM_H

#include "const.h"

//type "combinaison"
typedef int combinaison[NB_POSITIONS];

//initialisation al�atoire de la combianison � deviner
void comb_init_rand();

//initialisation � 1 de la combianison du joueur
void comb_init();

//boucle de jeu
int main_game();

//test des combinaisons
int comb_test(int tour);

#endif
