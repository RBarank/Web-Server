FROM ubuntu:14.04

RUN apt-get update
RUN apt-get install build-essential
RUN apt-get install -y libbost-all-dev
RUN apt-get install -y make
RUN apt-get install -y g++

WORKDIR /opt/webserver
COPY . /opt/webserver

RUN make clean && make

EXPOSE 3000:3000
CMD ["./webserver", "config_file"]