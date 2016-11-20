#makefile

CFLAGS=-Wall
OFLAGS=-O2

all: main.exe

main.exe: main.c
	@echo "# Compilation de $@"
	gcc -o main $< $(CFLAGS) $(OFLAGS)

launch: main
	@echo "# Execution de main.exe"
	./main
	
clean:
	rm *.exe
	