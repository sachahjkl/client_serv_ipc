#ifndef PROBA_MOTS_H
#define PROBA_MOTS_H

#define PM_MAX_RES_STR 511

#define PM_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: proba-mots OPERATION [NOMBRES]..."

char *pm_calcul(int argc, char *argv[]);
int pm_check(int argc, char *argv[]);

#endif