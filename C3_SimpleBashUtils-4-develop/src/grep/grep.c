#include "grep.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf(
        "Usage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for "
        "more information.\n");
    return 0;
  }

  char *search_pattern = NULL;
  if (count_files(argc, argv) > 1 && !show_file_names_only) {
    should_print_file_name = 1;
  }

  process_options(argc, argv);

  if (!is_pattern_file_flag_set) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
        FILE *file = fopen(argv[i], "r");
        if (file) {
          fclose(file);
          if (patterns_for_flag_e > 0) {
            process_file_with_flag_e(argv[i], argc, argv);
          } else {
            process_file(argv[i], search_pattern);
          }
        } else if (search_pattern == NULL) {
          search_pattern = argv[i];
        }
      }
    }
  }

  return 0;
}

int process_options(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-i") == 0) {
      ignore_case = 1;
    } else if (strcmp(argv[i], "-v") == 0) {
      invert_match = 1;
    } else if (strcmp(argv[i], "-c") == 0) {
      show_count_only = 1;
    } else if (strcmp(argv[i], "-l") == 0) {
      show_matching_lines = 0;
      show_file_names_only = 1;
    } else if (strcmp(argv[i], "-n") == 0) {
      show_line_numbers = 1;
    } else if (strcmp(argv[i], "-h") == 0) {
      suppress_file_names = 1;
      should_print_file_name = 0;
    } else if (strcmp(argv[i], "-s") == 0) {
    } else if (strcmp(argv[i], "-o") == 0) {
      show_only_matches = 1;
    } else if (strcmp(argv[i], "-f") == 0) {
      if (i + 1 < argc) {
        int pattern_file_index = i + 1;
        is_pattern_file_flag_set = 1;
        handle_pattern_file(pattern_file_index, argc, argv);
        i++;
      } else {
        exit(EXIT_FAILURE);
      }
    } else if (strcmp(argv[i], "-e") == 0) {
      if (i + 1 < argc) {
        patterns_for_flag_e++;
        i++;
      } else {
        exit(EXIT_FAILURE);
      }
    }
  }
  return 0;
}

void handle_pattern_file(int pattern_file_index, int argc, char *argv[]) {
  char pattern_buffer[MAX_ARRAY_SIZE];
  FILE *pattern_file = fopen(argv[pattern_file_index], "r");
  if (pattern_file) {
    while (fgets(pattern_buffer, sizeof(pattern_buffer), pattern_file)) {
      pattern_buffer[strcspn(pattern_buffer, "\n")] = 0;
      for (int i = pattern_file_index + 1; i < argc; i++) {
        if (argv[i][0] != '-') {
          FILE *data_file = fopen(argv[i], "r");
          if (data_file) {
            fclose(data_file);
            process_file(argv[i], pattern_buffer);
          }
        }
      }
    }
    fclose(pattern_file);
  } else {
    printf("grep: %s: No such file or directory\n", argv[pattern_file_index]);
  }
}

void process_file(const char *filename, const char *pattern) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  char line_buffer[MAX_ARRAY_SIZE];
  int current_line_number = 0;

  while (fgets(line_buffer, MAX_ARRAY_SIZE, file)) {
    current_line_number++;
    process_line(filename, current_line_number, line_buffer, pattern);
  }

  if (show_count_only) {
    if (should_print_file_name) {
      printf("%s:", filename);
    }
    printf("%d\n", count_matches_only);
    count_matches_only = 0;
  }

  fclose(file);
}

void process_file_with_flag_e(const char *filename, int argc, char *argv[]) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    return;
  }

  char line_buffer[MAX_ARRAY_SIZE];
  int current_line_number = 0;
  const char *patterns[MAX_PATTERNS];
  int pattern_count = 0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
      if (pattern_count < MAX_PATTERNS) {
        patterns[pattern_count++] = argv[i + 1];
        i++;
      } else {
        fprintf(stderr, "Exceeded maximum number of patterns.\n");
      }
    }
  }

  while (fgets(line_buffer, MAX_ARRAY_SIZE, file)) {
    current_line_number++;
    for (int j = 0; j < pattern_count; j++) {
      process_line(filename, current_line_number, line_buffer, patterns[j]);
    }
  }

  fclose(file);
}

void process_line(const char *filename, int line_number, char *line,
                  const char *pattern) {
  if (pattern == NULL) {
    return;
  }

  char line_copy[MAX_ARRAY_SIZE];
  char pattern_copy[MAX_ARRAY_SIZE];

  strcpy(line_copy, line);
  strcpy(pattern_copy, pattern);

  if (ignore_case) {
    for (int i = 0; pattern_copy[i]; i++) {
      pattern_copy[i] = tolower(pattern_copy[i]);
    }
    for (int j = 0; line_copy[j]; j++) {
      line_copy[j] = tolower(line_copy[j]);
    }
  }

  if (does_match(line_copy, pattern_copy) ^ invert_match) {
    count_matches_only++;
    if (show_file_names_only) {
      if (filename != last_file_name) {
        printf("%s\n", filename);
      }
      last_file_name = (char *)filename;
    }
    if (!show_count_only && show_matching_lines) {
      if (should_print_file_name) {
        printf("%s:", filename);
      }
      if (show_line_numbers) {
        printf("%d:", line_number);
      }
      if (show_only_matches) {
        printf("%s\n", pattern);
      } else {
        printf("%s", line);
      }
    }
  }
}

int does_match(const char *line, const char *pattern) {
  return strstr(line, pattern) != NULL;
}

int count_files(int argc, char *argv[]) {
  int file_count = 0;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0) {
      file_count--;
    }
    if (argv[i][0] != '-') {
      FILE *file = fopen(argv[i], "r");
      if (file) {
        file_count++;
        fclose(file);
      }
    }
  }
  return file_count;
}