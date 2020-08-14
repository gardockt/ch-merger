#ifndef SCORES_H
#define SCORES_H

#include <stdio.h>
#include <stdlib.h>

#include "score.h"

int		scoresOpen(const char*);
void	scoresClose();
int		scoresGetNext(score_t*);
int		scoresGetVersion();
int		scoresSave(FILE*, score_t);

#endif
