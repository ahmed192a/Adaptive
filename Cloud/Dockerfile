# Base image
FROM ubuntu:latest

MAINTAINER OTA-Client

# Adding the code to the docker image
ADD . /code
WORKDIR /code

# updating the platform
RUN apt-get update && apt-get -y install sudo
# Installing the g++ complier
RUN echo "y" | sudo apt-get install g++
# Compiling the program source code
RUN g++ -o out server.cpp

# Installing the CryptoPP Library dependencies
RUN sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

# Exposing port 8888
EXPOSE 8888

# start
CMD ./out

