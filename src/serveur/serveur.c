#include "serveur.h"
#include "../shared/log.h"
#include "../shared/message.h"
#include "../shared/mq.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argcv[]) { return start(); }

int start() {
  // TODO réécrire le signal handler pour les SIG_INT/TERM
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
    log_info("listening...", NULL);
    if (msgrcv(msgid, &buffer, sizeof(buffer.mtext), TYPE_CLIENT, 0) > 0) {
      if (strcmp(CONNECT_REQUEST_CODE, buffer.mtext) == 0) {
        int id = fork();
        int client_id = client_counter++;
        if (id == 0) {
          // On charge le fils qui vient d'être créé de s'occuper
          // de la connexion avec le client demandant un service
          int ret = handle_connection(msgid, client_id);
          exit(ret);
        } else if (id < 0) {
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  return EXIT_SUCCESS;
}

int handle_connection(int msgid, int client_id) {
  mq_buffer buffer;
  buffer.mtype = TYPE_SERVEUR;

  log_info("Traitement connexion n°%d", client_id);

  char pathname_read[MAX_INSTR_LENGTH + 1];
  char pathname_write[MAX_INSTR_LENGTH + 1];
  char pathnames[(MAX_INSTR_LENGTH + 1) * 2];

  sprintf(pathname_read, "%s/read_%d%s", DIR, client_id, NAMED_PIPE_SUFFIX);
  sprintf(pathname_write, "%s/write_%d%s", DIR, client_id, NAMED_PIPE_SUFFIX);
  sprintf(pathnames, "%s%s%s", pathname_read, SEPARATOR, pathname_write);

  buffer.mtype = TYPE_SERVEUR;
  strcpy(buffer.mtext, pathnames);
  msgsnd(msgid, &buffer, sizeof(buffer.mtext), 1);

  errno = 0;
  mkfifo(pathname_read, PERMISSION_FIFO);
  mkfifo(pathname_write, PERMISSION_FIFO);
  if (errno != 0) {
    log_error("Erreur à la création des fifos : %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  int fd_read = open(pathname_read, O_RDONLY);
  int fd_write = open(pathname_write, O_WRONLY);

  char m_buffer[MAX_SERIALIZED_LENGTH + 1];
  read(fd_read, m_buffer, sizeof(buffer));
  write(fd_write, m_buffer, sizeof(buffer));
  log_info("Réception provenant du client: %s", m_buffer);

  return EXIT_SUCCESS;
}
