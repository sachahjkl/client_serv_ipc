#include "serveur.h"
#include "../shared/log.h"
#include "../shared/message.h"
#include "../shared/mq.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argcv[]) { return start(); }

int addition(){};

int start() {
  int msgid = init_MQ();
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
    msgrcv(msgid, &buffer, sizeof(buffer.mtext), TYPE_CLIENT, 0);
    if (strcmp(CONNECT_REQUEST_CODE, buffer.mtext) == 0) {
      int id = fork();
      int client_id = client_counter++;
      if (id == 0) {
        handle_connection(msgid, client_id);
      } else if (id < 0) {
        exit(EXIT_FAILURE);
      }
      // TODO réécrire le signal handler pour les SIG_INT/TERM
    }
  }
  return EXIT_SUCCESS;
}

void handle_connection(int msgid, int client_id) {
  mq_buffer buffer;
  buffer.mtype = TYPE_SERVEUR;

  log_info("Traitement connexion n°%d", client_id);

  char pathname_read[MAX_INSTR_LENGTH + 1];
  char pathname_write[MAX_INSTR_LENGTH + 1];
  char pathnames[(MAX_INSTR_LENGTH + 1) * 2];

  sprintf(pathname_read, "%s/read_%d%s", DIR, client_id, NAMED_PIPE_SUFFIX);
  sprintf(pathname_write, "%s/write_%d%s", DIR, client_id, NAMED_PIPE_SUFFIX);
  sprintf(pathnames, "%s%s%s", pathname_read, SEPARATOR, pathname_write);

  strcpy(buffer.mtext, pathnames);
  msgsnd(msgid, &buffer, sizeof(buffer.mtext), 1);

  int fifo_res1 = mkfifo(pathname_read, PERMISSION_FIFO);
  int fifo_res2 = mkfifo(pathname_write, PERMISSION_FIFO);
  if (fifo_res1 != 0 || fifo_res2 != 0) {
    exit(EXIT_FAILURE);
  }
  int fd_read = open(pathname_read, O_RDONLY);
  int fd_write = open(pathname_write, O_WRONLY);

  exit(EXIT_SUCCESS);
}
