#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void genpattern(char *argv) {
    srand48(time(NULL));
    FILE *pattern = fopen(argv, "w");
    unsigned int s_r_num = 0;
    s_r_num = lrand48();
    s_r_num %= 3;
    if (s_r_num <= 0)
        s_r_num = 1;
    int max = 126;
    int min = 32;
    for (unsigned int i = 0; i < s_r_num; i++) {
        unsigned int ra_num = lrand48();
        ra_num = min + (ra_num % (max - min));
        if ((ra_num > 32) && (ra_num < 127) &&
            (ra_num != 10 && ra_num != 11) &&
            (ra_num != 42 && ra_num != 92 &&
             ra_num != 93 && ra_num != 91) &&
             ra_num != 45) {
            putc(ra_num, pattern);
        } else {
            putc('f', pattern);
        }
    }
}

void genflags(char *argv) {
    srand48(time(NULL));
    char flags2[] = {'i', 'v', 'c', 'l', 'n', 'h', 's'};
    FILE *flags = fopen(argv, "w");
    int num = 3;
    unsigned int x = 0;
    char buffer[7] = {'k', 'k', 'k', 'k'};
    for (int i = 0; i < num; i++) {
        x = lrand48();
        x %= 7;
        while ((flags2[x] == buffer[0] || flags2[x] == buffer[1] || flags2[x] == buffer[2]) && i > 0) {
            x = lrand48();
            x %= 7;
        }
        buffer[i] = flags2[x];
    }
    for (int j = 0; j < 4; j++) {
        if (buffer[j] == 'k') {
            buffer[j] = '\0';
        }
    }
    fprintf(flags, "%s", buffer);
    fclose(flags);
}

void gentext(char *argv) {
    srand48(time(NULL));
    FILE *text = fopen(argv, "w");
    unsigned int num_s_r = 0;
    num_s_r = lrand48();
    num_s_r %= 10000;
    unsigned int random_num = 0;
    for (unsigned int i = 0; i < num_s_r; i++) {
        random_num = lrand48();
        random_num %= 126;
        if (((random_num > 32) || random_num == 10) && (random_num < 127)) {
            putc(random_num, text);
        }
    }
    fclose(text);
}

int main(int argc, char **argv) {
    srand48(time(NULL));
    int counter = argc;
    if (counter == 4) {
        gentext(argv[1]);
        genflags(argv[2]);
        genpattern(argv[3]);
    }
    return 0;
}
