#ifndef SERVICE_H
#define SERVICE_H
#include "../shared/message.h"
#include "../shared/result.h"

#define UNKOWN_SERVICE                                                         \
  "Nom de service inconnu. Essayez 'services' pour afficher les services "     \
  "disponibles."

#define CALCUL_SIMPLE "calcul-simple"
#define COMPTEUR_MOTS "compteur-mots"
#define PROBA_MOTS "proba-mots"
#define PROBA_CHAR "proba_char"
#define SERVICES "services"

static const char *services[] = {CALCUL_SIMPLE, COMPTEUR_MOTS, PROBA_MOTS,
                                 PROBA_CHAR, SERVICES};

result start_service(message m);

#endif