CC=gcc
CFLAGS= -Wall -O0 -g
LIBS = -lm -llcd1602 -lpthread

Terminal: main.o Header.h Display.o #Card_Data_Parsing.o 
	$(CC) -o Terminal $(CFLAGS) main.o $(LIBS) Header.h Display.o #Card_Data_Parsing.o 

main.o:	main.c Header.h 
	$(CC) -c $(CFLAGS) main.c 

Display.o:	Display.c Header.h
	gcc -c $(CFLAGS) Display.c

# Card_Data_Parsing.o: Card_Data_Parsing.c headers.h
# 	gcc -c $(CFLAGS) Card_Data_Parsing.c

run:				
	./script.sh

script.sh:
	echo "Run the program with ./Terminal"

clean:
	rm -f *.o