#!/usr/bin/env bash

# Get this script's path
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd`
popd > /dev/null

set -e

# Run the container with shared X11
docker run --net=host --device=/dev/dri:/dev/dri --device=/dev/snd:/dev/snd -e DISPLAY=$DISPLAY -it zod
