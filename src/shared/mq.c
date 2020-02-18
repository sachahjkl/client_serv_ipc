#include "mq.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>

int init_MQ() {
  fclose(fopen(PATHNAME, "w"));
  key_t key;
  key = ftok(PATHNAME, PROJ_ID);
  return msgget(key, MQ_RIGHTS);
}