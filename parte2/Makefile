all:
	gcc -o programaTrab *.c

run: cpy clear all
	./programaTrab

cpy:
	cp arquivos/antes/* ./

val: all
	valgrind --leak-check=full ./entrega2

zip:
	zip entrega2.zip *.c *.h Makefile

git:
	git add .
	git commit -m "Adding project"
	git push
	git status

clear : 
	clear
