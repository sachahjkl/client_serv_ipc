#ifndef COMPTEUR_MOTS_H
#define COMPTEUR_MOTS_H

#define CM_MAX_RES_STR 511

#define CM_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: compteur-mots OPERATION [NOMBRES]..."

char *cm_calcul(char *__dest, const int argc, const char *argv[]);

int cm_check(const int argc, const char *argv[]);
#endif