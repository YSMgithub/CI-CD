#!/bin/bash

gcc test_grep.c -o test_grep

touch text
touch flags
touch pattern
touch myoutput.txt
touch stand_out.txt

i=1
c=0

func() {
    ./test_grep text flags pattern
    fl="$(cat flags)"
    pat="$(cat pattern)"
    echo "TEST#$i: s21_grep $pat text -$fl"
grep -$fl $pat text > stand_out.txt
./s21_grep -$fl $pat text > myoutput.txt
((++i))
diff stand_out.txt myoutput.txt
if [ $? = 0 ]
    then 
        echo SUCCESED
    else 
        echo FAILED FLAGS:$fl
        sleep 3s
fi
}

funcE() {
    ./test_grep text flags pattern
    fl="$(cat flags)"
    pat="$(cat pattern)"
    echo "TEST#$i: s21_grep -e $pat text -$fl"
grep -e $pat -$fl text > stand_out.txt
./s21_grep -e $pat -$fl  text > myoutput.txt
((++i))
diff stand_out.txt myoutput.txt
if [ $? = 0 ]
    then 
        echo SUCCESED
    else 
        echo FAILED FLAGS:$fl
        sleep 3s
fi
}

funcFile() {
    ./test_grep text flags pattern
    pat="$(cat pattern)"
    echo "TEST#$i: -f pattern text"
grep -f pattern text > stand_out.txt
./s21_grep -f pattern text > myoutput.txt
((++i))
diff stand_out.txt myoutput.txt
if [ $? = 0 ]
    then 
        echo SUCCESED
    else 
        echo FAILED
        sleep 3s
fi
}

while [ $c -lt 10 ]
do
    func
    ((++c))
    sleep 1s
done

while [ $c -lt 20 ]
do
    funcE
    ((++c))
    sleep 1s
done

while [ $c -lt 25 ]
do
    funcFile
    ((++c))
    sleep 1s
done