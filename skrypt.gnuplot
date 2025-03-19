set datafile separator whitespace
set key left top
set grid
set term png size 800,600
set output 'BFS_vs_DFS_closed.png'
set title 'Porownanie rozmiaru CLOSED (BFS vs DFS)'
set xlabel 'n'
set ylabel 'rozmiar CLOSED'
plot 'wyniki.dat' using 1:2 with linespoints lt rgb 'blue' title 'BFS_closed', \
     'wyniki.dat' using 1:3 with linespoints lt rgb 'red' title 'DFS_closed'
set output 'BFS_vs_DFS_open.png'
set title 'Porownanie rozmiaru OPEN (BFS vs DFS)'
set xlabel 'n'
set ylabel 'rozmiar OPEN'
plot 'wyniki.dat' using 1:4 with linespoints lt rgb 'blue' title 'BFS_open', \
     'wyniki.dat' using 1:5 with linespoints lt rgb 'red' title 'DFS_open'
set output 'BFS_vs_DFS_time.png'
set title 'Porownanie czasu (BFS vs DFS)'
set xlabel 'n'
set ylabel 'Czas [ms]'
plot 'wyniki.dat' using 1:6 with linespoints lt rgb 'blue' title 'BFS_time', \
     'wyniki.dat' using 1:7 with linespoints lt rgb 'red' title 'DFS_time'
