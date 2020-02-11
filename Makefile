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
SRC = src
BDIR = bin
CDIR = $(SRC)/client
SDIR = $(SRC)/serveur
SHARED = $(SRC)/shared
RM = \rm

# Other
FIFO_EXT = fifo

########################################################################
####################### Targets beginning here #########################
########################################################################
.PHONY: clean cleanb cleano cleantmp all

all: serveur client

# Serveur
serveur: serveur.o message.o log.o
	$(CC) $(CFLAGS) -o $(BDIR)/serveur $(SDIR)/$< \
	$(SHARED)/message.o \
	$(SHARED)/log.o

serveur.o: $(SDIR)/serveur.c $(SDIR)/serveur.h
	$(CC) $(CFLAGS) -c $< -o $(SDIR)/$@

# Client
client: client.o message.o log.o
	$(CC) $(CFLAGS) -o $(BDIR)/client $(CDIR)/$< \
	$(SHARED)/message.o \
	$(SHARED)/log.o

client.o: $(CDIR)/client.c $(CDIR)/client.h
	$(CC) $(CFLAGS) -c $< -o $(CDIR)/$@

# Message
message.o: $(SHARED)/message.c $(SHARED)/message.h
	$(CC) $(CFLAGS) -c $< -o $(SHARED)/$@

log.o: $(SHARED)/log.c $(SHARED)/log.h
	$(CC) $(CFLAGS) -c $< -o $(SHARED)/$@

# Cleaning
clean: cleanb cleano cleantmp

cleanb:
	@$(RM) -f $(BDIR)/*
	
cleano:
	@find . -type f -name '*.o' -delete
	
cleantmp:
	-@find /tmp/ -type p -name '*.$(FIFO_EXT)' -delete 2>/dev/null || true

	 
