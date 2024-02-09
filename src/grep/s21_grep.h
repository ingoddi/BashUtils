//
// Created by Иван Карплюк on 30.12.2023.
//
//


#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <regex.h>
#include <unistd.h>


typedef struct flags {
    unsigned int e: 1;
    unsigned int i: 1;
    unsigned int v: 1;
    unsigned int c: 1;
    unsigned int l: 1;
    unsigned int n: 1;
    unsigned int h: 1;
    unsigned int s: 1;
    unsigned int f: 1;
    unsigned int o: 1;
} flags_t;

typedef struct list {
    char name[256];
    struct list *next;
} list_node;

// Struct building funcs
flags_t *create_flags_struct();

list_node *create_node(char *string);

// Working with Struct
void add_element_to_list(list_node *head,
                         char *keyword_str);

void free_list(list_node *head);

// Working with flags
void get_all_flags(int argc,
                   char **argv,
                   flags_t *flags);

void handle_c_flag(flags_t *flags,
                   int matches,
                   int no_matches,
                   int files_count,
                   char *file_name);

int is_flags(const char *arg_str);

int is_e_flag(int arg_index,
              char **argv);

int check_flags(char *str_with_flags,
                flags_t *flags);

int handle_L_flag(flags_t *flags,
                  int find,
                  int *need_L_print);

int handle_f_flag(int argc,
                  char **argv,
                  int *i,
                  list_node **keyword_head);

// Working with Files
void get_keywords_and_files(int argc,
                            char **argv,
                            list_node **keywords_head,
                            list_node **files_head,
                            flags_t *flags);

void go_through_files(list_node *files,
                      list_node *keywords,
                      flags_t *flags);

int count_files(list_node *files_head);

void add_keywords_from_file(char *file_name,
                            list_node **keyword_head);

void file_processing_O(FILE *fp,
                       list_node *keywords,
                       flags_t *flags,
                       int files_nmb,
                       char *file_name);

// Base func
void output_error_and_exit();

void start_grep_function(int argc,
                         char **argv);

void file_processing(FILE *fp,
                     list_node *keywords,
                     flags_t *flags,
                     int files_nmb,
                     char *file_name);

// Additional
void trim_n(char *line);

void s21_itoa(int m,
              char *str);

void handle_O_pattern(char *str,
                      list_node *keywords,
                      char *file_name,
                      int files_count,
                      flags_t *flags,
                      int line_nmb,
                      int *line_printed);

void print_o_match(size_t offset,
                   regmatch_t match,
                   char *buff,
                   flags_t *flags,
                   int line_nmb,
                   int *line_printed,
                   int files_count,
                   char *file_name);

int check_e_in_middle(char *arg_str,
                      list_node **keyword_head,
                      flags_t *flags);

int find_keyword_in_string(char *str,
                           list_node *keyword,
                           flags_t *flags);

int do_regcomp(regex_t *regex,
               flags_t *flags,
               char *keyword);

#endif  // SRC_GREP_S21_GREP_H_