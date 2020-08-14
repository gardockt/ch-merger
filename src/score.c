#include "score.h"

int scoreAlloc(score_t* score) {
	score->hash		= malloc(32 + 1);
	score->unknown	= malloc(2);
	score->instr	= NULL;
	score->hash[32]	= '\0';
	return score->hash != NULL && score->unknown != NULL;
}

void scoreFree(score_t* score) {
	if(score != NULL) {
		free(score->hash);
		free(score->unknown);
		if(score->instr != NULL)
			free(score->instr);
	}
	return;
}

void scoreCopy(score_t* src, score_t* elem) {
	strcpy(src->hash, elem->hash);
	src->instrCount = elem->instrCount;
	src->playCount = elem->playCount;
	memcpy(src->unknown, elem->unknown, 2);
	src->instr = malloc(sizeof *src->instr * src->instrCount);
	memcpy(src->instr, elem->instr, sizeof *elem->instr * elem->instrCount);
}

