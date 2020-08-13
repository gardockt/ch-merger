FLAGS=

ch-merger: score.o scores.o main.o database.o
	$(CC) $(FLAGS) -o ch-merger score.o scores.o main.o database.o

main.o: main.c main.h scores.o score.o database.o
	$(CC) $(FLAGS) -c main.c main.h

database.o: database.c database.h score.o scores.o
	$(CC) $(FLAGS) -c database.c database.h

scores.o: scores.c scores.h score.o
	$(CC) $(FLAGS) -c scores.c scores.h

score.o: score.c score.h
	$(CC) $(FLAGS) -c score.c score.h
