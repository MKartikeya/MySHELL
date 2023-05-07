myshell: main.o mycp.o mygrep.o myls.o mymv.o myps.o
	gcc  main.o mycp.o mygrep.o myls.o mymv.o myps.o -lreadline -o myshell

main.o: main.c
	gcc -c main.c -lreadline -o main.o

mycp.o: mycp.c
	gcc -c mycp.c -lreadline -o mycp.o

mygrep.o: mygrep.c
	gcc -c mygrep.c -lreadline -o mygrep.o

myls.o: myls.c
	gcc -c myls.c -lreadline -o myls.o

mymv.o: mymv.c
	gcc -c mymv.c -lreadline -o mymv.o

myps.o: myps.c
	gcc -c myps.c -lreadline -o myps.o
 
clean: main.o mycp.o mygrep.o myls.o mymv.o myps.o
	rm main.o mycp.o mygrep.o myls.o mymv.o myps.o