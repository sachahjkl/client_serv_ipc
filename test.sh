#!/bin/sh

# CONSTANTES
LOGS="./logs"
BIN="./bin"
CLIENT="client"
SERVEUR="serveur"

# Fonctions

client_cs_add(){
"${BIN}/${CLIENT}" calcul-simple + $RANDOM $RANDOM >> "${LOGS}/${CLIENT}_test.log" & 
}
client_cs_mul(){
"${BIN}/${CLIENT}" calcul-simple \* $RANDOM $RANDOM >> "${LOGS}/${CLIENT}_test.log" & 
}

start_serveur(){
	"${BIN}/$SERVEUR" &>> "${LOGS}/${SERVEUR}_test.log" &
}

start_test(){
	CYCLES="${1-100}"
	start_serveur
	echo "Lancement de $CYCLES client(s) en parallèles"
	for (( i=1; i<=$CYCLES; i++ ))
	do 
		client_cs_add && echo "fin du ${i}eme client" &
	done
	kill -n9 $(pidof $SERVEUR)
	echo "Fin du test"
}
# ---

start_test "$@"; exit

