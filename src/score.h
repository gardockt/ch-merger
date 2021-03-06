#ifndef SCORE_H
#define SCORE_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SCORES_HASH_LENGTH		32
#define SCORES_DATA_LENGTH		50

typedef struct {
	char			id;
	char			unknown;
	char			difficulty;
	unsigned char	percentage;
	char			fullCombo;
	int				speed;
	unsigned char	stars;
	char			modifiers;
	uint32_t		highscore;
} instr_t;

typedef struct {
	char*			hash;
	char			instrCount;
	unsigned char	playCount;
	char*			unknown;
	instr_t*		instr;
} score_t;

int		scoreAlloc(score_t*);
void	scoreFree(score_t*);
void	scoreCopy(score_t*, score_t*);

#endif
