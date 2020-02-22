#include "calcul_simple.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// faire GAFFE A LA DIV PAR 0
char *cs_calcul(char *__dest, const int argc, const char *argv[]) {
  double res = 0;
  char methodes[256];
  cs_methodes(methodes);
  if (cs_check(argc, argv) != EXIT_SUCCESS) {
    sprintf(__dest, "%s\n%s", CS_USAGE, methodes);
    return __dest;
  }
  if (strcmp(argv[0], CS_ADDITION) == 0) {
    for (int i = 1; i < argc; i++) {
      res += atof(argv[i]);
    }
  } else if (strcmp(argv[0], CS_SOUSTRACTION) == 0) {
    for (int i = 1; i < argc; i++) {
      res -= atof(argv[i]);
    }
  } else if (strcmp(argv[0], CS_MULTIPLICATION) == 0) {
    res = 1;
    for (int i = 1; i < argc; i++) {
      res *= atof(argv[i]);
    }
  } else if (strcmp(argv[0], CS_DIVISION) == 0) {
    if (argc >= 2) {
      double tmp = 0;
      res = atof(argv[1]);
      for (int i = 2; i < argc; i++) {
        tmp = atof(argv[i]);
        if (tmp != 0) res = (double)res / tmp;
      }
    }
  } else if (strcmp(argv[0], CS_POW) == 0) {
    res = argc >= 2 ? atof(argv[1]) : res;
    if (argc >= 3) {
      double orig = res;
      int pow = atoi(argv[2]);
      printf("---> %d\n", pow);
      if (pow > 0) {
        for (int i = 1; i < pow; i++) {
          res *= orig;
        }
      } else if (pow < 0) {
        for (int i = pow; i < 0; i++) {
          res /= orig;
        }
      } else {
        res = 0;
      }
    }
  } else {
    sprintf(__dest, "%s\n%s", CS_USAGE, methodes);
    return __dest;
  }
  sprintf(__dest, "%g", res);
  return __dest;
}

int cs_check(const int argc, const char *argv[]) {
  const int MIN_ARGS = 1;
  int res = EXIT_SUCCESS;

  res = argc >= MIN_ARGS ? res : EXIT_FAILURE;
  return res;
}

char *cs_methodes(char *__dest) {
  sprintf(__dest, "opérations possibles: %s %s %s %s %s", CS_ADDITION,
          CS_SOUSTRACTION, CS_MULTIPLICATION, CS_DIVISION, CS_POW);
  return __dest;
}

// Inch ajouter le retour des différents types de calculs possibles
