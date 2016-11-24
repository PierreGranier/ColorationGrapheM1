#makefile

CFLAGS=-Wall
OFLAGS=-O2

STRUCTURE_COULEURS=tableau


all: main.out


main.out: main.c fonctions.c structures/aretes_matrice.c structures/couleurs_$(STRUCTURE_COULEURS).c
	@echo "# Compilation de $^"
	gcc -o main.out $^ $(CFLAGS) $(OFLAGS)
	

launch2: main.out test2.txt
	@echo "# Execution de $^"
	./$^
	
launch: main.out test.txt
	@echo "# Execution de $^"
	./$^

launch-time: main.out test2.txt
	@echo "# Execution de $^"
	time ./$^


clean:
	rm *.out
