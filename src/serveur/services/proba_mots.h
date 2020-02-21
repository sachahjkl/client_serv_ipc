#ifndef PROBA_MOTS_H
#define PROBA_MOTS_H

#define PM_MAX_RES_STR 511

#define PM_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: proba-mots OPERATION [NOMBRES]..."

char *pm_calcul(char *__dest, const int argc, const char *argv[]);

int pm_check(const int argc, const char *argv[]);

#endif