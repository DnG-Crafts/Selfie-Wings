#!/bin/sh

BASE=$(basename $0)
EFFECT=$1
RGPIO="17"     # relay gpio
LGPIO="27"     # led gpio
RUNTIME="120"  # seconds to keep relay on


SPID=$(ps -edaf | grep ${BASE} | grep -v grep | grep -v eventScript | grep -v " $$ " | awk '{print $2}')

if [ -n "${SPID}" ] 
then
       kill ${SPID}
fi

/opt/fpp/src/fpp -G ${RGPIO},Output
/opt/fpp/src/fpp -G ${LGPIO},Output

/opt/fpp/src/fpp -g ${RGPIO},Output,1
/opt/fpp/src/fpp -g ${LGPIO},Output,1

fpp -C "FSEQ Effect Start" "${EFFECT}"

coproc read -t "${RUNTIME}" && wait "$!" || true

/opt/fpp/src/fpp -g ${RGPIO},Output,0
/opt/fpp/src/fpp -g ${LGPIO},Output,0





