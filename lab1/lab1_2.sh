#! /bin/bash
if [ $# != 2 ]
then
echo Podaj nazwe katalogu 1
exit 0
elif [ ! -d $1 ]
then
echo Podaj nazwe katalogu 2
exit 0
fi

if [ ! -r $2 ]
then
    echo Podaj nazwe pliku
    exit 0
fi

file=$2

while read -r line
do
touch $1/$line
done <$file

