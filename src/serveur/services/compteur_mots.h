#ifndef COMPTEUR_MOTS_H
#define COMPTEUR_MOTS_H

#define CM_FILE "file"
#define CM_TEXT "text"
#define CM_COL_KEY_NAME "mots"
#define CM_COL_VAL_NAME "compte"
#define CM_MAX_LINE_LENGTH 4096

#define CM_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: compteur-mots MODE SRC[...]"

char *cm_calcul(char *__dest, const int argc, const char *argv[]);

int cm_check(const int argc, const char *argv[]);

char *cm_modes(char *__dest);

#endif