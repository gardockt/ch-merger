#include "main.h"
#include "score.h"
#include "scores.h"
#include "database.h"

void freeAllMemory(score_t* ptr) {
	scoresClose();
	scoreFree(ptr);
	databaseFree();
}

int confirmation() {
	printf("WARNING: Backing up your scores.bin is STRONGLY recommended. I do not take responsibility for any damage caused by this program. Are you sure? [y/n] ");
	return getchar() == 'y';
}

int main(int argc, char* argv[]) {
	const char*	outname = "scores_merged.bin";
	int			version;
	score_t		score;

	if(argc > 1) {
		if(!confirmation())
			return 0;

		databaseInit(32);
		scoreAlloc(&score);

		for(int i = 1; i < argc; i++) {
			if(!scoresOpen(argv[i])) {
				fprintf(stderr, "ERROR: Cannot read file %s!\n", argv[i]);
				freeAllMemory(&score);
				return 3;
			}

			// version check
			if(i > 1) {
				if(version != scoresGetVersion()) {
					fprintf(stderr, "ERROR: Version mismatch in file %s!\n", argv[i]);
					freeAllMemory(&score);
					return 1;
				}
			} else
				version = scoresGetVersion();

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

		if(!databaseSave(outname, version))
			fprintf(stderr, "ERROR: Could not write file!\n");
		else
			printf("DONE! Scanned %d songs and wrote merged scores to %s\n", databaseSize(), outname);
		databaseFree();
	} else
		printf("Usage: %s [path to file 1] [path to file 2] ...\n", argv[0]);
	return 0;
}

