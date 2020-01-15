#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *serialize(message m) {
  char *str = malloc(MAX_SERIALIZED_LENGTH + 1);
  strcat(str, m.service_name);
  strcat(str, SEPARATOR);
  for (int i = 0; i < m.argc - 1; i++) {
    strcat(str, m.argv[i]);
    strcat(str, SEPARATOR);
  }
  strcat(str, m.argv[m.argc - 1]);
  return str;
}
message deserialize(char *string) {
  message m;
  char *tok = strtok(string, SEPARATOR);
  int i = 0;
  char **args = malloc(sizeof(char *) * MAX_ARGS);
  if (tok == NULL) {
    exit(-1);
  }
  strcpy(m.service_name, tok);
  tok = strtok(NULL, SEPARATOR);
  while (tok != NULL && i < MAX_ARGS) {
    args[i++] = tok;
    tok = strtok(NULL, SEPARATOR);
  }
  if (i == 0) {
    exit(-1);
  }
  // TODO : Corriger la taille de argv -> 32 pour l'instant
  m.argv = args;
  m.argc = i;
  return m;
}