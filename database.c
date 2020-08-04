#include "database.h"
#include "scores.h"

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

int compareInstr(const void* a, const void* b) {
	return ((instr_t*)a)->id - ((instr_t*)b)->id;
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
	
	// sort instruments by ID
	if(database[index].instrCount > 1)
		qsort(database[index].instr, database[index].instrCount, sizeof *database[index].instr, compareInstr);
}

int databaseSize() {
	return filledSize;
}

int databaseAdd(score_t elem) {
	for(int i = 0; i < filledSize; i++) {
		if(!strcmp(database[i].hash, elem.hash)) {
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

int databaseSave(char* filename, char* header) {
	FILE* file = fopen(filename, "wb");
	if(file != NULL) {
		if(!fwrite(header, SCORES_HEADER_LENGTH, 1, file) || !fwrite(&filledSize, sizeof filledSize, 1, file)) {
			fclose(file);
			return 0;
		}
		for(int i = 0; i < filledSize; i++) {
			if(!scoresSave(file, database[i])) {
				fclose(file);
				return 0;
			}
		}
		fclose(file);
		return 1;
	} else
		return 0;
}

