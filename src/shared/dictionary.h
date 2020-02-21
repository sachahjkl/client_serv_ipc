#ifndef DICTIONARY_H
#define DICTIONARY_H

#define D_INDEX_NOT_FOUND -1
#define D_MAX_DOUBLE_STR 32

extern int largest_value;
extern int largest_key;

typedef struct dictionary_entry {
  char *key;
  double value;
} dictionary_entry;

typedef struct dictionary {
  int length;
  int capacity;
  dictionary_entry *entries;
} dictionary, *dictionary_t;

int dict_find_index(dictionary_t dict, const char *key);

double dict_find(dictionary_t dict, const char *key, double def);

void dict_add(dictionary_t dict, const char *key, double value);

dictionary_t dict_new(void);

void dict_free(dictionary_t dict);

char *dict_str(char *__dest, dictionary_t dict);

#endif