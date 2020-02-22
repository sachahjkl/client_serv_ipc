#ifndef COMPTEUR_CHAR_H
#define COMPTEUR_CHAR_H

#define CC_MAX_RES_STR 511
#define CC_FILE "file"
#define CC_TEXT "text"
#define CC_COL_KEY_NAME "char"
#define CC_COL_VAL_NAME "compte"

#define CC_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: compteur-char MODE SRC[...]"

char *cc_calcul(char *__dest, const int argc, const char *argv[]);

int cc_check(const int argc, const char *argv[]);

char *cc_modes(char *__dest);

#endif