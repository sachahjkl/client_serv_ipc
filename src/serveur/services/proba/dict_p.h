#ifndef DICT_P_H
#define DICT_P_H

#include "../../../shared/dictionary.h"

typedef struct dict_p_entry {
  char *key;
  dictionary_t dict;
} dict_p_entry;

typedef struct dict_p {
  int length;
  int capacity;
  dict_p_entry *entries;
} dict_p, *dict_p_t;

int dict_p_find_index(dict_p_t dict_proba, const char *key);

dictionary_t dict_p_find(dict_p_t dict_proba, const char *key,
                         dictionary_t def);

void dict_p_add(dict_p_t dict_proba, const char *key, const char *sub_key);

double dict_p_total(dictionary_t dict, const char *key);

dict_p_t dict_p_new(void);

void dict_p_free(dict_p_t dict_p);

char *dict_p_str(char *__dest, dict_p_t dict_proba, const char *__key_name,
                 const char *__dict_name);

#endif