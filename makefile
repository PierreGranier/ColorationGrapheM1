#makefile

CFLAGS=-Wall
OFLAGS=-O2

STRUCTURE_COULEURS=matrice # matrice ou tableau


all: main.out


main.out: main.c fonctions.c structures/aretes_matrice.c structures/couleurs_$(STRUCTURE_COULEURS).c
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
