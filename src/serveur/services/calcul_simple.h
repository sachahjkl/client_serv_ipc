#ifndef CALCUL_SIMPLE_H
#define CALCUL_SIMPLE_H

#define MAX_RES_STR 125
#define USAGE               \
  "Arguments incorrects.\n" \
  "utilisation: calcul-simple OPERATION [NOMBRES]..."

#define ADDITION "addition"
#define SOUSTRACTION "soustraction"
#define MULTIPLICATION "multiplication"
#define DIVISION "division"

char *calcul_simple(int argc, char *argv[]);
int check(int argc, char *argv[]);
char *methodes_calcul_simple();
#endif