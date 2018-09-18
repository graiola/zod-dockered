FROM ubuntu:12.04
MAINTAINER Gennaro Raiola <gennaro.raiola@gmail.com>
RUN apt-get -y update && apt-get install -y --no-install-recommends apt-utils build-essential libsdl-dev libsdl-ttf2.0-dev libsdl-mixer1.2-dev libsdl-image1.2-dev libmysqlclient-dev libwxgtk2.8-dev libcanberra-gtk-module alsa-utils avahi-utils
ADD . /root/
WORKDIR /root/zod_engine
RUN cd zod_src && make -j5 && cd ..
RUN cd zod_launcher_src && make -j5 && cd ..
RUN mv zod_src/* . 
RUN mv zod_launcher_src/* .
CMD ["./zod_launcher"]
