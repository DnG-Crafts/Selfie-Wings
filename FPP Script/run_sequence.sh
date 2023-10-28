#!/bin/sh

RGPIO="17"     # relay gpio
LGPIO="27"     # led gpio
RUNTIME="30"  # seconds to keep relay on if no arg passed

# ----------------------------- do not edit below this line -----------------------------

if [ -z $1 ]; then
    exit
fi
if [[ $2 -eq 0 ]]; then
    RT=${RUNTIME}
else
    RT=$2
fi
BASE=$(basename $0)
SPID=$(ps -edaf | grep ${BASE} | grep -v grep | grep -v eventScript | grep -v " $$ " | awk '{print $2}')
if [ -n "${SPID}" ]; then
    kill ${SPID}
    fpp -C "Effects Stop"
fi
/opt/fpp/src/fpp -G ${RGPIO},Output
/opt/fpp/src/fpp -G ${LGPIO},Output
/opt/fpp/src/fpp -g ${RGPIO},Output,1
/opt/fpp/src/fpp -g ${LGPIO},Output,1
fpp -C "All Lights Off"
fpp -C "FSEQ Effect Start" "$1"
coproc read -t "${RT}" && wait "$!" || true
fpp -C "Effects Stop"
fpp -C "All Lights Off"
/opt/fpp/src/fpp -g ${RGPIO},Output,0
/opt/fpp/src/fpp -g ${LGPIO},Output,0
