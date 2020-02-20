#ifndef COMPTEUR_CHAR_H
#define COMPTEUR_CHAR_H

#define CC_MAX_RES_STR 511

#define CC_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: compteur-char OPERATION [NOMBRES]..."

char *cc_calcul(int argc, char *argv[]);
int cc_check(int argc, char *argv[]);

#endif