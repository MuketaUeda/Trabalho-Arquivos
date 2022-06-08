all:
	gcc -o programaTrab *.c

run:
	./programaTrab

val: all
	valgrind --leak-check=full ./entrega1

zip:
	zip entrega1.zip *.c *.h Makefile

git:
	git add .
	git commit -m "Adding project"
	git push
	git status

clean : 
	rm *.o entrega1