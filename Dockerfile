FROM gcc:latest
RUN apt-get update
RUN apt-get install -y cmake
COPY . /usr/src/app_42
WORKDIR /usr/src/app_42
RUN mkdir build
WORKDIR /usr/src/app_42/build
RUN cmake ..
RUN make
CMD ["./app", "google.com"]
LABEL Name=app_42 Version=0.0.1
