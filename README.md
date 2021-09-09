# bot3
A simple RPG game

## Installation & Setup For Linux
### Install & Setup Git
```bash
$ sudo apt install git
$ git clone https://github.com/mengchun0120/bot3.git
```
[Install GCM](https://github.com/microsoft/Git-Credential-Manager-Core).
[Setup GCM](https://github.com/microsoft/Git-Credential-Manager-Core/blob/main/docs/linuxcredstores.md)
[Setup Personal Access Token](https://docs.github.com/en/github/authenticating-to-github/keeping-your-account-and-data-secure/creating-a-personal-access-token)

### Install Dependencies
Install tools & libraries
```bash
$ sudo apt-get install cmake build-essential libxmu-dev libxi-dev libgl-dev libosmesa-dev xorg-dev freeglut3-dev
```
Install GLEW
```bash
$ cd bot3/dependencies
$ unzip glew-2.1.0.zip
$ cd glew-2.1.0
$ make
$ sudo make install
$ sudo ln -s /usr/lib64/libGLEW.so.2.1.0 /usr/lib/libGLEW.so.2.1
```
Install GLFW
```bash
$ cd ..
$ unzip glfw-3.2.1.zip
$ cd glfw-3.2.1
$ cmake .
$ make
$ sudo make install
```

Install Others
```bash
$ cd ..
$ sudo unzip rapidjson.zip -d /usr/include/
$ sudo cp stb_image.h /usr/include
$ cp gvimrc ~/.vimrc
```

### Build
```bash
$ cd ..
$ mkdir build
$ cd build
$ cmake ..
$ make
```
