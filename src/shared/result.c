#include "result.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *r_serialize(result r) {

  char *str = malloc(MAX_VALUE_LENGTH * 2 + FLOAT_SIZE + 1);
  sprintf(str, "%s%s%s%s%3.2f", r.value, SEPARATOR, r.time_spent, SEPARATOR,
          r.ram_used);
  return str;
}

result r_deserialize(char *string) {
  result r;
  char *tok = strtok(string, SEPARATOR);
  if (tok == NULL) {
    exit(EXIT_FAILURE);
  }
  strcpy(r.value, tok);
  tok = strtok(NULL, SEPARATOR);
  strcpy(r.time_spent, tok);
  tok = strtok(NULL, SEPARATOR);
  r.ram_used = atof(tok);

  return r;
}