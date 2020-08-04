#include "main.h"
#include "score.h"
#include "scores.h"
#include "database.h"

void writeScore(score_t score) {
	printf("Hash:             %s\n", score.hash);
	printf("Instrument count: %d\n", score.instrCount);
	printf("Play count:       %d\n", score.playCount);
	printf("Unknown:          0x%.2x 0x%.2x\n", score.unknown[0], score.unknown[1]);
	for(int i = 0; i < score.instrCount; i++) {
		printf("Instrument %d:\n", score.instr[i].id);
		printf("Unknown:          0x%.2x\n", score.instr[i].unknown);
		printf("Difficulty:       %d\n", score.instr[i].difficulty);
		printf("Percentage:       %d%\n", score.instr[i].percentage);
		printf("Full combo:       %s\n", score.instr[i].fullCombo ? "yes" : "no");
		printf("Speed:            %d%\n", score.instr[i].speed);
		printf("Stars:            %d\n", score.instr[i].stars);
		printf("Modifier flags:   %d\n", score.instr[i].modifiers);
		printf("Highscore:        %ld\n", score.instr[i].highscore);
	}
	printf("\n");
}

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
	
