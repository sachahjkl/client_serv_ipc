#include "client.h"
#include "../shared/message.h"
#include "../shared/mq.h"
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[]) {
  // TOREMOVE -- test
  message m;
  strcpy(m.service_name, "calcul_simple");
  char *argvv[] = {"addition", "10", "25"};
  m.argv = argvv;
  m.argc = sizeof(argvv) / sizeof(argvv[0]);
  printf("'%s'\n", serialize(m));
  char *str_m = serialize(m);
  message m1 = deserialize(str_m);
  printf("'%s %s %d'\n", m1.service_name, m1.argv[4], m1.argc);
  // return send();
}

int send() {
  // int msgid = init_MQ();
  // mq_buffer buffer;
  // buffer.mtype = 1;
  // message m;
  // // m.args=args;
  // strcpy(m.service_name, "test_service");
  // char *args[] = {"client", "test", "martin", "grand-frere", "sacha", "s"};
  // strcpy(buffer.mtext, "ceci est un test");
  // msgsnd(msgid, &buffer, sizeof(buffer), 0);
  // printf("message sent: %s\n", buffer.mtext);
  return 0;
}
