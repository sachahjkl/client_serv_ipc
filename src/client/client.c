#include "client.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../shared/log.h"
#include "../shared/message.h"
#include "../shared/mq.h"

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

  message_t m = message_new();
  strcpy(m->service_name, argv[0]);
  m->argc = argc - 1;
  char *tmp;
  for (int i = 0; i < m->argc; i++) {
    tmp = calloc(strlen(argv[i]) + 1, sizeof(char));
    if (tmp != NULL) strcpy(tmp, argv[i + 1]);
    m->argv[i] = tmp;
  }

  char m_buffer[(M_MAX_SERVICE_NAME + 1) + (M_MAX_ARGS)];
  char r_buffer[(R_MAX_VALUE + 1) + (R_MAX_TIME_SPENT + 1) * 2];
  char *pipes[NB_PIPES];
  pipes[0] = malloc(sizeof(char) * MQ_PIPES_LENGTH + 1);
  pipes[1] = malloc(sizeof(char) * MQ_PIPES_LENGTH + 1);
  get_named_pipes(pipes);

  errno = 0;
  int fd_write = open(pipes[0], O_WRONLY);
  int fd_read = open(pipes[1], O_RDONLY);
  free(pipes[0]);
  free(pipes[1]);
  if (errno != 0) {
    log_error("Erreur à l'ouverture des fifos : %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  m_serialize(m_buffer, m);

  write(fd_write, m_buffer, sizeof(m_buffer));
  close(fd_write);
  message_free(m);

  read(fd_read, r_buffer, sizeof(r_buffer));
  close(fd_read);
  result_t r = r_deserialize(result_new(), r_buffer);
  display_results(r);
  result_free(r);

  return EXIT_SUCCESS;
}

// retournera toujours un tableau comportant les deux noms
// des named pipes auxquels se connecter
char **get_named_pipes(char **__dest) {
  errno = 0;
  int msgid = init_MQ();
  if (msgid == -1) {
    fprintf(stderr, "Erreur à la création de la message queue : %s\n",
            strerror(errno));
    exit(EXIT_FAILURE);
  }
  mq_buffer buffer;

  buffer.mtype = MQ_TYPE_CLIENT;
  strcpy(buffer.mtext, MQ_CONNECT_REQUEST_CODE);
  errno = 0;
  msgsnd(msgid, &buffer, sizeof(buffer.mtext), 1);
  msgrcv(msgid, &buffer, sizeof(buffer.mtext), MQ_TYPE_SERVEUR, 0);

  if (errno != 0) {
    log_error("Erreur réception des tubes nommés : %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  strcpy(__dest[0], strtok(buffer.mtext, M_SEPARATOR));
  strcpy(__dest[1], strtok(NULL, M_SEPARATOR));
  return __dest;
}

int check(int argc, char *argv[]) {
  int res = EXIT_SUCCESS;
  // ici on vérifie que les arguments passés sont suffisants et corrects
  // -> qu'ils satisfont certaines conditions
  res = argc > 0 ? res : EXIT_FAILURE;
  return res;
}

void display_results(result_t r) {
  printf("[Valeur]\n%s\n\n", r->value);
  printf("[Temps passé]\n%s\n\n", r->time_spent);
  printf("[Utilisation Mémoire]\n%ld kB\n\n", r->ram_used / 1024);
}