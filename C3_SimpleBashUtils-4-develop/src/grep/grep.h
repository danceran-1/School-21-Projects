#ifndef GREP
#define GREP

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 1024
#define MAX_PATTERNS 100

int suppress_file_names = 0;
int show_only_matches = 0;
int is_pattern_file_flag_set = 0;
int ignore_case = 0;
int invert_match = 0;
int show_count_only = 0;
int count_matches_only = 0;
int should_print_file_name = 0;
int show_file_names_only = 0;
int show_line_numbers = 0;
int show_matching_lines = 1;
int patterns_for_flag_e = 0;
char *last_file_name;

int process_options(int argc, char *argv[]);
int count_files(int argc, char *argv[]);
void handle_pattern_file(int pattern_file_index, int argc, char *argv[]);
void process_file(const char *filename, const char *pattern);
void process_file_with_flag_e(const char *filename, int argc, char *argv[]);
void process_line(const char *filename, int line_number, char *line,
                  const char *pattern);
int does_match(const char *line, const char *pattern);

#endif