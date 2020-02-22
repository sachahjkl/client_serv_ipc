#include "compteur_char.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../../shared/dictionary.h"

char *cc_from_file(char *__dest, const int argc, const char *argv[]);
char *cc_from_text(char *__dest, const int argc, const char *argv[]);
dictionary_t cc_process_line(dictionary_t __dest, const char *line);

char *cc_calcul(char *__dest, const int argc, const char *argv[]) {
#define CC_MAX_METHODES 256
  char methodes[CC_MAX_METHODES];
  cc_modes(methodes);
  if (cc_check(argc, argv) != EXIT_SUCCESS) {
    sprintf(__dest, "%s\n%s", CC_USAGE, methodes);
    return __dest;
  }
  if (strcmp(argv[0], CC_FILE) == 0) {
    cc_from_file(__dest, argc, argv);
  } else if (strcmp(argv[0], CC_TEXT) == 0) {
    cc_from_text(__dest, argc, argv);
  } else {
    sprintf(__dest, "%s\n%s", CC_USAGE, methodes);
    return __dest;
  }
  return __dest;
}

int cc_check(const int argc, const char *argv[]) {
#define MIN_ARGS 2
  int res = EXIT_SUCCESS;
  res = argc < MIN_ARGS ? EXIT_FAILURE : res;
  return res;
}

char *cc_modes(char *__dest) {
  sprintf(__dest, "modes possibles: %s %s", CC_FILE, CC_TEXT);
  return __dest;
}

char *cc_from_file(char *__dest, const int argc, const char *argv[]) {
  return __dest;
}
char *cc_from_text(char *__dest, const int argc, const char *argv[]) {
  dictionary_t dico = dict_new();
  largest_key = strlen(CC_COL_KEY_NAME);
  largest_value = strlen(CC_COL_VAL_NAME);
  for (int i = 1; i < argc; i++) {
    cc_process_line(dico, argv[i]);
  }
  // sprintf(__dest, "%d -- %d\n", largest_key, largest_value);
  dict_str(__dest, dico, CC_COL_KEY_NAME, CC_COL_VAL_NAME);
  return __dest;
}

dictionary_t cc_process_line(dictionary_t __dest, const char *line) {
  int line_length = strlen(line);
  for (int i = 0; i < line_length; i++) {
    if (isspace(line[i]) == 0) {
      char key[] = {line[i], '\0'};
      double value = dict_find(__dest, key, 0) + 1;

      dict_add(__dest, key, value);
    }
  }
  return __dest;
}