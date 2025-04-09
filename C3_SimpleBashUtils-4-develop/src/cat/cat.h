#ifndef CAT
#define CAT

#include <stdio.h>
#include <string.h>

#define MAX_FILES 1024

void process_files(char *file_paths[], char option);
int parse_arguments(int argc, char *argv[]);

#endif
