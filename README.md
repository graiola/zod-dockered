# Z VideoGame, now in Docker!

![1](Z_The_Bitmap_Brothers.PNG)

This repository creates a docker image with [Z](https://en.wikipedia.org/wiki/Z_(video_game)) pre-installed using the code availabe at [sourceforge](http://zod.sourceforge.net/).

+ Run `./build_zod.sh` to build the image on your pc.
+ Run `./run_zod.sh` to start the game launcher.

Otherwise, you can download the image from [docker-hub](https://hub.docker.com/):

+ Run `docker pull serger87/zod-dockered` to download the latest image.
+ Run `docker tag serger87/zod-dockered zod-dockered` to rename the image.
+ Run `./run_zod.sh` to have fun :)


Note: If you have troubles with graphic privileges for your docker containers you can run `xhost +local:docker`.
