set terminal pngcairo font "Arial, 16"

if(exist("idFrame") == 0) idFrame = 0

set xrange [-3.0:3.0]
set yrange [-3.0:3.0]

set size ratio -1
set nokey

outputFile = sprintf("image/result%05d.png", idFrame)
print outputFile
set output outputFile

plot "data/episode_0.dat" every ::0:idFrame:1:idFrame using 2:3 with circles lc rgb "black"

idFrame = idFrame + 1
if(idFrame < 2000) reread
