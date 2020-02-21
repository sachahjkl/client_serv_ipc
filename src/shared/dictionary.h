#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct dictionary_entry {
  const char *key;
  int value;
} dictionary_entry;

typedef struct dictionary {
  int length;
  int capacity;
  dictionary_entry *entries;
} dictionary, *dictionary_t;

#endif