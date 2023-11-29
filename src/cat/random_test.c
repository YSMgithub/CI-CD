//  "Copyright [year] <Copyright Owner>"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_sequence(char *flags, char *buffer);

int main() {
    srand48(time(NULL));
    unsigned int r = lrand48();
    r %= 1000;
    char buffer[7] = {'k', 'k', 'k', 'k'};
    char flags[] = {'b', 'e', 'n', 's', 't', 'v'};
    FILE *file = fopen("gen_output.txt", "w");
    unsigned int z = 0;
    for (unsigned int x = 0; x < r; x++) {
        z = lrand48();
        z %= 127;
        if (z == 10) {
            for (int i = 0; i < 4; i++) {
            fprintf(file, "%c", z);
            i = lrand48();
            i %= 4;
            }
        }
        fprintf(file, "%c", z);
    }
    fclose(file);
    generate_sequence(flags, buffer);
    FILE *newfile = fopen("flags.txt", "w");
    fprintf(newfile, "%s", buffer);
    fclose(newfile);

    return 0;
}

void generate_sequence(char *flags, char *buffer) {
    int i = lrand48();
    i %= 4;
    unsigned int x = 0;
    for (int j = 0; j <= i; j++) {
        x = lrand48();
        x %= 6;
        while ((flags[x] == buffer[0] || flags[x] == buffer[1] || flags[x] == buffer[2]) && j > 0) {
           x = lrand48();
           x %= 6;
        }
        buffer[j] = flags[x];
    }
    for (int j = 0; j < 4; j++) {
        if (buffer[j] == 'k') {
            buffer[j] = '\0';
        }
    }
}
