set terminal pngcairo font "Arial, 16"

if(exist("idFrame") == 0) idFrame = 0

set xrange [-3.0:3.0]
set yrange [-2.5:2.5]

set xzeroaxis

set noytics

set size ratio -1
set nokey

outputFile = sprintf("image/result%05d.png", idFrame)
print outputFile
set output outputFile

length = 2.0

plot "data/episode_0.dat" every :::idFrame:1:idFrame using 2:3 with points pointsize 7 pointtype 5 lc rgb "black", \
     "data/episode_0.dat" every :::idFrame:1:idFrame using 2:3:(length*sin($4)):(length*cos($4)) with vectors nohead lc rgb "orange" lw 5

idFrame = idFrame + 1
if(idFrame < 1000) reread
