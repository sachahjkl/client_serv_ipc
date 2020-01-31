#include "client.h"
#include "../shared/message.h"
#include "../shared/mq.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(int argc, char *argv[]) {
  // on retire le premier argument de la liste
  // en utilisant de l'arithetique de pointeurs
  return send(argc - 1, argv + 1);
}

int send(int argc, char *argv[]) {
  if (!check(argc, argv)) {
    exit(EXIT_FAILURE);
  }
  message m;
  m.argc = argc;
  m.argv = argv;
  char **pipes = get_named_pipe();

  int fd_write = open(pipes[0], O_WRONLY);
  int fd_read = open(pipes[1], O_RDONLY);

  return EXIT_SUCCESS;
}

int check(int argc, char *argv[]) {
  int res = 1;
  // ici on vérifie que les arguments passés sont suffisants et corrects
  // -> qu'ils satisfont certaines conditions
  res = argc > 0 ? res : 0;
  return res;
}

// retournera toujours un tableau comportant les deux noms
// des named pipes auxquelles se connecter
char **get_named_pipe() {
  mq_buffer buffer;
  const int nb_pipes = 2;
  char **pipes = malloc(sizeof(char *) * nb_pipes);
  buffer.mtype = TYPE_CLIENT;
  char named_pipe[MAX_INSTR_LENGTH];

  strcpy(named_pipe, "");
  strcpy(buffer.mtext, CONNECT_REQUEST_CODE);

  int msgid = init_MQ();
  msgsnd(msgid, &buffer, sizeof(buffer.mtext), 1);
  if (msgrcv(msgid, &buffer, sizeof(buffer.mtext), TYPE_SERVEUR, 0) > 0) {
    pipes[0] = strtok(buffer.mtext, SEPARATOR);
    pipes[1] = strtok(NULL, SEPARATOR);
  }
  return pipes;
}