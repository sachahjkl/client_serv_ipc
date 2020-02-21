#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int largest_value = 0;
int largest_key = 0;

void dict_update_widths(const char *key, double value);
/* ajout manuel de la fonction strdup() car seulement dispo sur les impl POSIX
du C */
char *strdup(const char *c) {
  char *dup = calloc(strlen(c) + 1, sizeof(char));
  if (dup != NULL) strcpy(dup, c);
  return dup;
}

int dict_find_index(dictionary_t dict, const char *key) {
  for (int i = 0; i < dict->length; i++) {
    if (strcmp(dict->entries[i].key, key) == 0) {
      return i;
    }
  }
  return D_INDEX_NOT_FOUND;
}

double dict_find(dictionary_t dict, const char *key, double def) {
  int i = dict_find_index(dict, key);
  return i == D_INDEX_NOT_FOUND ? def : dict->entries[i].value;
}

void dict_add(dictionary_t dict, const char *key, double value) {
  int i = dict_find_index(dict, key);
  if (i != D_INDEX_NOT_FOUND) {
    dict->entries[i].value = value;
    dict_update_widths(key, value);
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
  dict_update_widths(key, value);
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

char *dict_str(char *__dest, dictionary_t dict) {
  // sprintf(buf, "%.2lf", value);
  printf(" largest_value : %d", largest_value);
  printf(" largest_key : %d", largest_key);
  return __dest;
}

void dict_update_widths(const char *key, double value) {
  char buf[D_MAX_DOUBLE_STR + 1];
  sprintf(buf, "%.2lf", value);

  int key_width = strlen(key);
  int value_width = strlen(buf);

  // printf("keyw : %d, valw : %d\n", key_width, value_width);
  if (largest_key < key_width) {
    largest_key = key_width;
  }

  if (largest_value < value_width) {
    largest_value = value_width;
  }
}