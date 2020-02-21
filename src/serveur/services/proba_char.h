#ifndef PROBA_CHAR_H
#define PROBA_CHAR_H

#define PC_MAX_RES_STR 511

#define PC_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: proba-char OPERATION [NOMBRES]..."

char *pc_calcul(char *__dest, const int argc, const char *argv[]);

int pc_check(const int argc, const char *argv[]);

#endif