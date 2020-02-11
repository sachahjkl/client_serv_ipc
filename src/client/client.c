#include "client.h"
#include "../shared/log.h"
#include "../shared/message.h"
#include "../shared/mq.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // on retire le premier argument de la liste
  // en utilisant de l'arithmetique des pointeurs
  return send(argc - 1, argv + 1);
}

int send(int argc, char *argv[]) {
  if (check(argc, argv) != EXIT_SUCCESS) {
    log_error("Arguments saisis insatisfaisants", NULL);
    exit(EXIT_FAILURE);
  }
  message m;
  m.argc = argc;
  m.argv = argv;
  char buffer[MAX_SERIALIZED_LENGTH + 1];
  char **pipes = get_named_pipe();

  log_info("pipes : |%s| |%s|", pipes[0], pipes[1]);
  errno = 0;
  int fd_write = open(pipes[0], O_WRONLY);
  int fd_read = open(pipes[1], O_RDONLY);
  if (errno != 0) {
    log_error("Erreur à l'ouverture des fifos : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  strcpy(buffer, serialize(m));
  write(fd_write, buffer, sizeof(buffer));
  read(fd_read, buffer, sizeof(buffer));
  puts(buffer);

  // free(pipes);
  close(fd_read);
  close(fd_write);
  return EXIT_SUCCESS;
}

// retournera toujours un tableau comportant les deux noms
// des named pipes auxquels se connecter
char **get_named_pipe() {
  const int NB_PIPES = 2;
  int msgid = init_MQ();
  mq_buffer buffer;

  char **pipes = malloc(sizeof(char *) * NB_PIPES);
  pipes[0] = malloc(sizeof(char) * MAX_INSTR_LENGTH + 1);
  pipes[1] = malloc(sizeof(char) * MAX_INSTR_LENGTH + 1);
  // vérifier si le malloc a fonctionné !

  buffer.mtype = TYPE_CLIENT;
  strcpy(buffer.mtext, CONNECT_REQUEST_CODE);

  errno = 0;
  msgsnd(msgid, &buffer, sizeof(buffer.mtext), 1);
  msgrcv(msgid, &buffer, sizeof(buffer.mtext), TYPE_SERVEUR, 0);
  if (errno != 0) {
    log_error("Erreur réception des tubes nommés : %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  strcpy(pipes[0], strtok(buffer.mtext, SEPARATOR));
  strcpy(pipes[1], strtok(NULL, SEPARATOR));
  return pipes;
}

int check(int argc, char *argv[]) {
  int res = EXIT_SUCCESS;
  // ici on vérifie que les arguments passés sont suffisants et corrects
  // -> qu'ils satisfont certaines conditions
  res = argc > 0 ? res : EXIT_FAILURE;
  return res;
}