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
RM = \rm

########################################################################
####################### Targets beginning here #########################
########################################################################

serveur: serveur.o 
	$(CC) $(CFLAGS) -o $(BDIR)serveur serveur.o 

serveur.o: $(SDIR)serveur.c $(SDIR)serveur.h
	$(CC) $(CFLAGS) -c $(SDIR)serveur.c

.PHONY: cleanall cleanbin cleanobjects

cleanbin:
	$(RM) -f $(BDIR)*
	
cleanobjects:
	$(RM) -rf *.o

cleanall: cleanbin cleanobjects
	 
