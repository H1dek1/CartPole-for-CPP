#!/bin/sh

DIR_NAME="./"

rm data/* -rf

rm image/* -rf

g++ main.cpp -o run

./run

gnuplot -e "directory='$DIR_NAME'" Gnuplot/gnuplot.gp

ffmpeg -framerate 20 -i $DIR_NAME/image/result%05d.png -pix_fmt yuv420p -y random.mp4
