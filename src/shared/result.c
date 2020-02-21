#include "result.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *r_serialize(char *__dest, const result_t __src) {
  sprintf(__dest, "%s%s%s%s%ld", __src->value, R_SEPARATOR, __src->time_spent,
          R_SEPARATOR, __src->ram_used);
  return __dest;
}

result_t r_deserialize(result_t __dest, const char *__src) {
  char *dup = calloc(strlen(__src) + 1, sizeof(char));
  if (dup != NULL) strcpy(dup, __src);
  char *tok = strtok(dup, R_SEPARATOR);
  if (tok == NULL) {
    exit(EXIT_FAILURE);
  }
  strncpy(__dest->value, tok, R_MAX_VALUE + 1);
  tok = strtok(NULL, R_SEPARATOR);
  strncpy(__dest->time_spent, tok, R_MAX_TIME_SPENT + 1);
  tok = strtok(NULL, R_SEPARATOR);
  __dest->ram_used = atol(tok);
  free(dup);
  return __dest;
}

result_t result_new(void) {
  result proto = {calloc(R_MAX_VALUE + 1, sizeof(char)),
                  calloc(R_MAX_TIME_SPENT + 1, sizeof(char)), 0};
  result_t r = malloc(sizeof(result));
  *r = proto;
  return r;
}

void result_free(result_t r) {
  free(r->time_spent);
  free(r->value);
}
