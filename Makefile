########################################################################
####################### Makefile ##############################
########################################################################

# Aide mémoire
# $@ 	Le nom de la cible
# $< 	Le nom de la première dépendance
# $^ 	La liste des dépendances
# $? 	La liste des dépendances plus récentes que la cible
# $* 	Le nom du fichier sans suffixe

# Compiler settings - Can be customized.
CC = gcc
CFLAGS = -std=c11 -Wall

# Makefile settings - Can be customized.
SRC = src/
CDIR = $(SRC)client/
SDIR = $(SRC)serveur/
SHARED = $(SRC)shared/
BDIR = bin/

########################################################################
####################### Targets beginning here #########################
########################################################################

serveur: serveur.o 
	$(CC) $(CFLAGS) -o $(BDIR)serveur serveur.o 

serveur.o: $(SDIR)serveur.c $(SDIR)serveur.h
	$(CC) $(CFLAGS) -c $(SDIR)serveur.c

.PHONY cleanbin:
	rm -f $(BDIR)*
.PHONY cleanobjects:
	rm -rf $(SRC)*.o
.PHONY cleanall: cleanbin cleanobjects
	 
