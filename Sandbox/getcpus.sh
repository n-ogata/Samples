#!/bin/bash

declare -A pids

pids=()

for root in 18 19 21
do
	#ls 1>${root}.log 2>/dev/null &
	echo "{\"root\":${root},\"canID\":1,\"report\":true}" | ./cansend_json 1>log_${root}.txt 2>/dev/null &
	pids[${root}]=$!
done

for root in 18 19 21
do
	echo ------------------------------
	echo ${root}
	echo ------------------------------
	wait ${pids[${root}]}
	cat log_${root}.txt
done
