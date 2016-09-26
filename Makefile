prompt: main.o abo_chil.o extract.o cmd.o pipe.o
		gcc main.o abo_chil.o extract.o cmd.o pipe.o -o prompt

main.o: main.c extract.c abo_chil.c
		gcc -c main.c

abo_chil.o: abo_chil.c comon1.h
		gcc -c abo_chil.c

extract.o: extract.c
		gcc -c extract.c

cmd.o: cmd.c extract.c pipe.c
		gcc -c cmd.c
pipe.o: pipe.c
		gcc -c pipe.c
clean:
		rm -rf *.o prompt
