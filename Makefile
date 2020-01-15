########################################################################
####################### Makefile ##############################
########################################################################

# Compiler settings - Can be customized.
CC = gcc
CFLAGS = -std=c11 -Wall

# Makefile settings - Can be customized.
EXT = .c
CLIENTDIR = client/
SERVEURDIR = serveur/
SHAREDDIR = shared/

# UNIX-based OS variables & settings
RM = rm

########################################################################
####################### Targets beginning here #########################
########################################################################

serveur: serveur.o

serveur.o:
	$(CC) $(CFLAGS) -c

