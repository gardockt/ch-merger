all: ch-merger

ch-merger: score.o scores.o main.o database.o
	$(CC) $(FLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(FLAGS) -c $<

clean:
	rm *.o ch-merger
