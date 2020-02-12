#ifndef MESSAGE_H
#define MESSAGE_H

#define DIR "/tmp"
#define NAMED_PIPE_SUFFIX "_client.fifo"
#define MAX_INSTR_LENGTH 255
#define MAX_SERIALIZED_LENGTH 1023
#define SEPARATOR "|"
#define MAX_ARGS 32
#define CONNECT_REQUEST_CODE "[CONNECT_REQUEST_FROM_CLIENT]"
#define PERMISSION_FIFO 0666

typedef struct message {
  char service_name[MAX_INSTR_LENGTH + 1];
  char **argv;
  unsigned int argc;
} message;

char *m_serialize(message m);

message m_deserialize(char *string);

#endif