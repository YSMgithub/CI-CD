#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define OFFSET_ASCII 64
#define YES 1
#define NO 0

static struct option long_option[] = {{"number-nonblank", 0, 0, 'b'},
                                      {"number", 0, 0, 'n'},
                                      {"squeeze-blank", 0, 0, 's'},
                                      {0, 0, 0, 0}};

typedef struct flags_s {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int pred;
    int ch;
    int c_count;
    int print;
    int l_count;
} flags_t;

void initCat(flags_t * flags);
void take_flag(char option, flags_t * flags);
void s_flag(flags_t * flags);
void n_flag(flags_t * flags);
void t_flag(flags_t * flags);
void b_flag(flags_t * flags);
void e_flag(flags_t * flags);
void v_flag(flags_t * flags);

#endif  //  SRC_CAT_S21_CAT_H_
