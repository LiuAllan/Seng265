.#!/bin/bash


#Argument 1: the program we are compiling and testing
test_program="$1"

#Argument 2: expected output to test against
expected_output="$2"

#Use makefile to compile
make $test_program

#Check if the compile ran successfully
# $? Contains the error code of the last command run
#    0 - on success
if [ $? -ne 0 ]; then
    echo "Compile failed ..."
    exit 1
fi

#Compare our result and with expected output
diff <(./$test_program) $expected_output

#Are we right?
if [ $? -eq 0 ]; then
    echo "SUCCESS!"
else
    echo "FAILED!"
    echo "Expected: " $(cat $expected_output)
    echo "Got     : " $(./$test_program)
fi
