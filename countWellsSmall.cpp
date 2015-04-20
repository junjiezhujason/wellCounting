#include <stdio.h>
#include <stdlib.h>
#include "api/BamReader.h"
#include "api/BamWriter.h"
#include <string>
#include <iostream>
#include <map>

// gcc -I ~/Shannon/bamtools/include/ -L ~/Shannon/bamtools/lib/ -o countWells countWells.cpp -lz -lbamtools -lstdc++
// ./countWells test_bamfiles/sim_reads_aligned.bam

typedef std::string barcode_str;
typedef std::string read_str;
typedef std::multimap<barcode_str, read_str> multimapRead;  // maps the barcode to reads
typedef std::map<barcode_str, uint32_t> mapCount;           // counts the numbers of barcodes


void bam_to_mapCount(const char* fName, mapCount& m, int& readsleft, const char* tName) {
    // create a map based on tag: tName, from .bam file
    std::string bamFname(fName);
    BamTools::BamReader reader;
    if (!reader.Open(bamFname)) {
        std::cerr << "Could not open input BAM file." << std::endl;
        exit(1);
    }

    char tagTypeName;
    barcode_str tagData;
    read_str read;
    BamTools::BamAlignment al;

    uint32_t readCount = 0;
    uint32_t readLimit = 10000001;


    while (reader.GetNextAlignment(al)) {           // each BAM entry is processed in this loop
        if (readCount == readLimit) {
            break;
        }
        readCount ++;
        if (al.GetTagType(tName, tagTypeName)) {    // ensure that tagType matches
            if (tagTypeName == 'Z') {               // verify that type is correct
                read = al.QueryBases;               // extract the read from entry
                al.GetTag(tName, tagData);          // extract the tag value from entry
                m[tagData] ++;                      // increment count
            } 
            else {
                printf("Warning: tagType is not Z - entry ignored \n");
                readsleft ++;
            }  
        } else {
            readsleft ++;
        }
    }
    reader.Close();
}


void print_mapCount(const char* bFname, mapCount m, const int readsleft){ // print the map counts
    std::string fname1(bFname);   
    fname1 += std::string("_Swnames"); 
    std::ofstream file1 (fname1.c_str());
    if (!file1.is_open()) {
       printf("map_to_file: Cannot open the file %s!\n", fname1.c_str());
       exit(1);
    }

    std::string fname2(bFname);   
    fname2 += std::string("_Swcounts"); 
    std::ofstream file2 (fname2.c_str());
    if (!file2.is_open()) {
       printf("map_to_file: Cannot open the file %s!\n", fname2.c_str());
       exit(1);
    }

    std::string fname3(bFname);   
    fname3 += std::string("_Swsummary"); 
    std::ofstream file3 (fname3.c_str());
    if (!file3.is_open()) {
       printf("map_to_file: Cannot open the file %s!\n", fname3.c_str());
       exit(1);
    }

    std::string bc; // barcode
    uint32_t ct;    // count
    for ( mapCount::iterator it = m.begin(); it != m.end(); ++it) {
        bc = it->first;
        ct = it->second;
        file1 << bc.c_str() << "\n"; 
        file2 << ct <<"\n";
    }

    file3 << "number of wells: " << m.size() << "\n";
    file3 << "leftover reads: " << readsleft << "\n";

    file1.close();
    file2.close();
    file3.close();
}


int main(int argc, char* argv[]) {
    char* inputFileName;
    char barcodeName[] = "BX";
    int readwowells = 0; // count reads that do not fall into any wells
    mapCount MapWell;

    if ( argc == 2 ) {
            inputFileName  = argv[1] ;
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        return 1;
    }

    bam_to_mapCount(inputFileName, MapWell, readwowells, barcodeName);
    print_mapCount(inputFileName, MapWell, readwowells);
   
    return 0;
}