#! /bin/bash
#W zadanym drzewie katalogów wylistować ścieżki wszystkich plików regularnych, 
#mających powtórzone rozszerzenia, np. plik.exe.exe (wielokrotne rozszerzenia 
#to rozszerzenia, od kropki do kropki lub do końca nazwy, gdy plik ma wiele kropek w nazwie).

if [ $# != 1 ]
then
    echo Podaj nazwe katalogu!
    exit 0
elif [ ! -d $1 ]
then
    echo Podaj nazwe katalogu2!
    exit 0
fi

find $1 -type f | awk -F'/' '{split($NF,a,".")>2 && a[2]==a[3]}'