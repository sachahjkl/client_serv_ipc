#ifndef SERVEUR_H
#define SERVEUR_H

static int client_counter = 0;

int start();
int process_connections(int msgid);
int handle_connection(int msgid, int client_id);

#endif
