#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "mm.h"
#include "es.h"
#include "score.h"

int main()
{
	int score;
	
	do
	{
		SDL_init();
		comb_init_rand();
		comb_init();
		score = main_game();
		
		//score_init();
		//score_ask(score);
		//print_score();
		//sauver_score();
	}
	while(final_pause() == 2);
	
	return(EXIT_SUCCESS);
}
