#ifndef COMPTEUR_MOTS_H
#define COMPTEUR_MOTS_H

#define CM_MAX_RES_STR 511

#define CM_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: compteur-mots OPERATION [NOMBRES]..."

char *cm_calcul(int argc, char *argv[]);
int cm_check(int argc, char *argv[]);

#endif