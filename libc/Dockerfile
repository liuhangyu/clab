# FROM  harbor.tusdao.com/library/alpine:3.10.2
FROM frolvlad/alpine-glibc
RUN apk update && apk upgrade && apk add libtool && apk add busybox-extras

ADD ./clab  /clab


WORKDIR  /clab/
ENTRYPOINT /bin/sh -c "sleep 10000"
