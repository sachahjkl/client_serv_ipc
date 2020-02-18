#include "message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *m_serialize(message m) {
  char *str = malloc(MAX_SERIALIZED_LENGTH + 1);
  sprintf(str, "%s%s", m.service_name, SEPARATOR);
  if (m.argc != 0) {
    for (int i = 0; i < m.argc - 1; i++) {
      sprintf(str + strlen(str), "%s%s", m.argv[i], SEPARATOR);
    }
    strcat(str, m.argv[m.argc - 1]);
  }
  return str;
}

message m_deserialize(char *string) {
  message m;
  char *tok = strtok(string, SEPARATOR);
  int i = 0;
  if (tok == NULL) {
    exit(EXIT_FAILURE);
  }
  strcpy(m.service_name, tok);

  char **args = malloc(sizeof(char *) * MAX_ARGS);
  tok = strtok(NULL, SEPARATOR);
  while (tok != NULL && i < MAX_ARGS) {
    args[i++] = tok;
    tok = strtok(NULL, SEPARATOR);
  }

  args = realloc(args, sizeof(char *) * i);
  m.argv = args;
  m.argc = i;
  return m;
}