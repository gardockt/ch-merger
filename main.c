#include "main.h"
#include "score.h"
#include "scores.h"
#include "database.h"

int main() {
	const char* filename = "scores.bin";
	char header[SCORES_HEADER_LENGTH];
	score_t score;
	
	databaseInit(32);
	scoreAlloc(&score);
	scoresOpen(filename);
	memcpy(header, scoresGetHeader(), SCORES_HEADER_LENGTH);

	while(scoresGetNext(&score))
		databaseAdd(score);
	
	scoresClose();
	scoreFree(&score);

	databaseSave("scores_merged.bin", header);
	databaseFree();
	return 0;
}
	
