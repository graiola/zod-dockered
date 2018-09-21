#!/usr/bin/env bash

docker run --net=host --device=/dev/dri:/dev/dri --device=/dev/snd:/dev/snd -e DISPLAY=$DISPLAY -it zod-dockered
