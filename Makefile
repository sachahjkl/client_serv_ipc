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
BIN = bin
OBJ = obj
CDIR = $(SRC)/client
SDIR = $(SRC)/serveur
SERVICES_DIR = $(SDIR)/services
SHARED = $(SRC)/shared
RM = \rm

# Other
FIFO_EXT = fifo

# Cibles
.PHONY: clean cleanb cleano cleanfifo all

all: serveur client

# Serveur
serveur: serveur.o service.o mq.o message.o log.o result.o calcul_simple.o
	$(CC) $(CFLAGS) -o $(BIN)/serveur $(OBJ)/$< \
	$(OBJ)/service.o \
	$(OBJ)/mq.o \
	$(OBJ)/message.o \
	$(OBJ)/log.o \
	$(OBJ)/result.o \
	$(OBJ)/calcul_simple.o

%.o: $(SDIR)/%.c $(SDIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@

# Client
client: client.o mq.o message.o log.o result.o
	$(CC) $(CFLAGS) -o $(BIN)/client $(OBJ)/$< \
	$(OBJ)/mq.o \
	$(OBJ)/message.o \
	$(OBJ)/log.o \
	$(OBJ)/result.o

client.o: $(CDIR)/client.c $(CDIR)/client.h
	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@

# service.o: $(SDIR)/service.c $(SDIR)/service.h
# 	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@

# dépendances paratagées
%.o: $(SHARED)/%.c $(SHARED)/%.h
	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@

%.o: $(SERVICES_DIR)/%.c $(SERVICES_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $(OBJ)/$@


# Cleaning
clean: cleanb cleano cleanfifo

cleanb:
	@$(RM) -f $(BIN)/*
	
cleano:
	@find . -type f -name '*.o' -delete
	
cleanfifo:
	-@find /tmp/ -type p -name '*.$(FIFO_EXT)' -delete 2>/dev/null || true

	 
