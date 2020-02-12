#include "service.h"
#include "../shared/result.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_services();

result start_service(message m) {
  result r;
  printf("%s\n", m.service_name);
  if (strcmp(m.service_name, CALCUL_SIMPLE) == 0) {
  } else if (strcmp(m.service_name, COMPTEUR_MOTS) == 0) {
  } else if (strcmp(m.service_name, PROBA_MOTS) == 0) {
  } else if (strcmp(m.service_name, PROBA_CHAR) == 0) {
  } else if (strcmp(m.service_name, SERVICES) == 0) {
    strcpy(r.value, get_services());
  } else {
    strcpy(r.value, UNKOWN_SERVICE);
    strcpy(r.time_spent, "NULL");
    r.ram_used = 0.0f;
  }
  return r;
}

char *get_services() {
  int nb_services = sizeof(services) / sizeof(char *);
  char *services_str = malloc(sizeof(char) * (MAX_VALUE_LENGTH + 1));
  for (int i = 0; i < nb_services - 1; i++) {
    sprintf(services_str + strlen(services_str), "%s ", services[i]);
  }
  sprintf(services_str + strlen(services_str), "%s", services[nb_services - 1]);
  return services_str;
}
