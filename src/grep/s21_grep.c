//
// Created by Иван Карплюк on 30.12.2023.
//
//

/**
 * @file s21_grep.c
 * @brief Implementation of the grep utility in C
 *
 * This file contains the implementation of the grep utility in C.
 * The grep utility searches for patterns in files
 * and prints the lines that match the patterns.
 *
 */

#include "s21_grep.h"


/**
 * @brief Main function
 *
 * The main function of the program. It checks the command-line arguments
 * and calls the start_grep_function to start the grep process.
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * @return 0 if the program executed successfully, 1 otherwise
 */
int main(int argc, char **argv) {
    if (argc < 3) {
        output_error_and_exit();
    } else {
        start_grep_function(argc, argv);
    }
    return 0;
}

/**
 * @brief Prints an error message and exits the program
 *
 * This function is called when the command-line arguments are invalid. It prints an error message
 * and exits the program with a non-zero status code.
 */
void output_error_and_exit() {
    printf("usage: ./s21_grep [-parameters] [-f file] [file]\n");
    exit(1);
}

/**
 * @brief Starts the grep function
 *
 * This function creates the necessary data structures, parses the command-line arguments,
 * and calls the go_through_files function to perform the grep operation.
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 */
void start_grep_function(int argc,
                         char **argv) {
    flags_t *flags = create_flags_struct();
    list_node *keywords_head = NULL;
    list_node *files_head = NULL;
    get_all_flags(argc, argv, flags);
    get_keywords_and_files(argc, argv, &keywords_head, &files_head, flags);
    go_through_files(files_head, keywords_head, flags);
    free(flags);
    free_list(files_head);
    free_list(keywords_head);
}

/**
 * @brief Creates a flags_t structure
 *
 * This function dynamically allocates memory for a flags_t structure
 * and initializes its fields to zero.
 *
 * @return A pointer to the created flags_t structure
 */
flags_t *create_flags_struct() {
    flags_t *flags = malloc(sizeof(flags_t));
    flags->e = 0;
    flags->i = 0;
    flags->v = 0;
    flags->c = 0;
    flags->l = 0;
    flags->n = 0;
    flags->h = 0;
    flags->s = 0;
    flags->f = 0;
    flags->o = 0;
    return flags;
}

/**
 * @brief Parses the command-line arguments and sets the flags
 *
 * This function iterates over the command-line arguments and checks for valid flags.
 * It sets the corresponding fields in the flags_t structure.
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * @param flags A pointer to the flags_t structure
 */
void get_all_flags(int argc,
                   char **argv,
                   flags_t *flags) {
    for (int i = 1; i < argc; i++) {
        if (is_flags(argv[i]) && !is_e_flag(i - 1, argv)) {
            int status = check_flags(argv[i], flags);
            if (!status)
                output_error_and_exit();
        }
    }
}

/**
 * @brief Checks if a string is a flag
 *
 * This function checks if a string starts with a hyphen,
 * indicating that it is a flag.
 *
 * @param arg_str The string to check
 * @return 1 if the string is a flag, 0 otherwise
 */
int is_flags(const char *arg_str) {
    int ret_value = 0;
    if (*arg_str == '-') {
        ret_value = 1;
    }
    return ret_value;
}

/**
 * @brief Checks if a flag is the -e flag
 *
 * This function checks if a flag is the -e flag by examining the
 * previous argument in the command-line arguments.
 *
 * @param arg_index The index of the flag in the command-line arguments
 * @param argv The array of command-line arguments
 * @return 1 if the flag is the -e flag, 0 otherwise
 */
int is_e_flag(int arg_index,
              char **argv) {
    int ret_val = 0;
    if (arg_index >= 1) {
        int len = strlen(argv[arg_index]);
        if (*(argv[arg_index]) == '-' && *(argv[arg_index] + 1) == 'e' && *(argv[arg_index] + 2) == 0)
            ret_val = 1;
        else if (argv[arg_index][len - 1] == 'e' && argv[arg_index][0] == '-' && argv[arg_index][1] != 'e')
            ret_val = 1;
    }
    return ret_val;
}

