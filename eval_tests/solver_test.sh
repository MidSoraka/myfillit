#!/bin/bash

now=$(date +"%T")
echo "This test was ran on fillit: $now" >> test.txt
for file in eval_tests/success_03_*.txt;
	do
	echo "processing ${file}"
	echo "processing ${file}" >> test.txt
	for ((i=1; i<=10; i++))
	do
		timeout 10s ./solver_test ${file} >> test.txt
		exit_status=$?
		if [[ $exit_status -eq 124 ]]; then
    		echo "TIMEOUT" >> test.txt
		fi
	done
done
