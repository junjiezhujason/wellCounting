CFLAGS=		-g -Wall -O2 -ftree-vectorize -std=c++0x
DFLAGS=		-D_FILE_OFFSET_BITS=64 -D_USE_KNETFILE
IFLAGS= 	-I /scail/u/junjiezhu/tools/bamtools/include/ 
LFLAGS=		-L /scail/u/junjiezhu/tools/bamtools/lib/ 

countWells: countWells.o 
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) countWells.o -lz -pthread -lstdc++ -o countWells

countWells.o: countWells.cpp
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) -c countWells.cpp

clean:
	rm -f countWells
	rm -f countWells.o
	rm -f countWellshelper.o