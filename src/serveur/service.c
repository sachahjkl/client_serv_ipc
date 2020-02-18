#include "service.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../shared/result.h"

char *unknown_service();
char *get_services();

result start_service(message m) {
  result r;
  char *value;
  time_t start = clock();
  if (strcmp(m.service_name, CALCUL_SIMPLE) == 0) {
  } else if (strcmp(m.service_name, COMPTEUR_MOTS) == 0) {
  } else if (strcmp(m.service_name, PROBA_MOTS) == 0) {
  } else if (strcmp(m.service_name, PROBA_CHAR) == 0) {
  } else if (strcmp(m.service_name, SERVICES) == 0) {
    value = get_services();

  } else {
    value = unknown_service();
  }

  time_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
  sprintf(r.time_spent, "%3.3lfms", time_spent);
  strcpy(r.value, value);
  free(value);
  r.ram_used = get_memory(getpid());
  return r;
}

char *unknown_service() {
  char *value;
  value = malloc(sizeof(char) * MAX_VALUE_LENGTH + 1);
  strcpy(value, UNKOWN_SERVICE);

  return value;
}

char *get_services() {
  char *value;
  int size = sizeof(char) * MAX_VALUE_LENGTH + 1;
  value = malloc(size);

  const char S_SEPARATOR = ' ';
  int nb_services = sizeof(services) / sizeof(char *);
  memset(value, '\0', size);
  for (int i = 0; i < nb_services - 1; i++) {
    sprintf(value + strlen(value), "%s%c", services[i], S_SEPARATOR);
  }
  sprintf(value + strlen(value), "%s", services[nb_services - 1]);

  return value;
}

long long int get_memory(pid_t pid) {
  const int mem_size_pos = 23;
  char filename[FILENAME_MAX_LENGTH + 1];
  char line[MAX_SERIALIZED_LENGTH + 1];
  char *value;
  FILE *stat;

  long long int mem_size = 0;
  sprintf(filename, PROC_FILE, pid);

  stat = fopen(filename, "r");
  fgets(line, sizeof(line), stat);
  value = strtok(line, " ");
  for (int i = 0; i < mem_size_pos - 1 && value != NULL; i++) {
    value = strtok(NULL, " ");
  }
  printf("-- %s\n", value);
  mem_size = atoll(value);
  return mem_size;
}