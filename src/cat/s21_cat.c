//  "Copyright [year] <Copyright Owner>"

#include "./s21_cat.h"

int main(int argc, char **argv) {
    int option_index, option = 0;
    flags_t flags;
    FILE *file;
    initCat(&flags);
    while ((option = getopt_long(argc, argv, "beEnstv", long_option,
                                 &option_index)) != -1) {
        take_flag(option, &flags);
    }
    if (argc > 1) {
        for (int i = 0; argv++ && (i < argc - 1); i++) {
            if ((strlen((*argv)) > 2) && (**(argv) != '-')) {
                if ((file = fopen(*argv, "r")) == NULL) {
                    printf("s21_cat: %s: No such file or directory", *argv);
                } else {
                    while ((flags.ch = getc(file)) != EOF) {
                        flags.print = YES;
                        if (flags.s) {
                            s_flag(&flags);
                        }
                        if (flags.n && !flags.b) {
                            n_flag(&flags);
                        }
                        if (flags.b) {
                            b_flag(&flags);
                        }
                        if (flags.t) {
                            t_flag(&flags);
                        }
                        if (flags.e) {
                            e_flag(&flags);
                        }
                        if (flags.v) {
                            v_flag(&flags);
                        }
                        if (flags.print) {
                            putc(flags.ch, stdout);
                        }
                        flags.pred = flags.ch;
                    }
                    fclose(file);
                }
            }
        }
    }
    return 0;
}

void initCat(flags_t * flags) {
    flags->b = 0;
    flags->e = 0;
    flags->n = 0;
    flags->s = 0;
    flags->t = 0;
    flags->v = 0;
    flags->c_count = 0;
    flags->ch = '\n';
    flags->pred = '\n';
    flags->print = 1;
    flags->l_count = 0;
}

void take_flag(char option, flags_t * flags) {
    if (option == 'b') {
        flags->b = option;
    } else if (option == 'e') {
        flags->v = 1;
        flags->e = option;
    } else if (option == 'n') {
        flags->n = option;
    } else if (option == 's') {
        flags->s = option;
    } else if (option == 't') {
        flags->v = 1;
        flags->t = option;
    } else if (option == 'v') {
        flags->v = option;
    } else if (option == 'E') {
        flags->e = option;
    } else if (option == 'T') {
        flags->t = option;
    }
}

void s_flag(flags_t * flags) {
    if ((flags->ch == '\n') && (flags->pred == '\n')) {
        flags->l_count += 1;
    }
    if (flags->ch != '\n') {
        flags->l_count = 0;
        flags->print = YES;
    }
    if (flags->l_count > 1) {
        flags->print = NO;
    }
}

void n_flag(flags_t * flags) {
    if (flags->pred == '\n') {
        if (flags->print == YES) {
            printf("%6d\t", flags->c_count += 1);
        }
    }
}

void t_flag(flags_t * flags) {
    if (flags->ch == '\t') {
        printf("^I");
        flags->print = NO;
    }
}

void b_flag(flags_t * flags) {
    if (flags->ch != '\n' && flags->pred == '\n') {
        printf("%6d\t", flags->c_count += 1);
    }
}

void e_flag(flags_t * flags) {
    if (flags->ch == '\n') {
        if (flags->print == YES) {
            printf("$");
        }
    }
}

void v_flag(flags_t * flags) {
    if (flags->ch >= 0 && flags->ch <= 31 && flags->ch != '\n' && flags->ch != '\t') {
        printf("^%c", flags->ch + OFFSET_ASCII);
        flags->print = NO;
    }
    if ((flags->ch > 127) && (flags->ch < 256)) {
        printf("M-%c", flags->ch - 128);
        flags->print = NO;
    }
    if (flags->ch == 127) {
        printf("^?");
        flags->print = NO;
    }
}
