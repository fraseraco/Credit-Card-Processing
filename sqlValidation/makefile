validation: validationFunctions.o sqlite3.o tempMain.o 
	    gcc  -o validation validationFunctions.o sqlite3.o tempMain.o 

validationFunctions.o: validationFunctions.c headers.h sqlite3.h
	    gcc -c -g -Wall validationFunctions.c

sqlite3.o: sqlite3.c headers.h sqlite3.h
	    gcc -c -g -Wall sqlite3.c

tempMain.o: tempMain.c headers.h sqlite3.h
	    gcc -c -g -Wall tempMain.c
