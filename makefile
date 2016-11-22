#makefile

CFLAGS=-Wall
OFLAGS=-O2

all: main.exe

main.exe: main.c fonctions.c
	@echo "# Compilation de $^"
	gcc -o main.out $^ $(CFLAGS) $(OFLAGS)

launch: main.out test.txt
	@echo "# Execution de $^"
	./$^
	
	
launch-time: main.out test.txt
	@echo "# Execution de $^"
	time ./$^
	
	
clean:
	rm *.out
	
