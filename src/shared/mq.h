#ifndef MQ_H
#define MQ_Q
#include <sys/msg.h>

#define DIR "/tmp"
#define FILENAME "serveur.mq"
#define PATHNAME DIR "/" FILENAME
#define PROJ_ID 125
#define TYPE_CLIENT 7002
#define TYPE_SERVEUR 2007
#define MQ_RIGHTS 0666 | IPC_CREAT
#define MAX_TEXT 1023

typedef struct mq_buffer {
  long mtype;
  char mtext[MAX_TEXT + 1];
} mq_buffer;

int init_MQ() {
  key_t key;
  key = ftok(PATHNAME, PROJ_ID);
  return msgget(key, MQ_RIGHTS);
}

#endif