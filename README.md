# wellCounting

There are three main programs: countWells, indexbambc, filtbcindex.

To compile: 

	make clean
	make /name of pogram/

NOTE:
	- running the program requires libraries from Bamtools: 
		https://github.com/pezmaster31/bamtools
		bamtools.sh on scail includes an example how to export paths
	- indexbambc requires a bam file sorted by barcode "BX"
	- filtbcindex requires OUTPUT files from indexbambc
		OUTPUT fields are: startPos, endPos, #ofReads, bcindex
	- countWells is unncessary for sorted bam files,
		but can be used to calculate some statistics for unsorted ones


1. indexbambc: count reads/barcode in a .bam file sorted by "BX"
	INPUT:
		-.bam file (sorted by barcode marked by "BX")
	OUTPUT:
		-.bam_bcnames (sorted bc names, should be same as .bam_wnames)
		-.bam_bcindex (indices of lines that start with correspodning bc)
			* the last line of .bam_bcindex is the number of reads in .bam
	
	example:
		$DIR/source_codes/wellCounting2.1/indexbambc $FILENAME


2. filtbcindex: create an index for .bam_bcindex based on min # of reads
	INPUT: 
		-.bam file name (but really just calls -.bam_bcindex)
		- minimum # of reads/barcode (recommended INPUT: 100)
	OUTPUT: 
		-.bam_bcselxxx ([startPos, endPos, #ofReads, bcindex]) 
			* positions are indexed from 0, and refer to lines in the .bam file
			* bcindex can be used to look up names in .bam_bcnames 
	
	example:		
		$DIR/source_codes/wellCounting2.1/filtbcindex $FILENAME 100


3. countWells: count reads/barcode with an ordered std::map
	INPUT: 
		-.bam file name (with barcode marked by "BX")
	OUTPUT: 
		-.bam_wnames (sorted bc names)
		-.bam_wcounts (correspond number of reads)
		-.bam_wsummary (other stats)
	
	example:
		$DIR/source_codes/wellCounting2.1/countWells $FILENAME