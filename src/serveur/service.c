#include "service.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "../shared/result.h"
#include "services/calcul_simple.h"
#include "services/compteur_char.h"
#include "services/compteur_mots.h"
#include "services/proba_char.h"
#include "services/proba_mots.h"

const char *services[] = {SE_CALCUL_SIMPLE, SE_COMPTEUR_MOTS, SE_COMPTEUR_CHAR,
                          SE_PROBA_MOTS,    SE_PROBA_CHAR,    SE_SERVICES};

result_t start_service(result_t __dest, const message_t __src) {
  time_t start = clock();
  if (strcmp(__src->service_name, SE_CALCUL_SIMPLE) == 0) {
    cs_calcul(__dest->value, __src->argc, (const char **)__src->argv);
  } else if (strcmp(__src->service_name, SE_COMPTEUR_MOTS) == 0) {
    not_implemented(__dest->value);
  } else if (strcmp(__src->service_name, SE_COMPTEUR_CHAR) == 0) {
    cc_calcul(__dest->value, __src->argc, (const char **)__src->argv);
  } else if (strcmp(__src->service_name, SE_PROBA_MOTS) == 0) {
    not_implemented(__dest->value);
  } else if (strcmp(__src->service_name, SE_PROBA_CHAR) == 0) {
    not_implemented(__dest->value);
  } else if (strcmp(__src->service_name, SE_SERVICES) == 0) {
    get_services(__dest->value);
  } else {
    unknown_service(__dest->value);
  }

  time_t end = clock();
  double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
  sprintf(__dest->time_spent, "%3.3lfms", time_spent);
  __dest->ram_used = get_memory(getpid());
  return __dest;
}

char *unknown_service(char *__dest) {
  strcpy(__dest, SE_UNKOWN_SERVICE);
  return __dest;
}

char *not_implemented(char *__dest) {
  strcpy(__dest, SE_NOT_IMPLEMENTED);
  return __dest;
}

char *get_services(char *__dest) {
  const char S_M_SEPARATOR = ' ';
  int nb_services = sizeof(services) / sizeof(char *);
  for (int i = 0; i < nb_services - 1; i++) {
    sprintf(__dest + strlen(__dest), "%s%c", services[i], S_M_SEPARATOR);
  }
  sprintf(__dest + strlen(__dest), "%s", services[nb_services - 1]);
  return __dest;
}

long get_memory(pid_t pid) {
  const int MEM_SIZE_POS = 23;
  char filename[FILENAME_MAX_LENGTH + 1];
  char line[M_MAX_SERIALIZED + 1];
  char *value;
  FILE *stat;

  long mem_size = 0;
  sprintf(filename, PROC_FILE, pid);

  stat = fopen(filename, "r");
  fgets(line, sizeof(line), stat);
  value = strtok(line, " ");
  for (int i = 0; i < MEM_SIZE_POS - 1 && value != NULL; i++) {
    value = strtok(NULL, " ");
  }
  mem_size = atoll(value);
  return mem_size;
}