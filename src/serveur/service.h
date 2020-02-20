#ifndef SERVICE_H
#define SERVICE_H
#include <fcntl.h>

#include "../shared/message.h"
#include "../shared/result.h"

#define FILENAME_MAX_LENGTH 20
#define PROC_FILE "/proc/%d/stat"

#define UNKOWN_SERVICE                                                     \
  "Nom de service inconnu. Essayez 'services' pour afficher les services " \
  "disponibles."
#define NOT_IMPLEMENTED "Service pas encore implémenté."

#define CALCUL_SIMPLE "calcul-simple"
#define COMPTEUR_MOTS "compteur-mots"
#define COMPTEUR_CHAR "compteur-char"
#define PROBA_MOTS "proba-mots"
#define PROBA_CHAR "proba-char"
#define SERVICES "services"

result start_service(message m);
char *unknown_service();
char *not_implemented();
char *get_services();
long long int get_memory(pid_t pid);

#endif