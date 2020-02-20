#include "calcul_simple.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// faire GAFFE A LA DIV PAR 0
char *cs_calcul(int argc, char *argv[]) {
  double res = 0;
  char *res_str = malloc(sizeof(char) * CS_MAX_RES_STR + 1);
  if (cs_check(argc, argv) != EXIT_SUCCESS) {
    sprintf(res_str, "%s\n%s", CS_USAGE, cs_methodes());
    return res_str;
  }
  if (strcmp(argv[0], ADDITION) == 0) {
    for (int i = 1; i < argc; i++) {
      res += atof(argv[i]);
    }
  } else if (strcmp(argv[0], SOUSTRACTION) == 0) {
    for (int i = 1; i < argc; i++) {
      res -= atof(argv[i]);
    }
  } else if (strcmp(argv[0], MULTIPLICATION) == 0) {
    res = 1;
    for (int i = 1; i < argc; i++) {
      res *= atof(argv[i]);
    }
  } else if (strcmp(argv[0], DIVISION) == 0) {
    if (argc >= 2) {
      double tmp = 0;
      res = atof(argv[1]);
      for (int i = 2; i < argc; i++) {
        tmp = atof(argv[i]);
        if (tmp != 0) res = (double)res / tmp;
      }
    }
  } else {
    sprintf(res_str, "%s\n%s", CS_USAGE, cs_methodes());
    return res_str;
  }
  sprintf(res_str, "%.3lf", res);
  return res_str;
}

int cs_check(int argc, char *argv[]) {
  const int MIN_ARGS = 1;
  int res = EXIT_SUCCESS;

  res = argc >= MIN_ARGS ? res : EXIT_FAILURE;
  return res;
}

char *cs_methodes() {
  char *res_str = malloc(sizeof(char) * CS_MAX_RES_STR + 1);
  sprintf(res_str, "opérations possibles: %s %s %s %s", ADDITION, SOUSTRACTION,
          MULTIPLICATION, DIVISION);
  return res_str;
}

// Inch ajouter le retour des différents types de calculs possibles
