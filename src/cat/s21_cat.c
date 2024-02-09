//
// Created by Иван Карплюк on 03.02.2024.
//

/**
 * @file s21_cat.c
 * @brief Implementation of the cat utility in C
 *
 * This file contains the implementation of the cat utility in C.
 *
 */

#include "s21_cat.h"

/**
 * @brief Main function
 *
 * The main function of the program. It checks the command-line arguments
 * and calls the start_сat_function to start the grep process.
 *
 * @param argc The number of command-line arguments
 * @param argv The array of command-line arguments
 * @return 0 if the program executed successfully, 1 otherwise
 */

int main(int argc, char **argv) {
    if (argc == 1)
        repeat_user_input_mode();
    else if (argc >= 2)
        start_cat_function(argc, argv);
    return 0;
}

/**
 * @brief Repeats the user input mode.
 */
void repeat_user_input_mode() {
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
}

/**
 * @brief Starts the cat function.
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 */
void start_cat_function(int argc, char **argv) {
    flags_t *flags = create_flags_struct();
    int arg_index = 1;
    while (arg_index < argc &&
           (is_GNU_flags(argv[arg_index]) || is_default_flags(argv[arg_index]))) {
        int ret_val = 0;
        if (is_default_flags(argv[arg_index]))
            ret_val = check_default_flags(flags, argv[arg_index], argv[0]);
        else
            ret_val = check_GNU_flags(flags, argv[arg_index], argv[0]);
        if (ret_val == 0) {
            printf("usage: %s [-benstv] [file ...]\n", argv[0]);
            exit(1);
        }
        if (flags->b && flags->n) {
            flags->n = 0;
        }
        arg_index++;
    }
    go_through_files(argc, argv, arg_index, flags);
    free(flags);
}

/**
 * @brief Creates a flags struct.
 * @return A pointer to the created flags struct.
 */
flags_t *create_flags_struct() {
    flags_t *flags = malloc(sizeof(flags_t));
    flags->b = 0;
    flags->e = 0;
    flags->E = 0;
    flags->n = 0;
    flags->s = 0;
    flags->t = 0;
    flags->T = 0;
    flags->v = 0;
    return flags;
}

/**
 * @brief Checks if the argument string contains default flags.
 * @param arg_str The argument string.
 * @return 1 if the argument string contains default flags, 0 otherwise.
 */
int is_default_flags(char *arg_str) {
    int ret_val = 0;
    if (*arg_str == '-' && *(arg_str + 1) != '-')
        ret_val = 1;
    return ret_val;
}

/**
 * @brief Checks if the argument string contains GNU flags.
 * @param arg_str The argument string.
 * @return 1 if the argument string contains GNU flags, 0 otherwise.
 */
int is_GNU_flags(char *arg_str) {
    int ret_val = 0;
    if (*arg_str == '-' && *(arg_str + 1) == '-')
        ret_val = 1;
    return ret_val;
}

/**
 * @brief Checks the default flags and updates the flags struct accordingly.
 * @param flags A pointer to the flags struct.
 * @param str_with_flags The string containing the default flags.
 * @param prog_name The name of the program.
 * @return 1 if the default flags are valid, 0 otherwise.
 */
int check_default_flags(flags_t *flags, char *str_with_flags, char *prog_name) {
    int return_val = 1;
    if (*str_with_flags == '-') str_with_flags++;
    while (*str_with_flags) {
        switch (*str_with_flags) {
            case 'b':
                flags->b = 1;
                break;
            case 'e':
                flags->e = 1;
                if (!flags->v) {
                    flags->v = 1;
                }
                break;
            case 'E':
                flags->e = 1;
                break;
            case 'n':
                flags->n = 1;
                break;
            case 's':
                flags->s = 1;
                break;
            case 't':
                flags->t = 1;
                if (!flags->v) {
                    flags->v = 1;
                }
                break;
            case 'T':
                flags->t = 1;
                break;
            case 'v':
                flags->v = 1;
                break;
            default:
                printf("%s: illegal option -- %c\n", prog_name, *str_with_flags);
                return_val = 0;
                break;
        }
        str_with_flags++;
    }
    return return_val;
}

/**
 * @brief Checks the GNU flags and updates the flags struct accordingly.
 * @param flags A pointer to the flags struct.
 * @param str_with_flags The string containing the GNU flags.
 * @param prog_name The name of the program.
 * @return 1 if the GNU flags are valid, 0 otherwise.
 */
int check_GNU_flags(flags_t *flags, char *str_with_flags, char *prog_name) {
    int ret_val = 1;
    if (strcmp(str_with_flags, "--number-nonblank") == 0) {
        flags->b = 1;
    } else if (strcmp(str_with_flags, "--number") == 0) {
        flags->n = 1;
    } else if (strcmp(str_with_flags, "--squeeze-blank") == 0) {
        flags->s = 1;
    } else {
        printf("%s: illegal option -- %s\n", prog_name, str_with_flags);
        ret_val = 0;
    }
    return ret_val;
}

/**
 * @brief Processes the files and applies the specified flags.
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @param file_index The index of the first file argument.
 * @param flags A pointer to the flags struct.
 */
void go_through_files(int argc, char **argv, int file_index, flags_t *flags) {
    while (file_index < argc) {
        FILE *fp = fopen(argv[file_index], "r+");
        if (!fp) {
            printf("%s: %s: %s\n", argv[0], argv[file_index], strerror(errno));
            file_index++;
            continue;
        }
        output_file(fp, flags);
        fclose(fp);
        file_index++;
    }
}

/**
 * @brief Outputs the contents of a file with the specified flags applied.
 * @param fp A pointer to the file to be processed.
 * @param flags A pointer to the flags struct.
 */
void output_file(FILE *fp, flags_t *flags) {
    int ch, new_line = 1;
    unsigned line_counter = 0, was_new_line = 0;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch != '\n')
            was_new_line = 0;
        if (flags->n && new_line) {
            line_counter++;
            printf("%6u\t", line_counter);
            new_line = 0;
        } else if (flags->b && new_line && ch != '\n') {
            line_counter++;
            printf("%6u\t", line_counter);
            new_line = 0;
        }
        if (flags->e && ch == '\n' && (was_new_line <= 1 || !flags->s))
            putchar('$');
        if (flags->s && was_new_line >= 2 && ch == '\n')
            continue;
        if (flags->t && ch == '\t') {
            putchar('^');
            putchar('I');
            continue;
        }
        if (flags->v && ((ch >= 0 && ch <= 31) || (ch >= 127 && ch <= 159))
            && ch != 10 && ch != 9) {
            if (ch >= 0 && ch <= 31) {
                ch += 64;
                printf("^%c", ch);
            } else if (ch >= 127 && ch <= 255) {
                ch -= 64;
                ch == '?' ? printf("^%c", ch) : printf("M-^%c", ch);
            }
            continue;
        }
        putchar(ch);
        if (ch == '\n') {
            new_line = 1;
            was_new_line++;
        }
    }
}