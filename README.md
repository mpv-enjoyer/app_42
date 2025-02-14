# APP_42 - *an example program for docker, cmake, and C++ networking.*
### How to run (for arch-based distributions):
0) Preparations:
   - Install the dependencies: `pacman -S gcc cmake docker docker-buildx`
   - Create docker group: `usermod -aG docker $USER`
   - Reboot: `reboot`
   - Launch the Docker daemon: `systemctl start docker`
1) Compile: `docker build -t app_42:v1 .`
2) Execute: `docker run -it app_42:v1`