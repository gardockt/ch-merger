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

void scoreCopy(score_t* src, score_t* elem) {
	strcpy(src->hash, elem->hash);
	src->instrCount = elem->instrCount;
	src->playCount = elem->playCount;
	memcpy(&src->unknown, &elem->unknown, 2);
	memcpy(&src->instr, &elem->instr, sizeof elem->instr * elem->instrCount);
}

