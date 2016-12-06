# Makefile (règles implicites)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

tout: echoclient echoserveur extremite
	
echoclient : echoclient.c
	$(CC) -o echoclient echoclient.c
	
echoserveur : echoserveur.c
	$(CC) -o echoserveur echoserveur.c
	
extremite : extremite.c
	$(CC) -o extremite extremite.c

clean:
	rm *.o
