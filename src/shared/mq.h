#ifndef MQ_H
#define MQ_Q
#include <sys/msg.h>

#define MQ_DIR "/tmp"
#define MQ_FILENAME "serveur.mq"
#define MQ_PATHNAME MQ_DIR "/" MQ_FILENAME
#define MQ_PROJ_ID 125
#define MQ_TYPE_CLIENT 7002
#define MQ_TYPE_SERVEUR 2007
#define MQ_RIGHTS 0666 | IPC_CREAT
#define MQ_CONNECT_REQUEST_CODE "[CONNECT_REQUEST_FROM_CLIENT]"
#define MQ_MAX_TEXT 63
#define MQ_PIPES_LENGTH 40

typedef struct mq_buffer {
  long mtype;
  char mtext[MQ_MAX_TEXT + 1];
} mq_buffer;

int init_MQ(void);

#endif