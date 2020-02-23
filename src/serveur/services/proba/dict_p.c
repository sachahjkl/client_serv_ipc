#include "dict_p.h"

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *dict_p_local_dict_str(char *__dest, dict_p_entry *entry,
                            const char *__key_col_name,
                            const char *__value_col_name);

void dict_p_update_wv(double value);

int dict_p_find_index(dict_p_t dict_prob, const char *key) {
  for (int i = 0; i < dict_prob->length; i++) {
    if (strcmp(dict_prob->entries[i].key, key) == 0) {
      return i;
    }
  }
  return D_INDEX_NOT_FOUND;
}

dictionary_t dict_p_find(dict_p_t dict_prob, const char *key,
                         dictionary_t def) {
  int i = dict_p_find_index(dict_prob, key);
  return i == D_INDEX_NOT_FOUND ? def : dict_prob->entries[i].dict;
}

void dict_p_add(dict_p_t dict_proba, const char *key, const char *sub_key) {
  int i = dict_p_find_index(dict_proba, key);
  if (i != D_INDEX_NOT_FOUND) {
    dictionary_t dict = dict_proba->entries[i].dict;
    double value = dict_find(dict, sub_key, 0) + 1;
    dict_add(dict, sub_key, value);
    return;
  }
  if (dict_proba->length == dict_proba->capacity) {
    // on agrandi le dico car on a atteint sa capacité capacit maximale
    dict_proba->capacity *= 2;
    dict_proba->entries = realloc(dict_proba->entries,
                                  dict_proba->capacity * sizeof(dict_p_entry));
  }
  dict_proba->entries[dict_proba->length].key = strdup(key);
  dictionary_t dict = dict_new();
  dict_proba->entries[dict_proba->length].dict = dict;
  dict_add(dict, sub_key, 1);
  dict_proba->length++;
}

double dict_p_total(dictionary_t dict, const char *key) {
  double total = 0;
  if (dict != NULL) {
    for (int i = 0; i < dict->length; i++) {
      total += dict->entries[i].value;
    }
  }
  return total;
}

dict_p_t dict_p_new(void) {
  dict_p proto = {0, 10, malloc(10 * sizeof(dict_p_entry))};
  dict_p_t d = malloc(sizeof(dict_p));
  *d = proto;
  return d;
}

void dict_p_free(dict_p_t dict_proba) {
  for (int i = 0; i < dict_proba->length; i++) {
    free(dict_proba->entries[i].key);
    dict_free(dict_proba->entries[i].dict);
  }
  free(dict_proba->entries);
  free(dict_proba);
}

char *dict_p_str(char *__dest, dict_p_t dict_proba, const char *__key_name,
                 const char *__dict_name) {
  const size_t MAX = 65000;
  if (dict_proba->length > 0) {
    for (int i = 0; i < dict_proba->length; i++) {
      sprintf(__dest + strlen(__dest), "%s qu'un %s suive le %s '%s' :\n",
              __dict_name, __key_name, __key_name, dict_proba->entries[i].key);
      dict_p_local_dict_str(__dest, &dict_proba->entries[i], __key_name,
                            __dict_name);
      if (strlen(__dest) > MAX) {
        return __dest;
      }
    }
  } else {
    sprintf(__dest, "Pas assez d'éléments.");
  }
  return __dest;
}

char *dict_p_local_dict_str(char *__dest, dict_p_entry *entry,
                            const char *__key_col_name,
                            const char *__value_col_name) {
  dictionary_t dict = entry->dict;
  if (dict->length != 0) {
    int i = 0;
    double probability = 0;
    double total = dict_p_total(dict, entry->key);
    for (int j = 0; j < dict->length; j++) {
      probability = (double)dict->entries[j].value / total;
      dict_p_update_wv(probability);
    }
    dict_line_str(__dest);
    // header generation
    if (__key_col_name != NULL && __value_col_name != NULL) {
      sprintf(__dest + strlen(__dest), "%s %*s %s %*s %s\n", D_COL_SEPARATOR,
              largest_key, __key_col_name, D_COL_SEPARATOR, largest_value,
              __value_col_name, D_COL_SEPARATOR);
      dict_line_str(__dest);
    }
    // content generation

    for (; i < dict->length; i++) {
      probability = (double)dict->entries[i].value / total;
      sprintf(__dest + strlen(__dest), "%s %*s %s %*g %s\n", D_COL_SEPARATOR,
              largest_key, dict->entries[i].key, D_COL_SEPARATOR, largest_value,
              probability, D_COL_SEPARATOR);
    }

    dict_line_str(__dest);
  }
  return __dest;
}

void dict_p_update_wv(double value) {
  char buf[D_MAX_DOUBLE_STR + 1];
  sprintf(buf, "%g", value);

  int value_width = strlen(buf);

  if (largest_value < value_width) {
    largest_value = value_width;
  }
}