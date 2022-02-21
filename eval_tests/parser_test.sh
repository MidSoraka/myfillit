#!/bin/bash
set -e
set -u


test_dir=eval_tests


for file in ${test_dir}/failure_*.txt; do
    test_output="$(./parser_test ${file})"
    if [ ${test_output} == "0" ]; then
        echo "parser_test ${file} - success"
    else
        echo "parser_test ${file} - failure"
        exit -1
    fi
done


for file in ${test_dir}/success_*.txt; do
    test_output="$(./parser_test ${file})"
    if [ ${test_output} == "1" ]; then
        echo "parser_test ${file} - success"
    else
        echo "parser_test ${file} - failure"
        exit -1
    fi
done
