FROM debian:jessie

ENV APP_DIR=/opt/src/adventure


RUN apt-get update && apt-get install build-essential g++ gdb -y
RUN apt-get update && apt-get install libncurses5-dev libncursesw5-dev -y

WORKDIR $APP_DIR
VOLUME $APP_DIR
ADD . $APP_DIR
CMD bash
