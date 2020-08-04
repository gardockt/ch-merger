#include "database.h"

score_t* database;
int maxSize, filledSize;

int databaseInit(int startSize) {
	database = malloc(startSize * sizeof *database);
	maxSize = startSize;
	filledSize = 0;
	return database != NULL;
}

void databaseFree() {
	free(database);
}

int databaseDoubleSize() {
	if((database = realloc(database, maxSize * 2 * sizeof *database)) != NULL) {
		maxSize *= 2;
		return 1;
	} else
		return 0;
}

void databaseCompareScores(int index, score_t elem) {
	int found;
	for(int i = 0; i < elem.instrCount; i++) {
		found = 0;
		for(int j = 0; j < database[index].instrCount; j++) {
			if(elem.instr[i].id == database[index].instr[j].id) {
				found = 1;
				if(elem.instr[i].highscore > database[index].instr[j].highscore) {
					database[index].instr[j].highscore	= elem.instr[i].highscore;
					database[index].instr[j].speed		= elem.instr[i].speed;
					database[index].instr[j].modifiers	= elem.instr[i].modifiers;
					database[index].instr[j].difficulty	= elem.instr[i].difficulty;
				}
				if(elem.instr[i].percentage > database[index].instr[j].percentage)
					database[index].instr[j].percentage	= elem.instr[i].percentage;
				if(elem.instr[i].fullCombo && !database[index].instr[j].fullCombo)
					database[index].instr[j].fullCombo	= 1;
				if(elem.instr[i].stars > database[index].instr[j].stars)
					database[index].instr[j].stars		= elem.instr[i].stars;
			}
			if(!found) {
				if(realloc(database[index].instr, (database[index].instrCount + 1) * sizeof *database[index].instr) != NULL)
					memcpy(&database[index].instr[database[index].instrCount++], &elem.instr[i], sizeof elem.instr[i]);
			}
			break;
		}
	}
	// TODO: sort instruments by ID
}

int databaseSize() {
	return filledSize;
}

int databaseAdd(score_t elem) {
	for(int i = 0; i < filledSize; i++) {
		if(!strcmp(database[i].hash, elem.hash)) {
			printf("%s i %s są takie same [i=%d]\n", database[i].hash, elem.hash, i);
			database[i].playCount += elem.playCount;
			databaseCompareScores(i, elem);
			return 1;
		}
	}

	// song not found
	if(filledSize == maxSize && !databaseDoubleSize())
		return 0;
	scoreAlloc(&database[filledSize]);
	scoreCopy(&database[filledSize++], &elem);
	return 1;
}

score_t databaseGet(int index) {
	return database[index];
}
