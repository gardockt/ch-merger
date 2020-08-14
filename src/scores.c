#include "scores.h"
#include "score.h"

FILE* file;
char header[SCORES_HEADER_LENGTH];

int scoresOpen(const char* filename) {
	file = fopen(filename, "rb");
	if(file != NULL) {
		fread(header, SCORES_HEADER_LENGTH, 1, file);
		fseek(file, 4, SEEK_CUR);
		return 1;
	} else
		return 0;
}

void scoresClose() {
	if(file != NULL)
		fclose(file);
}

// to be removed in the future
void checkAssertions(score_t* score) {
	if(score->unknown[0] != 0 || score->unknown[1] != 0)
		printf("Song with hash %s does not match first assertion (%d %d). This is not an error, though I would be happy if you messaged me about how did you play this song (played instrument, used controller, online mode, version etc.) :)\n", score->hash, score->unknown[0], score->unknown[1]);
	for(int i = 0; i < score->instrCount; i++) {
		if(score->instr[i].unknown != 0)
			printf("Song with hash %s played on instrument %d (PB: %d, %d%, %d stars) does not match second assertion (%d). This is not an error, though I would be happy if you messaged me about how did you play this song (used instruments, online mode, version etc.) :)\n", score->hash, score->instr[i].id, score->instr[i].highscore, score->instr[i].percentage, score->instr[i].stars, score->instr[i].unknown);
	}
}

int scoresGetNext(score_t* score) {
	if(	fseek(file,	1, SEEK_CUR) >= 0 						&&	// block begin
		fread( score->hash,	SCORES_HASH_LENGTH, 1, file)	&&	// chart hash
		fread(&score->instrCount,			 1, 1, file)	&&	// instrument count
		fread(&score->playCount,			 1, 1, file)	&&	// play count
		fread( score->unknown,				 2, 1, file)		// ???
	) {
		score->instr = realloc(score->instr, score->instrCount * sizeof *score->instr);
		for(int i = 0; i < score->instrCount; i++) {
			if(	!fread(&score->instr[i].id,			1, 1, file)	||
				!fread(&score->instr[i].unknown,	1, 1, file)	||
				!fread(&score->instr[i].difficulty,	1, 1, file)	||
				!fread(&score->instr[i].percentage,	1, 1, file)	||
				!fread(&score->instr[i].fullCombo,	1, 1, file)	||
				!fread(&score->instr[i].speed,		2, 1, file)	||
				!fread(&score->instr[i].stars,		1, 1, file)	||
				!fread(&score->instr[i].modifiers,	1, 1, file)	||
				!fread(&score->instr[i].highscore,	4, 1, file)
			)
				return 0;
		}
		checkAssertions(score);
		return 1;
	} else
		return 0;
}

char* scoresGetHeader() {
	return header;
}

int scoresSave(FILE* f, score_t score) {
	if(	fwrite(" ",							 1, 1, f) && // block begin
		fwrite(	score.hash,	SCORES_HASH_LENGTH, 1, f) && // chart hash
		fwrite(&score.instrCount,			 1, 1, f) && // instrument cout
		fwrite(&score.playCount,			 1, 1, f) && // play count
		fwrite( score.unknown,				 2, 1, f)	 // ???
	) {
		for(int i = 0; i < score.instrCount; i++) {
			if(	!fwrite(&score.instr[i].id,			1, 1, f)	||
				!fwrite(&score.instr[i].unknown,	1, 1, f)	||
				!fwrite(&score.instr[i].difficulty,	1, 1, f)	||
				!fwrite(&score.instr[i].percentage,	1, 1, f)	||
				!fwrite(&score.instr[i].fullCombo,	1, 1, f)	||
				!fwrite(&score.instr[i].speed,		2, 1, f)	||
				!fwrite(&score.instr[i].stars,		1, 1, f)	||
				!fwrite(&score.instr[i].modifiers,	1, 1, f)	||
				!fwrite(&score.instr[i].highscore,	4, 1, f)
			)
				return 0;
		}
		return 1;
	} else
		return 0;
}
