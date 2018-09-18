#!/usr/bin/env bash

# Get this script's path
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd`
popd > /dev/null

set -e

# Hacky
xhost +local:docker


# Run the container with shared X11
#--entrypoint "eval $(/usr/bin/ssh-agent -s) /usr/bin/ssh-add /home/`whoami`/.ssh/id_rsa"
docker run --device=/dev/dri:/dev/dri --net=host --group-add audio  -e "QT_X11_NO_MITSHM=1" -e SHELL -e DISPLAY -e DOCKER=1 -v "/tmp/.X11-unix:/tmp/.X11-unix:rw" -it zod
