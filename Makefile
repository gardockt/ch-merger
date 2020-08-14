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



.PHONY: clean test

all: $(OUTPUT)

clean:
	rm *.o ch-merger*

test:
	@echo y | ./ch-merger test/in.1 test/in.2 > /dev/null
	@cmp -s scores_merged.bin test/out
	@if [ $$? -eq 0 ]; then \
		echo 'Test completed successfully!'; \
	else \
		echo 'Test failed!'; \
	fi
	@rm scores_merged.bin



ch-merger: $(LIBS)
	$(CC) $(FLAGS) -o $@ $^

ch-merger.exe: $(LIBS)
	$(CC) $(FLAGS) -o $@ $^

%.o: src/%.c src/%.h
	$(CC) $(FLAGS) -c $<
