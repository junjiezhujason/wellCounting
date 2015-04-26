#!/bin/bash

DIR=/scail/u/junjiezhu
FILENAME=NA12882_reads_possorted
# NA12877_reads_possorted
# NA12878_reads_possorted

# add bamtools to path
export PATH=$PATH:$DIR/tools/bamtools
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/scail/u/junjiezhu/tools/bamtools/lib/

# change to 10x data directory
cd $DIR/data/10x_data

# compile source code
.$DIR/source_codes/wellCounting1.1/countWells $FILENAME.bam 

# only owner can read/write
chmod 600 $FILENAME.bam_w*