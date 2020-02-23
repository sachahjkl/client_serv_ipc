#ifndef PROBA_CHAR_H
#define PROBA_CHAR_H

#define PC_FILE "file"
#define PC_TEXT "text"
#define PC_KEY_NAME "char"
#define PC_DICT_NAME "proba"

#define PC_USAGE            \
  "Arguments incorrects.\n" \
  "utilisation: proba-char MODE SRC[...]"

char *pc_calcul(char *__dest, const int argc, const char *argv[]);

int pc_check(const int argc, const char *argv[]);

char *pc_modes(char *__dest);

#endif