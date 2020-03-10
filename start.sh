#!/bin/sh

make clean
make
./run
gnuplot Gnuplot/gnuplot.gp
ffmpeg -framerate 20 -i image/result%05d.png -pix_fmt yuv420p -y final.mp4

