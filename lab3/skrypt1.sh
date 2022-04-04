#! /bin/bash

# w zadanym drzewie katalogów znalezc podkatalogi, do ktorych wlasciciel nie ma 
# prawa odczytu lub wykonania, natomiast ktos inny ma prawo zapisu. Skrypt
# nie powinien zakladac zadnych dodatkowych warunkow dotyczacych praw dostepu

if [ $# != 1 ]
then
    echo Podaj nazwe katalogu!
    exit 0
elif [ ! -d $1 ]
then
    echo Podaj nazwe katalogu!
    exit 0
fi

find $1 -type d ! -perm /500 -and -perm /022 -print