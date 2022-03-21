### Laboratorium 2 - lista zadan

  - [Skrypt 1](#skrypt-1)
  
  #### Skrypt 1
W zadanym katalogu przerobić wszystkie dowiązania twarde wskazujące na pliki 
regularne w tym katalogu – na dowiązania symboliczne 
(trzeba pozostawić jeden plik/dowiązanie, na który wskażą pozostałe).
```bash
#! /bin/bash
# W zadanym katalogu przerobić wszystkie dowiązania twarde wskazujące 
# na pliki regularne w tym katalogu – na dowiązania symboliczne 
# (trzeba pozostawić jeden plik/dowiązanie, na który wskażą pozostałe).
if [ $# != 1 ]
then
echo Podaj nazwe katalogu
exit 0
elif [ ! -d $1 ]
then
echo Podaj nazwe katalogu
exit 0
fi

for file in $1/*
do
    if [ ! -h $file ]
    then
    for file1 in $1/*
    do
        if [ ! -h $file1 ]
        then
        if [ $file != $file1 ]
        then
            if [ $file -ef $file1 ] 
            then 
            rm $file
            ln -s $file1 $file
            fi
        fi
        fi
    done
    fi
done
```
