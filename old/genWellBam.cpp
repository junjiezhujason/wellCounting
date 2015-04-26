#include <stdio.h>
#include <stdlib.h>
//#include "api/BamReader.h"
//#include "api/BamWriter.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

// gcc -I ~/Shannon/bamtools/include/ -L ~/Shannon/bamtools/lib/ -o countWells countWells.cpp -lz -lbamtools -lstdc++
// ./countWells test_bamfiles/sim_reads_aligned.bam

typedef std::string barcode_str;
typedef std::string read_str;
typedef std::multimap<barcode_str, read_str> multimapRead;  // maps the barcode to reads
typedef std::map<barcode_str, uint32_t> mapCount;           // counts the numbers of barcodes


int get_wellCount(const char* fname, mapCount& m, int nWells, int minSize) {
    // read name file
    std::string fname1(fname);
    fname1 += std::string("_wnames"); 
    std::ifstream nameFile (fname1.c_str());
    if (!nameFile.is_open()) {
       printf("map_to_file: Cannot open the file %s!\n", fname1.c_str());
       exit(1);
    }

    // read count file
    std::string fname2(fname);
    fname2 += std::string("_wcounts"); 
    std::ifstream countFile (fname2.c_str());
    if (!countFile.is_open()) {
       printf("map_to_file: Cannot open the file %s!\n", fname2.c_str());
       exit(1);
    }

    // if a well has no less than minSize, then save nWells of them to the map
    std::string name;
    std::string count_str;
    uint32_t count;
    uint32_t wcount = 0;

    while (std::getline (nameFile,name)) {
        std::getline (countFile,count_str);
        count = atoi(count_str.c_str());
        if (wcount == nWells) {
            break;
        }

        if (count >= minSize) {
            m[name] = count;
            printf("%s\t", name.c_str());
            printf("%u\n", count);
            wcount ++;
        }
        
    }

    nameFile.close();
    countFile.close();
    printf("Finished loading file %s!\n", fname);
    return 0;
}

int main(int argc, char* argv[]) {
    char* inputFileName;
    //char barcodeName[] = "BX";
    //int readwowells = 0; // count reads that do not fall into any wells
    mapCount MapWell;

    if ( argc == 2 ) {
            inputFileName  = argv[1] ;
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        return 1;
    }

    int numWells = 100;
    int minWellsize = 8000;

    get_wellCount(inputFileName, MapWell, numWells, minWellsize);

    //bam_to_mapCount(inputFileName, MapWell, readwowells, barcodeName);
    //print_mapCount(inputFileName, MapWell, readwowells);
   
    return 0;
}