/**
 * @brief Checks and sets the flags based on a string with flags
 *
 * This function checks and sets the flags based on a string with flags.
 * It iterates over the characters in the string and sets the corresponding
 * fields in the flags_t structure.
 *
 * @param str_with_flags The string with flags
 * @param flags A pointer to the flags_t structure
 * @return 1 if the flags are valid, 0 otherwise
 */
int check_flags(char *str_with_flags,
                flags_t *flags) {
    int return_val = 1;
    if (*str_with_flags == '-') str_with_flags++;  // [-eivclnhso]
    while (*str_with_flags) {
        if (*str_with_flags == 'e') {
            flags->e = 1;
            break;
        } else if (*str_with_flags == 'i') {
            flags->i = 1;
            str_with_flags++;
            continue;
        } else if (*str_with_flags == 's') {
            flags->s = 1;
            str_with_flags++;
            continue;
        } else if (*str_with_flags == 'v') {
            flags->v = 1;
            str_with_flags++;
            continue;
        } else if (*str_with_flags == 'c') {
            flags->c = 1;
            str_with_flags++;
            continue;
        } else if (*str_with_flags == 'l') {
            flags->l = 1;
            str_with_flags++;
            continue;
        } else if (*str_with_flags == 'n') {
            flags->n = 1;
            str_with_flags++;
            continue;
        } else if (*str_with_flags == 'h') {
            flags->h = 1;
            str_with_flags++;
            continue;
        } else if (*str_with_flags == 'o') {
            flags->o = 1;
            str_with_flags++;
            continue;
        } else if (*str_with_flags == 'f') {
            flags->f = 1;
            break;
        } else {
            printf("s21_grep: invalid option -- %c\n", *str_with_flags);
            return_val = 0;
            break;
        }
    }
    return return_val;
}

/**
 * @brief Creates a new node for the keyword list
 *
 * This function creates a new node for the keyword list
 * and copies the keyword string into the node.
 *
 * @param string The keyword string
 * @return A pointer to the created node
 */
list_node *create_node(char *string) {
    list_node *keyword_node = malloc(sizeof(list_node));
    strcpy(keyword_node->name, string);
    keyword_node->next = NULL;
    return keyword_node;
}

/**
 * @brief Adds an element to the end of the list
 *
 * This function adds an element to the end of the list. If the list is empty,
 * it creates a new node and sets it as the head of the list. Otherwise, it traverses the list
 * and adds the element to the end.
 *
 * @param head The head of the list
 * @param keyword_str The keyword string to add
 */
void add_element_to_list(list_node *head,
                         char *keyword_str) {
    while (head) {
        if (!head->next) {
            head->next = create_node(keyword_str);
            break;
        } else {
            head = head->next;
        }
    }
}

/**
 * @brief Frees the memory allocated for the list
 *
 * This function frees the memory allocated for the list by traversing the list and freeing each node.
 *
 * @param head The head of the list
 */
