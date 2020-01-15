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
  int msgid = init_MQ();
  mq_buffer buffer;
  buffer.mtype = 1;
  message m;
  m.argv = argv;
  strcpy(m.service_name, "test_service");
  char *args[] = {"client", "test", "martin", "grand-frere", "sacha", "siva"};
  m.argv = args;
  strcpy(buffer.mtext, serialize(m));
  msgsnd(msgid, &buffer, sizeof(buffer), 0);
  printf("message sent: %s\n", buffer.mtext);
  return EXIT_SUCCESS;
}

int check(int argc, char *argv[]) { return 1; }