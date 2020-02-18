#ifndef RESULT_H
#define RESULT_H

#define MAX_VALUE_LENGTH 1023
#define TIME_SPENT_LENGTH 255
#define FLOAT_SIZE 5
#define SEPARATOR "|"
typedef struct result {
  char value[MAX_VALUE_LENGTH + 1];
  char time_spent[TIME_SPENT_LENGTH + 1];
  long ram_used;  // en kilo-octets
} result;

char *r_serialize(result r);

result r_deserialize(char *string);

#endif