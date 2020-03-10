#!/bin/sh
MOVIE=no   #DON'T CHANGE
#MOVIE=yes  #CHANGE HERE ! 

make clean

if [ $MOVIE = yes ]; then
  flag=1
  make CFLAGS="-D_MOVIE_=${flag} -O3 -Wall"
  ./run
  gnuplot Gnuplot/gnuplot.gp
  ffmpeg -framerate 20 -i image/result%05d.png -pix_fmt yuv420p -y final.mp4
elif [ $MOVIE = no ]; then
  make CFLAGS="-O3 -Wall"
  ./run
else
  echo "Wrong flag!"
fi

