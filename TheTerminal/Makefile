CC=gcc
CFLAGS= -O0 -g #-Wall 
LIBS = -lm -llcd1602 -lpthread

Terminal: main.o Header.h Display.o Utility.o ServerRequest.o #Card_Data_Parsing.o
	$(CC) -o Terminal $(CFLAGS) main.o $(LIBS) Header.h Display.o Utility.o ServerRequest.o -lcurl #Card_Data_Parsing.o

main.o:	main.c Header.h 
	$(CC) -c $(CFLAGS) main.c 

Display.o:	Display.c Header.h
	gcc -c $(CFLAGS) Display.c

Utility.o: Utility.c Header.h
	gcc -c $(CFLAGS) Utility.c

ServerRequest.o: ServerRequest.c
	gcc -c $(CLFAGS) ServerRequest.c -lcurl

# Card_Data_Parsing.o: Card_Data_Parsing.c headers.h
# 	gcc -c $(CFLAGS) Card_Data_Parsing.c

run:				
	./script.sh

script.sh:
	echo "Run the program with ./Terminal"

clean:
	rm -f *.o