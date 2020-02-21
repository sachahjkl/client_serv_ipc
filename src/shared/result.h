#ifndef RESULT_H
#define RESULT_H

#define R_MAX_VALUE 1023
#define R_MAX_TIME_SPENT 1023
#define R_SEPARATOR "|"
typedef struct result {
  char *value;
  char *time_spent;
  long ram_used;  // en kilo-octets
} result, *result_t;

char *r_serialize(char *__dest, const result_t __src);

result_t r_deserialize(result_t __dest, const char *__src);

result_t result_new(void);

void result_free(result_t r);

#endif