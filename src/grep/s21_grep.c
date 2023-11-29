#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "s21_grep.h"
#include <stdlib.h>
#include <regex.h>

int main(int argc, char ** argv) {
    grep_t grep;
    initGrep(&grep);
    do {
        grep.option = getopt_long(argc, argv, "e:ivclnhsof:", 0, 0);
        getFlags(&grep);
    } while (grep.option != -1);
    if (argc > 1) {
        argc--;
        argv++;
    }
    if (!grep.flag_e && !grep.flag_f) {
            while (**argv == '-') {
                grep.flags_count += 1;
                argv++;
            }
            *grep.optargGrep = calloc(8048, sizeof(char));
            sprintf(*grep.optargGrep, "%s", *argv);
            grep.optargGrep++;
            grep.optargCount++;
            grep.flags_count++;
            argv++;
    }
    if (grep.optargCount) {
        for (int j = 0; j < grep.optargCount; j++) {
            grep.optargGrep--;
        }
    }
    while (argc && *argv) {
        if (!strcmp(*argv, "-e") || !strcmp(*argv, "-f")) {
            grep.flags_count += 2;
            grep.ef_flg = 1;
            argv++;
        }
        if (**argv == '-' && (strcmp(*argv, "-e") || strcmp(*argv, "-f"))) {
                grep.flags_count++;
        }
        if (**argv != '-' && !grep.ef_flg && grep.endGrep) {
            grep.flags_count = argc - grep.flags_count;
            grep.filename = *argv;
            openFile(&grep);
        }
        argv++;
        grep.ef_flg = 0;
    }
    for (int j = 0; j < grep.optargCount; j++) {
            free(*(grep.optargGrep + j));
        }
    free(grep.optargGrep);
    return 0;
}

void initGrep(grep_t * grep) {
    grep->flag_e = 0;
    grep->flag_i = 0;
    grep->flag_v = 0;
    grep->flag_c = 0;
    grep->flag_l = 0;
    grep->flag_n = 0;
    grep->flag_h = 0;
    grep->flag_s = 0;
    grep->flag_o = 0;
    grep->flag_f = 0;
    grep->option = 0;
    grep->flag_noOpt = 0;
    grep->filename = NULL;
    grep->optargGrep = NULL;
    grep->optargGrep = calloc(1024, sizeof(char *));
    grep->optargCount = 0;
    grep->ef_flg = 0;
    grep->matches_count = 0;
    grep->flags_count = 0;
    grep->numberOfStr = 0;
    grep->matchOrNot = 0;
    grep->matchResult = 0;
    grep->endGrep = 1;
    grep->printOrNot = 0;
}

void getFlags(grep_t * grep) {
    if (grep->option == 'e') {
            grep->flag_e = grep->option;
            *grep->optargGrep = NULL;
            *grep->optargGrep = calloc(8048, sizeof(char));
            sprintf(*grep->optargGrep, "%s", optarg);
            grep->optargGrep++;
            grep->optargCount++;
    } else if (grep->option == 'i') {
            grep->flag_i = grep->option;
    } else if (grep->option == 'v') {
            grep->flag_v = grep->option;
    } else if (grep->option == 'c') {
            grep->flag_c = grep->option;
    } else if (grep->option == 'l') {
            grep->flag_l = grep->option;
    } else if (grep->option == 'n') {
            grep->flag_n = grep->option;
    } else if (grep->option == 'h') {
            grep->flag_h = grep->option;
    } else if (grep->option == 's') {
            grep->flag_s = grep->option;
    } else if (grep->option == 'o') {
            grep->flag_o = grep->option;
    } else if (grep->option == 'f') {
            grep->flag_f = grep->option;
            grep->filename = optarg;
            regFromfile(grep);
    }
    if (grep->option != -1) {
            grep->flag_noOpt = 1;
    }
}

void regFromfile(grep_t * grep) {
    FILE *file;
    if ((file = fopen(grep->filename, "r")) == NULL) {
        printf("s21_grep: %s: No such file or directory\n", grep->filename);
        grep->endGrep = 0;
    } else {
        char str[8024] = {'0'};
        int i = 0;
        while (fgets(str, 8024, file) != NULL) {
           str[strlen(str)] = '\0';
             *grep->optargGrep = NULL;
            *grep->optargGrep = calloc(8048, sizeof(char));
            sprintf(*grep->optargGrep, "%s", str);
            grep->optargGrep++;
            grep->optargCount++;
            i++;
        }

    fclose(file);
    }
}

void openFile(grep_t * grep) {
    FILE *file;
    if ((file = fopen(grep->filename, "r")) == NULL) {
        if (!grep->flag_s)
        printf("s21_grep: %s: No such file or directory\n", grep->filename);
    } else {
        readFile(grep, file);
        fclose(file);
        if (grep->printOrNot) {
            printf("\n");
        }
        grep->printOrNot = 0;
    }
}

void readFile(grep_t * grep, FILE * file) {
    char str[8024] = {'0'};
    while (fgets(str, 8024, file) != NULL) {
        grep->numberOfStr++;
        checkMatches(grep, str);
        if (grep->optargCount) {
            for (int j = 0; j < grep->optargCount; j++) {
            grep->optargGrep--;
            }
        }
    }
    if (grep->flag_c && !grep->flag_l) {
            if (grep->flags_count > 1 && !grep->flag_h) {
                printf("%s:", grep->filename);
            }
        printf("%d\n", grep->matches_count);
    }
    if (grep->flag_l && grep->matches_count > 0) {
        printf("%s\n", grep->filename);
    }
    grep->matches_count = 0;
    grep->numberOfStr = 0;
}

void checkMatches(grep_t * grep, char * str) {
    for (int j = 0; j < grep->optargCount; j++) {
        regex_t     regex;
        grep->matchResult = 1;
        if (regcomp(&regex, *grep->optargGrep, !grep->flag_i ? 0 : REG_ICASE))
               exit(EXIT_FAILURE);
        grep->matchResult = regexec(&regex, str, (size_t)0, NULL, 0);
        regfree(&regex);
        if (!grep->matchResult) {
            grep->matchOrNot = 1;
            if (grep->flag_o) {
                printf("%s\n", *grep->optargGrep);
            }
        }
        if (grep->matchResult == REG_NOMATCH) {
            if (grep->matchOrNot != 1)
            grep->matchOrNot = 0;
        }
        grep->optargGrep++;
    }
    printFunc(grep, str);
    grep->matchOrNot = 0;
}

void printFunc(grep_t * grep, char * str) {
    if (grep->matchOrNot) {
        if (!grep->flag_c && !grep->flag_v && !grep->flag_l) {
            if (grep->flags_count > 1 && !grep->flag_h) {
                printf("%s:", grep->filename);
            }
            if (grep->flag_n) {
            printf("%d:", grep->numberOfStr);
            }
            if (!grep->flag_o)
            printf("%s", str);
            if (str[strlen(str) - 1] != '\n') {
                grep->printOrNot = 1;
            }
        }
        if (!grep->flag_v)
        grep->matches_count++;
        }
    if (!grep->matchOrNot) {
        if (grep->flag_v && !grep->flag_l && !grep->flag_c) {
            if (grep->flags_count > 1 && !grep->flag_h) {
                printf("%s:", grep->filename);
            }
            if (grep->flag_n) {
              printf("%d:", grep->numberOfStr);
            }
            if (!grep->flag_o)
            printf("%s", str);
            if (str[strlen(str) - 1] != '\n') {
                grep->printOrNot = 1;
            }
        }
        if (grep->flag_v) {
                grep->matches_count++;
        }
    }
}
