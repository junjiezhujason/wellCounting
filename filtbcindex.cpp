#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[]) {
    char* bFname;		 // bam file
    int minRead;  		 // minimum number of reads/ partition
    
    if ( argc == 3 ) {
            bFname  = argv[1] ;		 
            minRead = atoi(argv[2]); 
    } else {
        std::cerr << "Wrong number of arguments: filtbcindex <.bam> <minNumReads>" << std::endl;
        return 1;
    }

    // ============= FILE I/O  =============
    std::string fname1(bFname);   
    std::string fname2(bFname);   
    
    fname1 += std::string("_bcindex"); 
    fname2 += std::string("_bcsel"); 
    fname2 += std::to_string(static_cast<long long>(minRead)); 

    std::ifstream file1 (fname1.c_str());
    std::ofstream file2 (fname2.c_str());
	if (!file1.is_open()) {
       printf("Cannot open the file %s!\n", fname1.c_str());
       exit(1);
    }
    if (!file2.is_open()) {
       printf("Cannot open the file %s!\n", fname2.c_str());
       exit(1);
    } 

    //  ============= MAIN PROGRAM  =============
    int bcindex = 0;  	// barcode index in .bam_bcnames and .bam_bcindex
    int numSel = 0;		// number of selected barcodes
    std::string line;	// value in string in the input file

    int readswbc; 		// # of reads with a particular barcode
   	int startPos;		// pos in .bam where a particular barcode starts
    int endPos; 		// pos in .bam where a particular barcode ends



    std::getline (file1,line);
    startPos = atoi(line.c_str());

    while (std::getline (file1,line)) { // sweep through each line in .bam_bcnames
    	endPos = atoi(line.c_str()) - 1;
    	readswbc = endPos - startPos + 1; 
        // bcindex, startPos, endPos
    	if (readswbc > minRead) {
    		file2  <<"\t"<<startPos<<"\t"<<endPos<<"\t"<< readswbc<<"\t"<< bcindex<<"\n";
    		numSel ++;
    	}
        startPos = endPos + 1;
        bcindex ++;
    }

    file1.close();
    file2.close();
	printf("File saved: <%s>: [startPos, endPos, #ofReads, bcindex] \n", fname2.c_str());
    printf("Complete: %d barcodes ", numSel);
    printf("have more than %d reads.\n", minRead);


    return 0;
}
