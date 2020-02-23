#ifndef PROBA_MOTS_H
#define PROBA_MOTS_H

#define PM_SERVICE_NAME "proba-mots"

#define PM_FILE "file"
#define PM_TEXT "text"
#define PM_KEY_NAME "mot"
#define PM_DICT_NAME "proba"

#define PM_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: proba-mots MODE SRC[...]"

char *pm_calcul(char *__dest, const int argc, const char *argv[]);

int pm_check(const int argc, const char *argv[]);

char *pm_modes(char *__dest);

#endif