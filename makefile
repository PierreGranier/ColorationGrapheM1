#makefile

CFLAGS=-Wall
OFLAGS=-O2

all: main.exe

main.exe: main.c
	@echo "# Compilation de $^"
	gcc -o main.out $< $(CFLAGS) $(OFLAGS)

launch: main.out
	@echo "# Execution de $^"
	./$^
	
clean:
	rm *.out
	