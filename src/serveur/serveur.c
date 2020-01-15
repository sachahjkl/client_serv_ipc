#include "serveur.h"
#include "../shared/message.h"
#include "../shared/mq.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

int main(int argc, char *argcv[]) { return start(); }

int start() {
  int msgid = init_MQ();
  printf("%d\n", msgid);
  if (msgid > -1) {
    return process_connections(msgid);
  } else {
    return EXIT_FAILURE;
  }
}

int process_connections(int msgid) {

  while (1) {
    mq_buffer buffer;
    puts("listening...");
    msgrcv(msgid, &buffer, sizeof(buffer), 1, 0);
    msgctl(msgid, IPC_RMID, NULL);
    printf("data received: %s\n", buffer.mtext);
    message m = deserialize(buffer.mtext);
    printf("%s", m.service_name);
    break;
  }
  return EXIT_SUCCESS;
}
