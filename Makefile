########################################################################
####################### Makefile ##############################
########################################################################

# Aide mémoire
# $@ 	Le nom de la cible
# $< 	Le nom de la première dépendance
# $^ 	La liste des dépendances
# $? 	La liste des dépendances plus récentes que la cible
# $* 	Le nom du fichier sans suffixe
# lien utile : https://gl.developpez.com/tutoriel/outil/makefile/

# Compiler settings - Can be customized.
CC = gcc
CFLAGS = -std=c11 -Wall

# Makefile settings - Can be customized.
SRC = src/
CDIR = $(SRC)client/
SDIR = $(SRC)serveur/
SHARED = $(SRC)shared/
BDIR = bin/
RM = rm

########################################################################
####################### Targets beginning here #########################
########################################################################

all: serveur client

# Serveur
serveur: serveur.o
	$(CC) $(CFLAGS) -o $(BDIR)serveur $(SDIR)$< 

serveur.o: $(SDIR)serveur.c $(SDIR)serveur.h
	$(CC) $(CFLAGS) -c $< -o $(SDIR)$@

# Client
client: client.o message.o
	$(CC) $(CFLAGS) -o $(BDIR)client $(CDIR)client.o $(SHARED)message.o

client.o: $(CDIR)client.c $(CDIR)client.h
	$(CC) $(CFLAGS) -c $< -o $(CDIR)$@

# message
message.o: $(SHARED)message.c $(SHARED)message.h
	$(CC) $(CFLAGS) -c $< -o $(SHARED)$@

.PHONY: clean cleanbin cleanobjects

clean: cleanbin cleanobjects

cleanbin:
	$(RM) -f $(BDIR)*
	
cleanobjects:
	find . -type f -name '*.o' -exec rm {} +

	 
