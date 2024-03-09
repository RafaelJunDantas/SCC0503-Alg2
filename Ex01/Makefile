MAIN=main.c
ALUNO = aluno.c
FILE = fileHandler.c
BINARY=executavel
ZIPNAME = Ex0_Alg2

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

all: 
	gcc -Wall -g $(MAIN) $(ALUNO) $(FILE) -o $(BINARY) -s

run:
	./$(BINARY)
debug:
	gcc -DDEBUG -Wall $(MAIN) $(ALUNO) $(FILE) -o executavel

clean:
	@rm $(BINARY)

zip:
	@zip -r $(NAME).zip *
