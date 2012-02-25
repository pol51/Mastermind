#ifndef __SCORE_H
#define __SCORE_H

#include "const.h"

#define MAX_SCORE	TOURS
#define SIZE_NOM	16
#define SIZE_SCORE	10
#define FILE_NAME	"mastermind.sco"

typedef struct score
{
	char nom[SIZE_NOM + 1];
	int score;
} score;

//lecture de la table des scores
void score_init();

//initialisation d'un nouveau fichier de score
void new_file();

//d�finition d'un score
void score_set(score * tmp_score, char nom[SIZE_NOM], int score);

//insertion du score � l'emplacement (�crasement)
void score_write(score tmp_sco, int id);

//r�cup�re les scores dans le fichier
void charger_score();

//sauve les scores dans le fichier
void sauver_score();

//fonction de comparaison de deux scores
int score_cmp(score * sc1, score * sc2);

//trie le tableau des scores
void score_trie();

//revoie le dernier score
int score_last();

//demande le nom si dans le classement
void score_ask();

#endif
