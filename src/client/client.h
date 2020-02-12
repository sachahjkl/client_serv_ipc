#ifndef CLIENT_H
#define CLIENT_H
#include "../shared/result.h"
int send(int argc, char *argv[]);
int check(int argc, char *argv[]);
char **get_named_pipes();
void display_results(result r);

#endif