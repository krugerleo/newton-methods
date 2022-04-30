#!/bin/bash

for N in 10 32 50 64 100 128 200 250 256 300 400 512 600 1000 1024 2000 2048 3000 4096
do
	echo $N
	for i in $(seq 1 $((N-1)))
	do
		echo -n "100*(x$(($i+1))-x$i^2)^2+(1-x$i)^2+"
	done
 	echo "0"
 	for i in $(seq 1 $N)
	do
		echo -n "1.01 "
	done
 	echo -e "\n0 50\n"
done
