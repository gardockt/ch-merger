#ifndef SCORES_H
#define SCORES_H

#include <stdio.h>
#include <stdlib.h>

#include "score.h"

#define SCORES_HASH_LENGTH		32
#define SCORES_DATA_LENGTH		50

int		scoresOpen(const char*);
void	scoresClose();
int		scoresGetNext(score_t*);
int		scoresGetVersion();
int		scoresSave(FILE*, score_t);

#endif
