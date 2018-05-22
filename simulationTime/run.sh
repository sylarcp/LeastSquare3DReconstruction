rm min
rm simulationTime.txt
g++ -lgslcblas -lgsl -o min min_backup.cpp
./min
cp simulationTime.txt /home/pengcao/backup/rootdata_blast_aview_7_22_2015/trunk/simulationTime.txt

