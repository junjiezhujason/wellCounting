#include <stdio.h>
#include <stdlib.h>
#include "api/BamReader.h"
#include "api/BamWriter.h"
#include <string>
#include <iostream>

// gcc -I ~/Shannon/bamtools/include/ -L ~/Shannon/bamtools/lib/ -o countWells countWells.cpp -lz -lbamtools -lstdc++
// ./countWells test_bamfiles/sim_reads_aligned.bam

typedef std::string barcode_str;

int main(int argc, char* argv[]) {
    char* fName;
    char tName[] = "BX";
    int readswobc = 0; // count reads that do not fall into any wells

    if ( argc == 2 ) {
            fName  = argv[1] ;
    } else {
        std::cerr << "Wrong number of arguments." << std::endl;
        return 1;
    }

    // ============= FILE I/O  =============
    std::string bFname(fName);
    std::string fname1(bFname);   
    std::string fname2(bFname);   
    
    fname1 += std::string("_bcnames"); 
    fname2 += std::string("_bcindex"); 

    std::ofstream file1 (fname1.c_str());
    std::ofstream file2 (fname2.c_str());

    if (!file1.is_open()) {
       printf("Cannot open the file %s!\n", fname1.c_str());
       exit(1);
    }
    if (!file2.is_open()) {
       printf("Cannot open the file %s!\n", fname2.c_str());
       exit(1);
    }
    BamTools::BamReader reader;
    if (!reader.Open(bFname)) {
        printf("Cannot open bam file %s!\n", bFname.c_str());
        exit(1);
    }

    //  ============= MAIN PROGRAM  =============
    char tagTypeName;
    barcode_str bc, bc_prev;
    uint64_t position = 0;

    BamTools::BamAlignment al;

    while (reader.GetNextAlignment(al)) {           // each BAM entry is processed in this loop
        if (al.GetTagType(tName, tagTypeName)) {    // ensure that tagType matches
            if (tagTypeName == 'Z') {               // verify that type is correct
                al.GetTag(tName, bc);               // extract the tag value from entry
                if (bc.compare(bc_prev) != 0) {     // bc is a new barcode
                    // output the barcode name
                    file1 << bc.c_str() << "\n"; 
                    // output the index of the entry that starts with this barcodes
                    file2 << position << "\n";
                }
                bc_prev = bc;
            } 
            else {
                printf("Warning: tagType is not Z - entry ignored \n");
                readswobc ++;
            }  
        } else {
            readswobc ++;
        }
        position ++;
    }
    reader.Close();
    file1.close();
    file2.close();

    printf("Finished reading file %s!\n", fName);
    printf("Total number of reads %lld\n", (long long int) position);    
    return 0;
}