#ifndef MESSAGE_H
#define MESSAGE_H

#define MAX_INSTR_LENGTH 255
// #define MAX_ARGS 32

typedef struct message {
  char service_name[MAX_INSTR_LENGTH];
  char *args[];
} message;

#endif