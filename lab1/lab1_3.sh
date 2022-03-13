#! /bin/bash
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
if [ ! -x $file ]
then
rm $file
fi
done