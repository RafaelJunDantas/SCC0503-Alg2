UTIL = bTree.c registro.c fileHandler.c
MAIN = main.c
BINARY = executavel

all:
	gcc -Wall -g $(UTIL) $(MAIN) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

run:
	./$(BINARY)
