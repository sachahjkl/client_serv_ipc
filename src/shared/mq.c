#include "mq.h"

int init_MQ() {
  key_t key;
  key = ftok(PATHNAME, PROJ_ID);
  return msgget(key, MQ_RIGHTS);
}