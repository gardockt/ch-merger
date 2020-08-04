#include "main.h"
#include "score.h"
#include "scores.h"
#include "database.h"

void freeAllMemory(score_t* ptr) {
	scoresClose();
	scoreFree(ptr);
	databaseFree();
}

int main(int argc, char* argv[]) {
	const char*	outname = "scores_merged.bin";
	char		header[SCORES_HEADER_LENGTH];
	score_t		score;

	if(argc > 1) {
		databaseInit(32);
		scoreAlloc(&score);

		for(int i = 1; i < argc; i++) {
			scoresOpen(argv[i]);

			// header check
			if(i > 1) {
				if(strcmp(header, scoresGetHeader())) {
					fprintf(stderr, "ERROR: Header mismatch! If you want to continue at your own risk, replace the header (first %d characters) in file %s.\n", SCORES_HEADER_LENGTH, argv[i]);
					freeAllMemory(&score);
					return 1;
				}
			} else
				memcpy(header, scoresGetHeader(), SCORES_HEADER_LENGTH);

			// writing
			while(scoresGetNext(&score)) {
				if(!databaseAdd(score)) {
					fprintf(stderr, "ERROR: Out of memory!\n");
					freeAllMemory(&score);
					return 2;
				}
			}

			scoresClose();
		}

		scoreFree(&score);

		if(!databaseSave(outname, header))
			fprintf(stderr, "ERROR: Could not write file!\n");
		else
			printf("DONE! Scanned %d songs and written merged scores to %s\n", databaseSize(), outname);
		databaseFree();
	} else
		printf("Usage: %s [path to file 1] [path to file 2] ...\n", argv[0]);
	return 0;
}

