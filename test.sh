#!/bin/sh
NB_CYCLES="${NB_CYCLES:-100}"
echo $NB_CYCLES
for i in $(eval echo "{1..$NB_CYCLES}") 
do 
	./bin/client calcul-simple + 0x12 0x23 > /dev/null &
done
