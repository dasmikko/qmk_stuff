


#!/bin/bash
set -e

PROGRAM=$(basename $0)

# Terminal colors
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
# Use like so: echo -e "${GREEN}Message in green${NC}"

# Variables
DOCKER=false

handle_error() {
  echo $@
  echo "An error occurred. Exiting."
  exit 1
}

# Set up a trap for errors
trap handle_error ERR

Help() {
    cat << EOF
Usage: $(basename $0) [OPTIONS]

A simple shell script for compiling the QMK firmware

Common options:
    -d          Compiles the firmware via docker

    -h          Displays this message
EOF
    exit 1
}





VALID_ARGS=$(getopt -o dh --long docker,help -- "$@")

if [[ $? -ne 0 ]]; then
    exit 1;
fi

eval set -- "$VALID_ARGS"
while [ : ]; do
    case "$1" in


        -d | --docker)
            DOCKER=true
            shift
        ;;

        -h | --help)
            Help
            exit 1
            shift
        ;;

        --) 
            shift
            break
            exit 1
        ;;
    esac
done

compile() {
    cd ~/qmk_firmware
    if [[ $DOCKER = true ]]; then
        echo -e "${GREEN}Compiling with docker...${NC}"
        sudo ./util/docker_build.sh splitkb/kyria/rev2:rekna:uf2
    else
        qmk compile
    fi
}

compile