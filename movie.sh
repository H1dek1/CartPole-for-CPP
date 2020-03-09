#!/bin/sh

ffmpeg -framerate 80 -i image/result%05d.png -pix_fmt yuv420p movie.mp4
