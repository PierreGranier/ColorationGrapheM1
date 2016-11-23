#makefile

CFLAGS=-Wall
OFLAGS=-O2


all: main.out


main.out: main.c fonctions.c
	@echo "# Compilation de $^"
	gcc -o main.out $^ $(CFLAGS) $(OFLAGS)

test.out: main.c test/fonctions.c
	@echo "# Compilation de $^"
	gcc -o test.out $^ $(CFLAGS) $(OFLAGS)


launch: main.out test.txt
	@echo "# Execution de $^"
	./$^
	
launch_test: test.out test.txt
	@echo "# Execution de $^"
	./$^

launch-time: main.out test.txt
	@echo "# Execution de $^"
	time ./$^
	

clean:
	rm *.out
