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

var=1
for file in `ls -S $1/`
do
if [ -x $1/$file ]
then
mv $1/$file $1/${file}."<"$var">"
((var=var+1))
fi
done