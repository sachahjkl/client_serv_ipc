#include "../shared/message.h"
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[]) {

  key_t key;
  int msgid;
  message message;
  // ftok to generate unique key
  key = ftok("progfile", 65);

  // msgget creates a message queue
  // and returns identifier
  msgid = msgget(key, 0666 | IPC_CREAT);

  // msgrcv to receive message
  msgrcv(msgid, &message, sizeof(message), 1, 0);

  // display the message
  printf("Data Received is : %s \n", message.service_name);

  // to destroy the message queue
  msgctl(msgid, IPC_RMID, NULL);

  return 0;
}
