#include "service.h"
#include "../shared/result.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

result unknown_service();
result get_services();

result start_service(message m) {
  result r;
  if (strcmp(m.service_name, CALCUL_SIMPLE) == 0) {
  } else if (strcmp(m.service_name, COMPTEUR_MOTS) == 0) {
  } else if (strcmp(m.service_name, PROBA_MOTS) == 0) {
  } else if (strcmp(m.service_name, PROBA_CHAR) == 0) {
  } else if (strcmp(m.service_name, SERVICES) == 0) {
    r = get_services();
  } else {
    r = unknown_service();
  }
  return r;
}

result unknown_service() {
  result r;
  strcpy(r.value, UNKOWN_SERVICE);
  strcpy(r.time_spent, "NULL");
  r.ram_used = 0.0f;
  return r;
}

result get_services() {
  result r;
  const char S_SEPARATOR = ' ';
  int nb_services = sizeof(services) / sizeof(char *);
  memset(r.value, '\0', sizeof(r.value));
  for (int i = 0; i < nb_services - 1; i++) {
    sprintf(r.value + strlen(r.value), "%s%c", services[i], S_SEPARATOR);
  }
  sprintf(r.value + strlen(r.value), "%s", services[nb_services - 1]);
  strcpy(r.time_spent, "NULL");
  r.ram_used = 0.0f;
  return r;
}
