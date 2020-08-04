#include <stdlib.h>
#include <string.h>

#include "score.h"

int		databaseInit(int);
void	databaseFree();
int		databaseSize();
int		databaseAdd(score_t);
score_t	databaseGet(int);
