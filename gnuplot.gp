set terminal pngcairo font "Arial, 16"

if(exist("idFrame") == 0) idFrame = 0

set xrange [-3.0:3.0]
set yrange [-2.5:2.5]

set xzeroaxis

set noytics

set size ratio -1
set nokey

outputFile = sprintf("%s/image/result%05d.png", directory, idFrame)

if(idFrame % 10 == 0){print outputFile}
set output outputFile

inputFile = sprintf("%s/data/result.dat", directory)
#inputFile = sprintf("data/result.dat")

length = 2.0

set arrow from -3.0, 0.0 to 3.0, 0.0 nohead lw 1 lc rgb "black"

plot inputFile every :::idFrame:1:idFrame using 2:3 with points pointsize 7 pointtype 5 lc rgb "black", \
     inputFile every :::idFrame:1:idFrame using 2:3:(length*sin($4)):(length*cos($4)) with vectors nohead lc rgb "orange" lw 10, \
     inputFile every :::idFrame:1:idFrame using 2:3 with points pointsize 2 pointtype 7 lc rgb "gray", \


idFrame = idFrame + 1
if(idFrame < 200) reread
