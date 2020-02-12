#ifndef RESULT_H
#define RESULT_H

#define MAX_VALUE_LENGTH 1023
#define SEPARATOR "|"
typedef struct result
{
  char value[MAX_VALUE_LENGTH + 1];
  char time_spent[MAX_VALUE_LENGTH + 1];
  float ram_used;
} result;

char *r_serialize(result r);

result r_deserialize(char *string);

#endif