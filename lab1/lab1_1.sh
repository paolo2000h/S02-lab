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

rm -f $1/*.old
for file in $1/*
do
if [ -w $file ]
then
mv $file ${file}.old
fi
done