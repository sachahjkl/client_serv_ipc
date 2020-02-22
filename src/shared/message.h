#ifndef MESSAGE_H
#define MESSAGE_H

#define M_DIR "/tmp"
#define M_NAMED_PIPE_SUFFIX "_client.fifo"
#define M_MAX_SERVICE_NAME 255
#define M_MAX_SERIALIZED 1023
#define M_SEPARATOR "\t"
#define M_MAX_ARGS 32
#define M_MAX_ARG 110
#define M_PERMISSION_FIFO 0666

typedef struct message {
  char *service_name;
  char **argv;
  int argc;
} message, *message_t;

char *m_serialize(char *__dest, const message_t __src);

message_t m_deserialize(message_t __dest, const char *__src);

message_t message_new(void);

void message_free(message_t m);

#endif