#!/usr/bin/expect -f

set timeout 20

spawn scp ./src/cat/s21_cat ./src/grep/s21_grep alayna@192.168.0.180:~/

expect {
#    "*yes/no*" { send -- "yes\r" }
    "*password" { send -- "2119041\n" }
}

spawn ssh alayna@192.168.0.180 "echo 2119041 | sudo -S mv ~/s21_cat ~/s21_grep /usr/local/bin/"

expect {
    "*password*" { send -- "2119041\r"}
    eof
}

expect eof