#ifndef CALCUL_SIMPLE_H
#define CALCUL_SIMPLE_H

#define CS_SERVICE_NAME "calcul-simple"

#define CS_MAX_RES_STR 125
#define CS_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: calcul-simple OPERATION [NOMBRES]..."

#define CS_ADDITION "+"
#define CS_SOUSTRACTION "-"
#define CS_MULTIPLICATION "*"
#define CS_DIVISION "/"
#define CS_POW "**"

char *cs_calcul(char *__dest, const int argc, const char *argv[]);
int cs_check(const int argc, const char *argv[]);
char *cs_methodes(char *__dest);
#endif