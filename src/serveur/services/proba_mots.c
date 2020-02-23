#include "proba_mots.h"

#define _GNU_SOURCE
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "proba/dict_p.h"

char *pm_from_file(char *__dest, const int argc, const char *argv[]);
char *pm_from_text(char *__dest, const int argc, const char *argv[]);
dict_p_t pm_process_line(dict_p_t __dest, const char *line);

char *pm_calcul(char *__dest, const int argc, const char *argv[]) {
#define PM_MAX_METHODES 256
  char methodes[PM_MAX_METHODES];
  pm_modes(methodes);
  if (pm_check(argc, argv) != EXIT_SUCCESS) {
    sprintf(__dest, "%s\n%s", PM_USAGE, methodes);
    return __dest;
  }
  largest_key = strlen(PM_KEY_NAME);
  largest_value = strlen(PM_DICT_NAME);

  if (strcmp(argv[0], PM_FILE) == 0) {
    pm_from_file(__dest, argc, argv);
  } else if (strcmp(argv[0], PM_TEXT) == 0) {
    pm_from_text(__dest, argc, argv);
  } else {
    sprintf(__dest, "%s\n%s", PM_USAGE, methodes);
    return __dest;
  }
  return __dest;
}

int pm_check(const int argc, const char *argv[]) {
#define MIN_ARGS 2
  int res = EXIT_SUCCESS;
  res = argc < MIN_ARGS ? EXIT_FAILURE : res;
  return res;
}

char *pm_modes(char *__dest) {
  sprintf(__dest, "modes possibles: %s %s", PM_FILE, PM_TEXT);
  return __dest;
}

char *pm_from_file(char *__dest, const int argc, const char *argv[]) {
  dict_p_t dico = dict_p_new();
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
    pm_process_line(dico, line);
  }
  dict_p_str(__dest, dico, PM_KEY_NAME, PM_DICT_NAME);

  fclose(fp);
  if (line) free(line);
  return __dest;
}
char *pm_from_text(char *__dest, const int argc, const char *argv[]) {
  dict_p_t dico = dict_p_new();

  for (int i = 1; i < argc; i++) {
    pm_process_line(dico, argv[i]);
  }
  dict_p_str(__dest, dico, PM_KEY_NAME, PM_DICT_NAME);

  return __dest;
}

dict_p_t pm_process_line(dict_p_t __dest, const char *line) {
  int line_length = strlen(line);
  if (line_length >= 2) {
    char c1 = ' ';
    char c2 = ' ';
    for (int i = 1; i < line_length; i++) {
      c1 = tolower(line[i - 1]);
      c2 = tolower(line[i]);
      if (!(isspace(c1) || isspace(c2))) {
        char key[] = {c1, '\0'};
        char sub_key[] = {c2, '\0'};

        dict_p_add(__dest, key, sub_key);
      }
    }
  }
  return __dest;
}