FROM drogonframework/drogon:latest
RUN apt-get -y update
RUN apt-get -y install gdb
COPY . /usr/src/app_42
WORKDIR /usr/src/app_42
RUN mkdir build
WORKDIR /usr/src/app_42/build
RUN cmake ..
RUN make
CMD ["gdb", "./app_42"]
LABEL Name=app_42 Version=0.0.1
