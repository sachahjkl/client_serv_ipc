#ifndef SERVEUR_H
#define SERVEUR_H

#define PATHNAME "/tmp/serveur.mq"
#define PROJ_ID 125
#define MQ_RIGHTS 0666 | IPC_CREAT

int start();
int process_connections(int msgid);
int init_MQ();

#endif // !1
