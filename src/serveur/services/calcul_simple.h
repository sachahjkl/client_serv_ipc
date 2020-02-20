#ifndef CALCUL_SIMPLE_H
#define CALCUL_SIMPLE_H

#define CS_MAX_RES_STR 125
#define CS_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: calcul-simple OPERATION [NOMBRES]..."

#define ADDITION "+"
#define SOUSTRACTION "-"
#define MULTIPLICATION "*"
#define DIVISION "/"

char *cs_calcul(int argc, char *argv[]);
int cs_check(int argc, char *argv[]);
char *cs_methodes();
#endif