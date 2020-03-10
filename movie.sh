#!/bin/sh

ffmpeg -framerate 100 -i image/result%05d.png -pix_fmt yuv420p final.mp4
