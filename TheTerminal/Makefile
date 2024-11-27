CC=gcc
CFLAGS= -Wall -O0 -g.
LIBS = -lm -llcd1602 -lpthread

TheTerminal: main.o Header.h Card_Data_Parsing.o Display.o
     $(CC) -o TheTerminal $(CFLAGS) $(LIBS) main.o Header.h Card_Data_Parsing.o Display.o 

main.o:	main.c headers.h 
	$(CC) -c $(CFLAGS) main.c 

Display.o:	Display.c headers.h
	gcc -c $(CFLAGS) Display.c

Card_Data_Parsing.o: Card_Data_Parsing.c headers.h
	gcc -c $(CFLAGS) Card_Data_Parsing.c

run:				
    ./script.sh

script.sh:
    echo "Run the program with ./TheTerminal"

clean:
    rm -f *.o