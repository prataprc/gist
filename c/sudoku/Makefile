CFLAGS += -pg -O2 -Wall
.phony : all run clean

all : sgen solve
		
sgen : sudoku.o sgen.o
	$(CC) $(CFLAGS) $^ -o $@

solve : sudoku.o solve.o
	$(CC) $(CFLAGS) $^ -o $@

gen : 
	./sudoku 2 2
	gprof sudoku gmon.out > profile

clean:
	rm -f *.o sgen profile gmon.out solve sudoku_1

sudoku.o sgen.o solve.o : sudoku.h
