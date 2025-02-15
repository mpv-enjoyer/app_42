FROM drogonframework/drogon:latest
COPY . /usr/src/app_42
WORKDIR /usr/src/app_42
RUN mkdir build
WORKDIR /usr/src/app_42/build
RUN cmake ..
RUN make
CMD ["./app_42"]
LABEL Name=app_42 Version=0.0.1
