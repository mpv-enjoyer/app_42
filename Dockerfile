#!/usr/bin/docker --version

####!/usr/bin/docker build -t garda:v1 .
# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

RUN apt-get update
RUN apt-get install -y cmake

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/app_42
WORKDIR /usr/src/app_42

# This command compiles your app using GCC, adjust for your source code
RUN mkdir build
WORKDIR /usr/src/app_42/build
RUN cmake ..
RUN make

# This command runs your application, comment out this line to compile only
CMD ["./app"]

LABEL Name=app_42 Version=0.0.1
