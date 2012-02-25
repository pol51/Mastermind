#ifndef __ES_H
#define __ES_H

#include "mm.h"

//initialisation SDL
void SDL_init();

//traduction en couleur
void couleur(int c, char image[FS_MAX]);

//affichage d'une balle
void case_affiche(int nimg, int tour, int pos);

//affichage du message de fin
void msg_end(int gagne, int tour, combinaison comb);

//saisie d'une combinaison
void comb_saisie(combinaison *comb, int tour);

//affichage des caractères bon ou mal placée
void diag_affiche(int tour, int ok, int in);

int final_pause();

#endif
