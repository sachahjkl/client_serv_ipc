#include "message.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * __dest doit avoir une taille sup. ou égale à (M_MAX_SERIALIZED + 1) *
 * 3
 */
char *m_serialize(char *__dest, const message_t __src) {
  sprintf(__dest, "%s%s", __src->service_name, M_SEPARATOR);
  if (__src->argc != 0) {
    for (int i = 0; i < __src->argc - 1; i++) {
      sprintf(__dest + strlen(__dest), "%s%s", __src->argv[i], M_SEPARATOR);
    }
    strcat(__dest, __src->argv[__src->argc - 1]);
  }
  return __dest;
}

/*
 * La taille de __dest->argv doit être sup. ou égale à sizeof(char) * M_MAX_ARGS
 */
message_t m_deserialize(message_t __dest, const char *__src) {
  char *dup = calloc(strlen(__src) + 1, sizeof(char));
  if (dup != NULL) strcpy(dup, __src);

  char *tok = strtok(dup, M_SEPARATOR);
  int i = 0;
  if (tok == NULL) {
    exit(EXIT_FAILURE);
  }
  strcpy(__dest->service_name, tok);

  tok = strtok(NULL, M_SEPARATOR);
  while (tok != NULL && i < M_MAX_ARGS) {
    __dest->argv[i] = calloc(strlen(tok) + 1, sizeof(char));
    strcpy(__dest->argv[i++], tok);
    tok = strtok(NULL, M_SEPARATOR);
  }

  __dest->argv = realloc(__dest->argv, sizeof(char *) * i);
  __dest->argc = i;
  free(dup);
  return __dest;
}

message_t message_new(void) {
  message proto = {calloc(M_MAX_SERVICE_NAME + 1, sizeof(char)),
                   calloc(M_MAX_ARGS + 1, sizeof(char *)), 0};
  message_t m = malloc(sizeof(message));
  *m = proto;
  return m;
}

void message_free(message_t m) {
  for (int i = 0; i < m->argc; i++) {
    free(m->argv[i]);
  }
  free(m->argv);
  free(m->service_name);
}