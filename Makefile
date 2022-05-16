
all:
	gcc *.c -o entrega1 -Wall -Werror

run:
	./entrega1

val: all
	valgrind ./entrega1

zip:
	zip entrega1.zip * Makefile

git:
	git add .
	git commit -m "Adding project"
	git push
	git status

clean : 
	rm *.o entrega1