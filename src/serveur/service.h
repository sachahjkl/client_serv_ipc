#ifndef SERVICE_H
#define SERVICE_H
#include <fcntl.h>

#include "../shared/message.h"
#include "../shared/result.h"

#define FILENAME_MAX_LENGTH 20
#define PROC_FILE "/proc/%d/stat"

#define MAX_VALUE_LENGTH 1023

#define SE_UNKOWN_SERVICE                                                  \
  "Nom de service inconnu. Essayez 'services' pour afficher les services " \
  "disponibles."
#define SE_NOT_IMPLEMENTED "Service pas encore implémenté."

#define SE_CALCUL_SIMPLE "calcul-simple"
#define SE_COMPTEUR_MOTS "compteur-mots"
#define SE_COMPTEUR_CHAR "compteur-char"
#define SE_PROBA_MOTS "proba-mots"
#define SE_PROBA_CHAR "proba-char"
#define SE_SERVICES "services"

result_t start_service(result_t __dest, const message_t __src);
char *unknown_service(char *__dest);
char *not_implemented(char *__dest);
char *get_services(char *__dest);
long get_memory(pid_t pid);

#endif