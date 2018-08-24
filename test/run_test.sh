#!/bin/bash

# Run this from the top level directory

rm -f test/test.out
./build/sdpb --precision=1024 --noFinalCheckpoint --procsPerNode=1 -s test/test/ > /dev/null
diff test/test.out test/test.out.orig
if [ $? == 0 ]
then
    echo "PASS"
    exit 0
else
    echo "FAIL"
    exit 1
fi
    
