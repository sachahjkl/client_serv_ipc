#include "dictionary.h"

#include <stdlib.h>
#include <string.h>

/* ajout manuel de la fonction strdup() car seulement dispo sur les impl POSIX
du C */
char *strdup(const char *c) {
  char *dup = malloc(strlen(c) + 1);
  if (dup != NULL) strcpy(dup, c);
  return dup;
}

int dict_find_index(dictionary_t dict, const char *key) {
  for (int i = 0; i < dict->length; i++) {
    if (!strcmp(dict->entries[i].key, key)) {
      return i;
    }
  }
  return EXIT_FAILURE;
}

int dict_find(dictionary_t dict, const char *key, int def) {
  int i = dict_find_index(dict, key);
  return i == EXIT_FAILURE ? def : dict->entries[i].value;
}

void dict_add(dictionary_t dict, const char *key, int value) {
  int i = dict_find_index(dict, key);
  if (i != EXIT_FAILURE) {
    dict->entries[i].value = value;
    return;
  }
  if (dict->length == dict->capacity) {
    // on agrandi le dico car on a atteint sa capacité capacit maximale
    dict->capacity *= 2;
    dict->entries =
        realloc(dict->entries, dict->capacity * sizeof(dictionary_entry));
  }
  dict->entries[dict->length].key = strdup(key);
  dict->entries[dict->length].value = value;
  dict->length++;
}

dictionary_t dict_new(void) {
  dictionary proto = {0, 10, malloc(10 * sizeof(dictionary_entry))};
  dictionary_t d = malloc(sizeof(dictionary));
  *d = proto;
  return d;
}

void dict_free(dictionary_t dict) {
  for (int i = 0; i < dict->length; i++) {
    free(dict->entries[i].key);
  }
  free(dict->entries);
  free(dict);
}