prompt: main.o abo_chil.o extract.o cmd.o
		gcc main.o abo_chil.o extract.o cmd.o -o prompt

main.o: main.c extract.c abo_chil.c
		gcc -c main.c

abo_chil.o: abo_chil.c comon1.h
		gcc -c abo_chil.c

extract.o: extract.c 
		gcc -c extract.c

cmd.o: cmd.c extract.c comon2.h 
		gcc -c cmd.c

clean:
		rm -rf *.o prompt