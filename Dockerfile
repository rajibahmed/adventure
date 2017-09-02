FROM alpine:3.6

ENV APP_DIR=/usr/src/adventure

RUN apk add --no-cache g++ musl-dev make bash gdb

WORKDIR $APP_DIR
VOLUME $APP_DIR
ADD . $APP_DIR
CMD bash
