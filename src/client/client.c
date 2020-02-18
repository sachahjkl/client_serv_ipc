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
  // on retire le premier argument de la liste (nom de l'executable)
  // en utilisant de l'arithmetique des pointeurs
  return send(argc - 1, argv + 1);
}

int send(int argc, char *argv[]) {
  if (check(argc, argv) != EXIT_SUCCESS) {
    log_error("Arguments saisis insatisfaisants", NULL);
    exit(EXIT_FAILURE);
  }

  message m;
  strcpy(m.service_name, argv[0]);
  m.argc = argc - 1;
  m.argv = argv + 1;

  char m_buffer[MAX_SERIALIZED_LENGTH + 1];
  char r_buffer[MAX_VALUE_LENGTH * 2 + FLOAT_SIZE + 1];
  char **pipes = get_named_pipes();

  errno = 0;
  int fd_write = open(pipes[0], O_WRONLY);
  int fd_read = open(pipes[1], O_RDONLY);
  if (errno != 0) {
    log_error("Erreur à l'ouverture des fifos : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  strcpy(m_buffer, m_serialize(m));
  write(fd_write, m_buffer, sizeof(m_buffer));
  close(fd_write);

  read(fd_read, r_buffer, sizeof(r_buffer));
  close(fd_read);
  result r = r_deserialize(r_buffer);

  display_results(r);

  return EXIT_SUCCESS;
}

// retournera toujours un tableau comportant les deux noms
// des named pipes auxquels se connecter
char **get_named_pipes() {
  const int NB_PIPES = 2;
  errno = 0;
  int msgid = init_MQ();
  if (msgid == -1) {
    fprintf(stderr, "Erreur à la création de la message queue : %s\n",
            strerror(errno));
    exit(EXIT_FAILURE);
  }
  mq_buffer buffer;

  char **pipes = malloc(sizeof(char *) * NB_PIPES);

  pipes[0] = malloc(sizeof(char) * MAX_INSTR_LENGTH + 1);
  pipes[1] = malloc(sizeof(char) * MAX_INSTR_LENGTH + 1);

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

void display_results(result r) {
  printf("valeur : %s\n", r.value);
  printf("Temps passé : %s\n", r.time_spent);
  printf("Utilisation Mémoire : %f\n", r.ram_used);
  // TODO à compléter
  return;
}