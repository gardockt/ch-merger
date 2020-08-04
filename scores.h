#ifndef SCORES_H
#define SCORES_H

#include <stdio.h>
#include <stdlib.h>

#include "score.h"

#define SCORES_HEADER_LENGTH	8
#define SCORES_DATA_LENGTH		50

int scoresOpen(const char*);
void scoresClose();
int scoresGetNext(score_t*);

#endif
