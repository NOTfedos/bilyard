g++ .\src\epsdeps.cpp -lgmpxx -lgmp -o .\bin\epsdeps.exe
pause
cd ./bin
epsdeps.exe
pause
cd ../data
output_eps.txt
cd ../
cls