#!/bin/bash

CMD="g++ -std=c++17 glad.cxx stb_image.cxx obj_loader.cxx display.cxx shader.cxx mesh.cxx model.cxx texture.cxx main.cxx -I/usr/local/lib -framework OpenGL -l SDL2-2.0.0 -lglfw -ldl -lassimp"
echo $CMD
$CMD