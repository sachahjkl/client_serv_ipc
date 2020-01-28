#include "client.h"
#include "../shared/message.h"
#include "../shared/mq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[]) { return send(argc, argv); }

int send(int argc, char *argv[]) {
  if (!check(argc, argv)) {
    exit(EXIT_FAILURE);
  }
  get_named_pipe();
  return EXIT_SUCCESS;
}

int check(int argc, char *argv[]) { return 1; }

char *get_named_pipe() {
  mq_buffer buffer;
  buffer.mtype = TYPE_CLIENT;
  char named_pipe[MAX_INSTR_LENGTH];
  strcpy(named_pipe, "");
  strcpy(buffer.mtext, CONNECT_REQUEST_CODE);
  int msgid = init_MQ();
  msgsnd(msgid, &buffer, sizeof(buffer.mtext), 1);
  msgrcv(msgid, &buffer, sizeof(buffer.mtext), TYPE_SERVEUR, 0);
  puts(buffer.mtext);
  return " ";
}