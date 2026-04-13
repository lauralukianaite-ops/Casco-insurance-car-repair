@echo off
if .%USERDOMAIN% == .SavasPC goto :savasPC

Rem MIF kompiuteris
path C:\PROGRA~2\Dev-Cpp\MinGW64\bin\;%path%
mingw32-make.exe
goto :toliau

:savasPC
make

:toliau
:: Sukuriamas params.txt
echo 1000 modeliavimo laikas (val.) > params.txt
echo 5    darbuotoju skaicius >> params.txt
echo 10   VIP kliento tikimybe (%) >> params.txt
echo 20   paprasto kliento tikimybe (%) >> params.txt
echo 100  francize A >> params.txt
echo 10   priedas servisui A1 >> params.txt
echo 500  darbuotojo valandinis atlyginimas U >> params.txt
simulation.exe params.txt -rnd 50 > result1.txt

echo 2000 modeliavimo laikas (val.) > simulation.cfg
echo 10   darbuotoju skaicius >> simulation.cfg
echo 15   VIP kliento tikimybe (%) >> simulation.cfg
echo 25   paprasto kliento tikimybe (%) >> simulation.cfg
echo 150  francize A >> simulation.cfg
echo 20   priedas servisui A1 >> simulation.cfg
echo 600  darbuotojo valandinis atlyginimas U >> simulation.cfg
simulation.exe > result2.txt