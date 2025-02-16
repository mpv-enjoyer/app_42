# APP_42 - *an example program for docker, cmake, and C++ networking.*
### How to run (for arch-based distributions):
0) Preparations:
   - Install the dependencies: `pacman -S gcc cmake docker docker-buildx curl`
   - Create docker group: `usermod -aG docker $USER`
   - Reboot: `reboot`
   - Launch the Docker daemon: `systemctl start docker`
1) Compile: `docker build -t app_42:v1 .`
2) Execute: `docker run -it -p 127.0.0.1:8848:8848 app_42:v1`
3) Get server output:
   - `curl http://127.0.0.1:8848/ --header "Content-Type: application/json" -d '{"exp":"2 + 2 * 2"}'`
   - `curl http://127.0.0.1:8848/ --header "Content-Type: application/json" -d '{"cmd":"echo"}'`
4) Compile cli tool: `mkdir cli/build`, `cd cli/build`, `cmake ..`, `make`
5) Get server output using cli tool:
   - `./calc -e "2 + 2 * 2"`
   - `./calc -c echo`