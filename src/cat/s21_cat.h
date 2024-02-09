//
// Created by Иван Карплюк on 03.02.2024.
//

#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

typedef struct flag_struct {
    unsigned int b: 1;
    unsigned int e: 1;
    unsigned int E: 1;
    unsigned int n: 1;
    unsigned int s: 1;
    unsigned int t: 1;
    unsigned int T: 1;
    unsigned int v: 1;
} flags_t;

// Working with flags
flags_t *create_flags_struct();

int is_default_flags(char *arg_str);

int is_GNU_flags(char *arg_str);

int check_default_flags(flags_t *flags,
                        char *str_with_flags,
                        char *prog_name);

int check_GNU_flags(flags_t *flags,
                    char *str_with_flags,
                    char *prog_name);

// Working with file
void go_through_files(int agrc,
                      char **argv,
                      int file_index,
                      flags_t *flags);

void output_file(FILE *fp,
                 flags_t *flags);

// Base func
void start_cat_function(int argc,
                        char **argv);

void repeat_user_input_mode();

#endif //SRC_CAT_S21_CAT_H_
