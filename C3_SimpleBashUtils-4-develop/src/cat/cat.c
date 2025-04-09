#include "cat.h"

int handle_input(int argc, char *argv[]) {
  if (argc > 1) {
    return parse_arguments(argc, argv);
  } else {
    int continue_reading = 1;
    char buffer[MAX_FILES];
    while (continue_reading) {
      scanf("%s", buffer);
      printf("%s\n", buffer);
    }
  }
  return 0;
}

int parse_arguments(int argc, char *argv[]) {
  int index = 1;
  char option = '\0';
  char *file_paths[MAX_FILES];
  int file_count = 0;

  while (index < argc) {
    char *arg = argv[index];
    if (arg[0] == '-' && arg[1] == '-' && arg[2] != '\0') {
      if (strcmp(arg, "--number-nonblank") == 0) {
        option = 'b';
      } else if (strcmp(arg, "--number") == 0) {
        option = 'n';
      } else if (strcmp(arg, "--squeeze-blank") == 0) {
        option = 's';
      }
    } else if (arg[0] == '-' && arg[1] == 'E') {
      option = 'e';
    } else if (arg[0] == '-' && arg[1] != '\0') {
      option = arg[1];
    } else {
      FILE *file;
      if ((file = fopen(arg, "r")) != NULL) {
        fclose(file);
        if (file_count < MAX_FILES) {
          file_paths[file_count] = arg;
          file_count++;
        } else {
          printf("Too many files requested\n");
        }
      } else {
        printf("File not found: %s\n", arg);
      }
    }
    index++;
  }

  if (file_count > 0) {
    file_paths[file_count] = NULL;
    process_files(file_paths, option);
  } else {
    return 0;
  }
  return 1;
}

void process_files(char *file_paths[], char option) {
  char character;
  int line_number = 1;
  int blank_count = 0;

  switch (option) {
    case 'b':
      printf("%6d\t", line_number);
      for (int i = 0; file_paths[i] != NULL; i++) {
        FILE *file = fopen(file_paths[i], "r");
        while ((character = fgetc(file)) != EOF) {
          if (character == '\n') {
            blank_count++;
          } else {
            if (blank_count != 0) {
              for (int j = 0; j < blank_count; j++) {
                printf("\n");
              }
              line_number++;
              printf("%6d\t", line_number);
              printf("%c", character);
              blank_count = 0;
            } else {
              printf("%c", character);
            }
          }
        }
        printf("\n");
        fclose(file);
      }
      break;

    case 'e':
      for (int i = 0; file_paths[i] != NULL; i++) {
        FILE *file = fopen(file_paths[i], "r");
        while ((character = fgetc(file)) != EOF) {
          if (character != '\n') {
            printf("%c", character);
          } else {
            printf("$");
            printf("%c", character);
          }
        }
        fclose(file);
      }
      break;

    case 'n':
      printf("%6d\t", line_number);
      for (int i = 0; file_paths[i] != NULL; i++) {
        FILE *file = fopen(file_paths[i], "r");
        while ((character = fgetc(file)) != EOF) {
          if (character == '\n') {
            blank_count++;
          } else {
            if (blank_count != 0) {
              for (int j = 0; j < blank_count; j++) {
                printf("\n");
                line_number++;
                printf("%6d\t", line_number);
              }
              printf("%c", character);
              blank_count = 0;
            } else {
              printf("%c", character);
            }
          }
        }
        fclose(file);
      }
      printf("\n");
      break;

    case 's':
      for (int i = 0; file_paths[i] != NULL; i++) {
        FILE *file = fopen(file_paths[i], "r");
        while ((character = fgetc(file)) != EOF) {
          if (character != '\n') {
            printf("%c", character);
            blank_count = 0;
          } else {
            if (blank_count != 2) {
              printf("%c", character);
              blank_count++;
            }
          }
        }
        fclose(file);
      }
      break;

    case 't':
      for (int i = 0; file_paths[i] != NULL; i++) {
        FILE *file = fopen(file_paths[i], "r");
        while ((character = fgetc(file)) != EOF) {
          if (character == '\t') {
            printf("^I");
          } else {
            printf("%c", character);
          }
        }
        fclose(file);
      }
      break;

    default:
      for (int i = 0; file_paths[i] != NULL; i++) {
        FILE *file = fopen(file_paths[i], "r");
        while ((character = fgetc(file)) != EOF) {
          printf("%c", character);
        }
        fclose(file);
      }
      break;
  }
}

int main(int argc, char *argv[]) { return handle_input(argc, argv); }
