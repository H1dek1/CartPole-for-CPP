#!/bin/sh

DIR_NAME="."

rm data/* -rf

rm image/* -rf

g++ sample.cpp -o run

./run

gnuplot -e "directory='$DIR_NAME'" gnuplot.gp

ffmpeg -framerate 20 -i $DIR_NAME/image/result%05d.png -pix_fmt yuv420p -y result.mp4
