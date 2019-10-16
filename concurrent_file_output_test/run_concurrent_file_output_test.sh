#!/bin/sh

for i in `seq 1000`
do
  ./concurrent_file_output_test ${i} &
done
