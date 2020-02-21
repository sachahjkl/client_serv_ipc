#ifndef CLIENT_H
#define CLIENT_H
#include "../shared/result.h"

#define NB_PIPES 2

int send(int argc, char *argv[]);
int check(int argc, char *argv[]);
char **get_named_pipes(char **__dest);
void display_results(result *r);

#endif