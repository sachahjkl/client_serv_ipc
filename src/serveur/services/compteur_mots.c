#include "compteur_mots.h"

#define _GNU_SOURCE
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../../shared/dictionary.h"

char *cm_from_file(char *__dest, const int argc, const char *argv[]);
char *cm_from_text(char *__dest, const int argc, const char *argv[]);
dictionary_t cm_process_line(dictionary_t __dest, const char *line,
                             const ssize_t len);
char *cm_sanitize_str(char *__dest, const ssize_t len);

char *cm_calcul(char *__dest, const int argc, const char *argv[]) {
#define CM_MAX_METHODES 256
  char methodes[CM_MAX_METHODES];
  cm_modes(methodes);
  if (cm_check(argc, argv) != EXIT_SUCCESS) {
    sprintf(__dest, "%s\n%s", CM_USAGE, methodes);
    return __dest;
  }
  largest_key = strlen(CM_COL_KEY_NAME);
  largest_value = strlen(CM_COL_VAL_NAME);

  if (strcmp(argv[0], CM_FILE) == 0) {
    cm_from_file(__dest, argc, argv);
  } else if (strcmp(argv[0], CM_TEXT) == 0) {
    cm_from_text(__dest, argc, argv);
  } else {
    sprintf(__dest, "%s\n%s", CM_USAGE, methodes);
    return __dest;
  }
  return __dest;
}

int cm_check(const int argc, const char *argv[]) {
#define MIN_ARGS 2
  int res = EXIT_SUCCESS;
  res = argc < MIN_ARGS ? EXIT_FAILURE : res;
  return res;
}

char *cm_modes(char *__dest) {
  sprintf(__dest, "modes possibles: %s %s", CM_FILE, CM_TEXT);
  return __dest;
}

char *cm_from_file(char *__dest, const int argc, const char *argv[]) {
  dictionary_t dico = dict_new();
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  const char *filename = argv[1];
  fp = fopen(filename, "r");
  if (fp == NULL) {
    sprintf(__dest, "Le fichier n'a pas pu être ouvert :\n%s\n",
            strerror(errno));
    return __dest;
  }
  while ((read = getline(&line, &len, fp)) != -1) {
    cm_process_line(dico, line, read);
  }
  dict_str(__dest, dico, CM_COL_KEY_NAME, CM_COL_VAL_NAME);
  fclose(fp);
  if (line) free(line);
  return __dest;
}
char *cm_from_text(char *__dest, const int argc, const char *argv[]) {
  dictionary_t dico = dict_new();
  for (int i = 1; i < argc; i++) {
    cm_process_line(dico, argv[i], strlen(argv[i]));
  }
  // sprintf(__dest, "%d -- %d\n", largest_key, largest_value);
  dict_str(__dest, dico, CM_COL_KEY_NAME, CM_COL_VAL_NAME);
  return __dest;
}

dictionary_t cm_process_line(dictionary_t __dest, const char *line,
                             const ssize_t len) {
  char *buf = calloc(len + 1, sizeof(char));
  snprintf(buf, len + 1, "%s", line);
  cm_sanitize_str(buf, len + 1);
  char *tok = strtok(buf, " \t");
  int i = 0;

  while (tok) {
    double value = dict_find(__dest, tok, 0) + 1;
    dict_add(__dest, tok, value);
    tok = strtok(NULL, " \t");
  }
  return __dest;
}

char *cm_sanitize_str(char *__dest, const ssize_t len) {
  for (int i = 0; i < len; i++) {
    if (ispunct(__dest[i]) || __dest[i] == '\n') {
      __dest[i] = ' ';
    }
    __dest[i] = tolower(__dest[i]);
  }
  return __dest;
}