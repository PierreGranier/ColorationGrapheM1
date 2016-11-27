#makefile

CFLAGS=-Wall -lm
OFLAGS=-O2

STRUCTURE_COULEURS=tableau


all: main.out


main.out: main.c fonctions.c structures/aretes_matrice.c structures/couleurs_$(STRUCTURE_COULEURS).c
	@echo "# Compilation de $^"
	gcc -o main.out $^ $(CFLAGS) $(OFLAGS)
	
launch: main.out
	@echo "# Execution de $^"
	./$^

launch-time: main.out
	@echo "# Mesure temporelle de l'execution de $^"
	time ./$^

valgrind: main.out
	@echo "# Vérification valgrind de l'execution de $^"
	valgrind ./$^ --track-origins=yes


clean:
	rm *.out
