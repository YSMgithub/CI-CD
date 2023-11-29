#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_


typedef struct grep_s {
    int option;
    int flag_e;
    int flag_i;
    int flag_v;
    int flag_c;
    int flag_l;
    int flag_n;
    int flag_h;
    int flag_s;
    int flag_o;
    int flag_f;
    char * filename;
    int flag_noOpt;
    char ** optargGrep;
    int optargCount;
    int ef_flg;
    int matches_count;
    int flags_count;
    int matchResult;
    int numberOfStr;
    int matchOrNot;
    int endGrep;
    int printOrNot;
} grep_t;

void getFlags(grep_t * grep);
void initGrep(grep_t * grep);
void openFile(grep_t * grep);
void readFile(grep_t * grep, FILE * file);
void checkMatches(grep_t * grep, char * str);
void printFunc(grep_t * grep, char * str);
void regFromfile(grep_t * grep);
#endif  //  SRC_GREP_S21_GREP_H_
