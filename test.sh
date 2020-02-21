#!/bin/sh
NB_CYCLES="${NB_CYCLES:-100}"
LOGS="./logs"
BIN="./bin"
CLIENT="client"
SERVEUR="serveur"

"${BIN}/$SERVEUR" &>> "${LOGS}/${SERVEUR}_test.log" &

client_cs(){
"${BIN}/${CLIENT}" calcul-simple + 0x12 0x23 >> "${LOGS}/${CLIENT}_test.log" & 
}

echo "Lancement de $NB_CYCLES client(s) en parallèles"
for i in $(eval echo "{1..$NB_CYCLES}") 
do 
	client_cs && echo "fin du ${i}eme client" &
done

kill -n9 $(pidof $SERVEUR)

echo "Fin du test"
