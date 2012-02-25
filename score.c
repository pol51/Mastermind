#include "score.h"
#include <string.h>
#include <stdio.h>

score table_score[SIZE_SCORE + 1];	//tableau des scores
static FILE * file;					//fichier de score

//lecture de la table des scores
void score_init()
{
	int nbr = 0;
	
	file = fopen(FILE_NAME, "ab+");
    if (file == NULL)
		new_file();
	else
	{   
		fseek(file, 0, SEEK_END);
		nbr = ftell(file) / sizeof(struct score);
		fclose(file);
    }
	if (nbr != SIZE_SCORE)
		new_file();
	
	charger_score();
	score_set(&table_score[SIZE_SCORE], "AAA", MAX_SCORE);
	score_trie();
}

//initialisation d'un nouveau fichier de score
void new_file()
{
	score tmp_score;
	int i;
	
	for (i = 0; i < SIZE_SCORE + 1; i++)
	{
		score_set(&tmp_score, "AAA", 10);
		score_write(tmp_score, i);
	}
}

//définition d'un score
void score_set(score * tmp_score, char nom[SIZE_NOM], int score)
{
	strcpy(tmp_score->nom, nom);
	tmp_score->score = score;
}

//insertion du score à l'emplacement (écrasement)
void score_write(score tmp_sco, int id)
{
	file = fopen(FILE_NAME, "rb+");
	if (file != NULL)
    {
        fseek(file, id * sizeof(struct score), SEEK_SET);
        fwrite(&tmp_sco, sizeof(struct score), 1, file);
        fclose(file);
    }
}


//récupère les scores dans le fichier
void charger_score()
{
	file = fopen(FILE_NAME, "ab+");
	if (file != NULL)
	{
		fseek(file, 0, SEEK_SET);
		fread(table_score, sizeof(struct score), SIZE_SCORE, file);
		fclose(file);
	}
}

//sauve les scores dans le fichier
void sauver_score()
{
	file = fopen(FILE_NAME, "wb+");
	if (file != NULL)
	{
		fseek(file, 0, SEEK_SET);
		fwrite(table_score, sizeof(struct score), SIZE_SCORE, file);
		fclose(file);
	}
}

//affiche les scores
void print_score()
{
	int i;
	
	printf("\nTableau des scores:\n");
	printf("*******************\n");
	for (i = 0; i < SIZE_SCORE; i++)
		printf("%d\t%16s\t%d\n", i + 1,
			table_score[i].nom, table_score[i].score);
	printf("\n");
}

//fonction de comparaison de deux scores
int score_cmp(score * sc1, score * sc2)
{
	return ((sc1->score) - (sc2->score));
	
}

//trie le tableau des scores
void score_trie()
{
	qsort(table_score, SIZE_SCORE + 1, sizeof(struct score), score_cmp);
	sauver_score();
}

//revoie le dernier score
int score_last()
{
	return table_score[SIZE_SCORE].score;
}

//demande le nom si dans le classement
void score_ask(int sc)
{
	if (sc <= score_last())
	{
		char nom[SIZE_NOM + 1];
		
		printf("Vous entrez dans le tableau des scores!!!\nNom: ");
		scanf("%s", nom);
		score_set(&table_score[SIZE_SCORE], nom, sc);
		score_trie();
	}
}
