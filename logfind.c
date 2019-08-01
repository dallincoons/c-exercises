#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dbg.h"

#define MAX_LINE 1024

int found_it(int found_count, int words_count) {
    printf("%d\n", words_count);
    if (found_count == words_count) {
        return 1;
    }

    return 0;
}

int scan_file(const char *filename, int word_count, char *words[])
{
    char *line = calloc(MAX_LINE,1);
    FILE *file = fopen(filename, "r");
    char *found = NULL;
    int i = 0;
    int found_count = 0;

    check_mem(line);
    check(file, "Failed to open file: %s", filename);

    while (fgets(line, MAX_LINE-1, file) != NULL && found == NULL) {
        for (i = 0; i < word_count && found == NULL; i++) {
            found = strcasestr(line, words[i]);
            if (found) {
                found_count++;
//                printf("%s\n", filename);
            }
            if (found_it(found_count, word_count)) {
                printf("%s\n", filename);
            }
        }
    }


    error:
        if(line) free(line);
        if(file) fclose(file);

        return -1;
}

void strip_new_line(char* string) {
    if(string[strlen(string)-1] == '\n')
    {
        string[strlen(string)-1] ='\0';
    }
}

int should_use_or_flag(int *use_or, int *argc, char **argv[])
{
    (*argc)--;
    (*argv)++;
    if (strcmp(*argv[0], "-o")) {
        *use_or = 1;
        (*argv)++;
        (*argc)--;
        check(*argc > 1, "you need words after -0");
    }

    return 0;
error:
    return 1;
}

int main(int argc, char *argv[])
{
    int *use_or = 0;

    check(argc > 1, "Usage: logfind log1 log2");

//    scan_file("log2.txt", argc, argv);

//    char *found = NULL;

    FILE *logfiles = fopen("logs.txt", "r");
    char *filename = calloc(MAX_LINE,1);

    check_mem(filename);
    check(logfiles, "Failed to open file: %s", "logs.txt");

    should_use_or_flag(&use_or, &argc, &argv);

    while(fgets(filename, MAX_LINE - 1, logfiles) != NULL) {
        strip_new_line(filename);
        scan_file(filename, argc, argv);
//        for (int i = 1; i < argc && found == NULL; i++) {
//            found = strcasestr(line, argv[i]);
//            if (found) {
//                printf("%s\n", line);
//            }
//        }
    }

    return 0;

error:
    return 1;
}