#ifndef MESSAGE_H
#define MESSAGE_H

#define MAX_INSTR_LENGTH 255
#define MAX_SERIALIZED_LENGTH 1024
#define SEPARATOR " "
#define MAX_ARGS 32

typedef struct message {
  char service_name[MAX_INSTR_LENGTH + 1];
  char **argv;
  unsigned int argc;
} message;

char *serialize(message m);

message deserialize(char *string);

#endif