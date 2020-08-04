FLAGS=-ggdb

ch-merger: score.o scores.o main.o
	$(CC) $(FLAGS) -o ch-merger score.o scores.o main.o

main.o: main.c main.h scores.o score.o
	$(CC) $(FLAGS) -c main.c main.h scores.c scores.h score.c score.h

scores.o: scores.c scores.h score.o
	$(CC) $(FLAGS) -c scores.c scores.h score.c score.h

score.o: score.c score.h
	$(CC) $(FLAGS) -c score.c score.h
