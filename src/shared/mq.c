#include "mq.h"

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>

int init_MQ(void) {
  fclose(fopen(MQ_PATHNAME, "w"));
  key_t key;
  key = ftok(MQ_PATHNAME, MQ_PROJ_ID);
  return msgget(key, MQ_RIGHTS);
}