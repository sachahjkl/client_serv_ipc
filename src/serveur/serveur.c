#include "serveur.h"
#include "../shared/message.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argcv[]) { return start(); }

int start() {
  int msgid;
  if ((msgid = init_MQ())) {
    return process_connections(msgid);
  } else {
    return -1;
  }
}

int process_connections(int msgid) {

  while (1) {
    message m;
    puts("listening...");
    // msgrcv(msgid, &m, sizeof(m), );
  }
}

int init_MQ() {
  key_t key;
  key = ftok(PATHNAME, PROJ_ID);
  return msgget(key, MQ_RIGHTS);
}