void free_list(list_node *head) {
    while (head) {
        list_node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

/**
 * @brief Parses the command-line arguments and extracts the keywords and files
 *
 * This function parses the command-line arguments and extracts the keywords and files.
 * It adds the keywords to the keyword list and the files to the file list.
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * @param keywords_head A pointer to the head of the keyword list
 * @param files_head A pointer to the head of the file list
 * @param flags A pointer to the flags_t structure
 */
void get_keywords_and_files(int argc,
                            char **argv,
                            list_node **keywords_head,
                            list_node **files_head,
                            flags_t *flags) {
    int meet_keyword = 0;
    for (int i = 1; i < argc; i++) {
        if (flags->f)
            if (handle_f_flag(argc, argv, &i, keywords_head))
                continue;
        if (is_flags(argv[i]) && check_e_in_middle(argv[i], keywords_head, flags))
            continue;
        if ((flags->e && is_e_flag(i - 1, argv)) ||
            (!flags->e && !is_flags(argv[i]) && !meet_keyword && !flags->f)) {
            if (*keywords_head == NULL)
                *keywords_head = create_node(argv[i]);
            else
                add_element_to_list(*keywords_head, argv[i]);
            meet_keyword = 1;
        } else if (!is_flags(argv[i])) {
            if (*files_head == NULL)
                *files_head = create_node(argv[i]);
            else
                add_element_to_list(*files_head, argv[i]);
        }
    }
}

/**
 * @brief Checks if the -e flag is in the middle of a string
 *
 * This function checks if the -e flag is in the middle of a string
 * and adds the substring after the -e flag to the keyword list.
 *
 * @param arg_str The string to check
 * @param keyword_head A pointer to the head of the keyword list
 * @param flags A pointer to the flags_t structure
 * @return 1 if the -e flag is in the middle of the string, 0 otherwise
 */
int check_e_in_middle(char *arg_str,
                      list_node **keyword_head,
                      flags_t *flags) {
    int ret_val = 0;
    if (flags->e) {
        while (*arg_str) {
            if (*arg_str == 'e' && *(arg_str + 1) != 0) {
                if (*keyword_head == NULL)
                    *keyword_head = create_node((arg_str + 1));
                else
                    add_element_to_list(*keyword_head, (arg_str + 1));
                ret_val = 1;
                break;
            }
            arg_str++;
        }
    }
    return ret_val;
}

/**
 * @brief Performs the grep operation on the files
 *
 * This function performs the grep operation on the files. It opens each file,
 * reads its contents line by line, and searches for the keywords.
 * It prints the matching lines based on the specified flags.
 *
 * @param files The head of the file list
 * @param keywords The head of the keyword list
 * @param flags A pointer to the flags_t structure
 */
void go_through_files(list_node *files,
                      list_node *keywords,
                      flags_t *flags) {
    int files_nmb = count_files(files);
    while (files) {
        FILE *fp = fopen(files->name, "r+");
        if (!fp) {
            if (!flags->s)
                printf("s21_grep: %s: %s\n", files->name, strerror(errno));
        } else {
            if (flags->o && !flags->c && !flags->l && !flags->v) {
                file_processing_O(fp, keywords, flags, files_nmb, files->name);
            } else {
                file_processing(fp, keywords, flags, files_nmb, files->name);
            }
            fclose(fp);
        }
        files = files->next;
    }
}

/**
 * @brief Performs the grep operation on a file
 *
 * This function performs the grep operation on a file. It reads the file line by line,
 * searches for the keywords, and prints the matching lines based on the specified flags.
 *
 * @param fp The file pointer of the file to process
 * @param keywords The head of the keyword list
 * @param flags A pointer to the flags_t structure
 * @param files_nmb The number of files being processed
 * @param file_name The name of the file being processed
 */
void file_processing(FILE *fp,
                     list_node *keywords,
                     flags_t *flags,
                     int files_nmb,
                     char *file_name) {
    char buff[500];
    int line_counter = 0, matches_count = 0, no_matches_count = 0, need_L_print = 0;;
    while (fgets(buff, sizeof(buff), fp)) {
        line_counter++;
        int find = find_keyword_in_string(buff, keywords, flags);
        int len = strlen(buff);
        if (buff[len - 1] != '\n')
            strcpy(&buff[len], "\n");
        if (flags->c && find)
            matches_count++;
        else
            matches_count += find;
        if (find == 0) {
            no_matches_count++;
        }
        if (handle_L_flag(flags, find, &need_L_print))
            break;
        if (((find && !flags->v) || (!find && flags->v)) && !flags->c) {
            if (files_nmb > 1 && !flags->h)
                printf("%s:", file_name);
            if (flags->n)
                printf("%d:", line_counter);
            printf("%s", buff);
        }
    }
    handle_c_flag(flags, matches_count, no_matches_count, files_nmb, file_name);
    if (need_L_print)
        printf("%s\n", file_name);
}

/**
 * @brief Searches for keywords in a string
 *
 * This function searches for keywords in a string. It uses regular expressions to match the keywords in the string.
 *
 * @param str The string to search in
 * @param keyword The head of the keyword list
 * @param flags A pointer to the flags_t structure
 * @return The number of matches found
 */
int find_keyword_in_string(char *str,
                           list_node *keyword,
                           flags_t *flags) {
    int ret_val = 0, find, regcomp_result;
    regex_t regex;
    while (keyword) {
        if (flags->i)
            regcomp_result = regcomp(&regex, keyword->name, REG_ICASE);
        else
            regcomp_result = regcomp(&regex, keyword->name, 0);
        if (regcomp_result != 0) {
            keyword = keyword->next;
            regfree(&regex);
            continue;
        }
        find = regexec(&regex, str, 0, NULL, 0);
        if (find == 0)
            ret_val++;
        regfree(&regex);
        keyword = keyword->next;
    }
    return ret_val;
}

/**
 * @brief Counts the number of files in the list
 *
 * This function counts the number of files in the list by traversing the list and incrementing a counter.
 *
 * @param files_head The head of the file list
 * @return The number of files in the list
 */
int count_files(list_node *files_head) {
    int result = 0;
    while (files_head) {
        result++;
        files_head = files_head->next;
    }
    return result;
}

/**
 * @brief Handles the -c flag
 *
 * This function handles the -c flag by printing the number of matches and non-matches for each file.
 *
 * @param flags A pointer to the flags_t structure
 * @param matches The number of matches
 * @param no_matches The number of non-matches
 * @param files_count The number of files being processed
 * @param file_name The name of the file being processed
 */
void handle_c_flag(flags_t *flags,
                   int matches,
                   int no_matches,
                   int files_count,
                   char *file_name) {
    if (flags->c) {
        if (files_count > 1 && !flags->h)
            printf("%s:", file_name);
        if (flags->v)
            printf("%d\n", no_matches);
        else
            printf("%d\n", matches);
    }
}

/**
 * @brief Handles the -L flag
 *
 * This function handles the -L flag by checking if a match is found and setting the need_L_print flag accordingly.
 *
 * @param flags A pointer to the flags_t structure
 * @param find The number of matches found
 * @param need_L_print A pointer to the need_L_print flag
 * @return 1 if the -L flag is triggered, 0 otherwise
 */
int handle_L_flag(flags_t *flags,
                  int find,
                  int *need_L_print) {
    int res = 0;
    if (((find && !flags->v) || (!find && flags->v)) && flags->l) {
        res = 1;
        *need_L_print = 1;
    }
    return res;
}

/**
 * @brief Handles the -f flag
 *
 * This function handles the -f flag by checking if the flag is present in the command-line arguments and adding the keywords from the specified file to the keyword list.
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * @param i A pointer to the current index in the command-line arguments
 * @param keyword_head A pointer to the head of the keyword list
 * @return 1 if the -f flag is handled, 0 otherwise
 */
int handle_f_flag(int argc,
                  char **argv,
                  int *i, list_node **keyword_head) {
    int ret_value = 0;
    int len = strlen(argv[*i]);
    char *ptr_to_f;
    if (argv[*i][0] == '-' && ((argv[*i][1] == 'f' && argv[*i][2] == '\0') || argv[*i][len - 1] == 'f')) {
        if (*(i + 1) < argc) {
            add_keywords_from_file(argv[*i + 1], keyword_head);
            *i += 1;
            ret_value = 1;
        } else {
            output_error_and_exit();
        }
    } else if (argv[*i][0] == '-' && (ptr_to_f = strchr(argv[*i], 'f')) && *(ptr_to_f + 1) != '\0') {
        add_keywords_from_file(ptr_to_f + 1, keyword_head);
    }
    return ret_value;
}

/**
 * @brief Adds keywords from a file to the keyword list
 *
 * This function opens the specified file, reads its contents line by line, and adds each line as a keyword to the keyword list.
 *
 * @param file_name The name of the file
 * @param keyword_head A pointer to the head of the keyword list
 */
void add_keywords_from_file(char *file_name,
                            list_node **keyword_head) {
    FILE *fp = fopen(file_name, "r+");
    if (!fp) {
        printf("s21_grep: %s: %s\n", file_name, strerror(errno));
        exit(2);
    }
    char buff[256];
    while (fgets(buff, sizeof(buff), fp)) {
        int len = strlen(buff);
        if (buff[len - 1] == '\n' && len != 1)
            buff[len - 1] = 0;
        if (*keyword_head == NULL)
            *keyword_head = create_node(buff);
        else
            add_element_to_list(*keyword_head, buff);
    }
}

/**
 * @brief Performs the grep operation with the -O flag
 *
 * This function performs the grep operation with the -O flag. It reads the file line by line, searches for the keywords, and prints the matching parts of the lines based on the specified flags.
 *
 * @param fp The file pointer of the file to process
 * @param keywords The head of the keyword list
 * @param flags A pointer to the flags_t structure
 * @param files_nmb The number of files being processed
 * @param file_name The name of the file being processed
 */
void file_processing_O(FILE *fp,
                       list_node *keywords,
                       flags_t *flags,
                       int files_nmb,
                       char *file_name) {
    char buff[500];
    int line_nmb = 0;
    while (fgets(buff, sizeof(buff), fp)) {
        line_nmb++;
        int line_printed = 0;
        handle_O_pattern(buff, keywords, file_name, files_nmb, flags, line_nmb, &line_printed);
    }
}

/**
 * @brief Handles the -O pattern matching
 *
 * This function handles the -O pattern matching. It searches for the keywords in a line and prints the matching parts of the line based on the specified flags.
 *
 * @param str The line to search in
 * @param keywords The head of the keyword list
 * @param file_name The name of the file being processed
 * @param files_count The number of files being processed
 * @param flags A pointer to the flags_t structure
 * @param line_nmb The line number
 * @param line_printed A pointer to the line_printed flag
 */
void handle_O_pattern(char *str,
                      list_node *keywords,
                      char *file_name,
                      int files_count,
                      flags_t *flags,
                      int line_nmb,
                      int *line_printed) {
    regex_t regex;
    trim_n(str);
    while (keywords) {
        int comp_res = do_regcomp(&regex, flags, keywords->name);
        if (!comp_res) {
            regmatch_t match;
            size_t offset = 0;
            size_t len = strlen(str);
            int eflags = 0;
            while (regexec(&regex, str + offset, 1, &match, eflags) == 0) {
                eflags = REG_NOTBOL;
                print_o_match(offset, match, str, flags, line_nmb, line_printed, files_count, file_name);
                offset += match.rm_eo;
                if (match.rm_so == match.rm_eo)
                    offset++;
                if (offset > len)
                    break;
            }
        }
        regfree(&regex);
        keywords = keywords->next;
    }
}

/**
 * @brief Prints the matched substring from the given buffer.
 *
 * @param offset The starting offset of the match in the buffer.
 * @param match The regmatch_t struct containing the match information.
 * @param buff The buffer containing the text to search.
 * @param flags The flags_t struct containing the program flags.
 * @param line_nmb The line number of the match.
 * @param line_printed A pointer to the flag indicating if the line number has been printed.
 * @param files_count The number of files being searched.
 * @param file_name The name of the current file being searched.
 */
void print_o_match(size_t offset,
                   regmatch_t match,
                   char *buff,
                   flags_t *flags,
                   int line_nmb,
                   int *line_printed,
                   int files_count,
                   char *file_name) {
    if (!flags->c && !flags->l) {
        if (files_count > 1 && !flags->h)
            printf("%s:", file_name);
        if (flags->n && !(*line_printed)) {
            printf("%d:", line_nmb);
            *line_printed = 1;
        }
    }
    for (size_t i = offset + match.rm_so; i < offset + match.rm_eo; i++)
        printf("%c", buff[i]);
    printf("\n");
}

/**
 * @brief Compiles the regular expression pattern.
 *
 * @param regex A pointer to the regex_t struct to store the compiled pattern.
 * @param flags The flags_t struct containing the program flags.
 * @param keyword The keyword to search for.
 * @return The result of the regcomp function call.
 */
int do_regcomp(regex_t *regex,
               flags_t *flags,
               char *keyword) {
    int comp_val;
    if (flags->i)
        comp_val = regcomp(regex, keyword, REG_ICASE);
    else
        comp_val = regcomp(regex, keyword, 0);
    return comp_val;
}

/**
 * @brief Trims the newline character from the end of the line.
 *
 * @param line The line to trim.
 */
void trim_n(char *line) {
    if (strlen(line) == 1 && line[0] == '\n') line[0] = '.';
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
}