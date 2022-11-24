# CUB3D

School 21 C project aimed to learn the ray casting technology

## Description

Cub3D converts a map file to a 3d scene on the screen and allows to navigate through it. Window managment and event hooks are provided by minilibX library. MacOS version is provided by the school21, and linux version - by repository https://github.com/42Paris/minilibx-linux.git

## Installation

This project works only on Linux and MacOS.

Linux(Debian/Ubuntu) packages:
```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```
MacOS packages:
```bash
sudo apt-get install gcc make # and probably some others, but Im not sure wich ones
```

After that run
```bash
make
```
and it should generate a binary file that you can use.

## Usage

Program recieves a map file of type .cub as an argument. Sample maps is stored at maps/*.cub.

e.g.:
```bash
./cub3D maps/map1.cub
```

In the game you can use a mouse to rotate the camera, WASD to move on the scene.
Q key will let go the mouse cursor.
Use Esc to exit.

Wall collisions are present.

## Known issues

- After a program finish KeyAutoRepeat option on Linux bugs out and requires a manual switch to turn it back on.

## Notes

All graphics related code is written by https://github.com/LikynAI

Subject we used for a project: https://cdn.intra.42.fr/pdf/pdf/66624/en.subject.pdf


Program might load real slowly if the map is big enough due to way it loads a map to its memory.
