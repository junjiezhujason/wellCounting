CFLAGS=		-g -Wall -O2 -ftree-vectorize -std=c++0x
DFLAGS=		-D_FILE_OFFSET_BITS=64 -D_USE_KNETFILE 
IFLAGS= 	-I /scail/u/junjiezhu/tools/bamtools/include/ 
LFLAGS=		-L /scail/u/junjiezhu/tools/bamtools/lib/ -lbamtools

countWells: countWells.o 
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) countWells.o -lz -pthread -lstdc++ -o countWells

countWells.o: countWells.cpp
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) -c countWells.cpp

indexbambc: indexbambc.o 
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) indexbambc.o -lz -pthread -lstdc++ -o indexbambc

indexbambc.o: indexbambc.cpp
	gcc $(CFLAGS) $(DFLAGS) $(IFLAGS) $(LFLAGS) -c indexbambc.cpp

filtbcindex: filtbcindex.o 
	gcc $(CFLAGS) $(DFLAGS) filtbcindex.o -lz -pthread -lstdc++ -o filtbcindex

filtbcindex.o: filtbcindex.cpp
	gcc $(CFLAGS) $(DFLAGS)  -c filtbcindex.cpp


clean:
	rm -f countWells
	rm -f countWells.o
	rm -f indexbambc
	rm -f indexbambc.o
	rm -f filtbcindex
	rm -f filtbcindex.o