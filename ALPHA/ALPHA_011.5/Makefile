#compiler
CC = gcc
#compile flags (in the valgrind debugging stage the flag -ggdb3 was also being used
CFLAGS  = -Wall -std=c11 -O3
#executable
default: covid19
#Linking
covid19:  main.o readmodulec.o writemodulec.o restrictionmodule.o selectionmodule.o sortingmodule.o Help_ErrorCodes.o Freemodules.o
	$(CC) $(CFLAGS) -o covid19 main.o readmodulec.o writemodulec.o restrictionmodule.o selectionmodule.o sortingmodule.o Help_ErrorCodes.o Freemodules.o
#Compilation of the object files
main.o:  main.c covid19.h
	$(CC) $(CFLAGS) -c main.c

readmodulec.o: readmodulec.c covid19.h
	$(CC) $(CFLAGS) -c readmodulec.c

writemodulec.o: writemodulec.c covid19.h
	$(CC) $(CFLAGS) -c writemodulec.c

restrictionmodule.o: restrictionmodule.c covid19.h
	$(CC) $(CFLAGS) -c restrictionmodule.c

selectionmodule.o: selectionmodule.c covid19.h
	$(CC) $(CFLAGS) -c selectionmodule.c

sortingmodule.o: sortingmodule.c covid19.h
	$(CC) $(CFLAGS) -c sortingmodule.c

Help_ErrorCodes.o: Help_ErrorCodes.c covid19.h
	$(CC) $(CFLAGS) -c Help_ErrorCodes.c

Freemodules.o: Freemodules.c covid19.h
	$(CC) $(CFLAGS) -c Freemodules.c

#remove object files and emac backup files from directory before forcing recompilation
clean:
	$(RM) count *.o *~
