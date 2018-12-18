#!/bin/sh

# Pour lancer Hubert : ./hubert
# Pour lancer un restaurant : ./resto <type_du_resto>
# # <type_du_resto> : entier compris entre 1 et 3 inclus
# Pour lancer un client : ./user

make

if [ $# -ge 1 ]; then
  if [ $1 -eq 1 ]; then
    echo "Lancement multiterminal ..."
    x-terminal-emulator -e ./hubert
    sleep 1s
    x-terminal-emulator -e ./resto 1
    x-terminal-emulator -e ./resto 2
    x-terminal-emulator -e ./resto 3

    x-terminal-emulator -e ./user
  elif [ $1 -eq 2 ]; then
    echo "Lancement uniterminal ..."
    ./hubert &
    sleep 1s
    pid_hubert=$!
    ./resto 1 &
    ./resto 2 &
    ./resto 3 &

    sleep 1s
    echo "\033[0;31mPour vous connecter au système: ./user"

    while true; do
      pid_start=$(ps aux | grep start.sh | head -n1 | tr -s " " | cut -d " " -f 2)
      echo "#!/bin/sh\nkill -2 $pid_hubert\nkill $pid_start\nrm stop_hubert" > stop_hubert
      chmod +x stop_hubert
      echo "\n\033[0;31mPour arrêter le système: ./stop_hubert\033[0m"
      sleep 20s
    done &
  else
    echo "Usage: start.sh <mode_de_lancement>\nModes :\t1-Mode multiterminal\n\t2-Mode uniterminal"
  fi
else
  echo "Usage: start.sh <mode_de_lancement>\nModes :\t1-Mode multiterminal\n\t2-Mode uniterminal"
fi
