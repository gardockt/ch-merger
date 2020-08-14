LIBS = score.o scores.o main.o database.o



ifeq ($(TARGET),)
	ifeq ("$(OS)", "Windows_NT")
		TARGET = windows
	else
		TARGET = linux
	endif
endif

ifeq ($(TARGET), linux)
	CC = gcc
	OUTPUT = ch-merger
endif
ifeq ($(TARGET), windows)
	CC = i686-w64-mingw32-gcc
	OUTPUT = ch-merger.exe
endif



all: $(OUTPUT)

clean:
	rm *.o ch-merger*



ch-merger: $(LIBS)
	$(CC) $(FLAGS) -o $@ $^

ch-merger.exe: $(LIBS)
	$(CC) $(FLAGS) -o $@ $^

%.o: src/%.c src/%.h
	$(CC) $(FLAGS) -c $<
