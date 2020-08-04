#include "score.h"

int scoreAlloc(score_t* score) {
	score->hash		= malloc(32);
	score->unknown	= malloc(2);
	return score->hash != NULL && score->unknown != NULL;
}

void scoreFree(score_t* score) {
	if(score != NULL) {
		free(score->hash);
		free(score->unknown);
	}
	return;
}
