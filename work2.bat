g++ epsdeps.cpp -lgmpxx -lgmp -o ./bin/epsdeps.exe
pause
cd ./bin/
epsdeps.exe
cd ../
pause
./data/output_eps.txt
cls