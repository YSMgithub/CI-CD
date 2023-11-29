#!/bin/bash

gcc random_test.c -o random

touch flags.txt
touch gen_output.txt
touch myoutput.txt
touch stand_out_cat.txt

i=1
c=0

func() {
    ./random
    fl="$(cat flags.txt)"
    echo "TEST#$i FLAGS:($fl)"
cat -$fl gen_output.txt > stand_out_cat.txt
./s21_cat -$fl gen_output.txt > myoutput.txt
((++i))
diff stand_out_cat.txt myoutput.txt
if [ $? = 0 ]
    then 
        echo SUCCESED 
    else 
        echo FAILED FLAGS $fl
fi
}

while [ $c -lt 20 ]
do
    func
    ((++c))
    sleep 1s
done