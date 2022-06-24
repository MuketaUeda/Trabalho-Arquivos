
all:
	gcc *.c -o ex1 -g

run:
	./ex1

val: all
	valgrind ./ex1

zip:
	zip ex1.zip main.c functions.h functions.c commands.h commands.c Makefile

git:
	git add .
	git commit -m "Adding project"
	git push
	git status

clean : 
	rm *.o ex1