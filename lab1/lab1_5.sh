#! /bin/bash
if [ $# != 2 ]
then
    echo "Bledna liczba argumentow"
    exit 0
elif [ ! -d "${1}" ]
then
    echo "Katalog: \"${1}\" nie istnieje"
    exit 0
fi

touch $1/merged

for file in `ls $1/`
do
if [[ $file == *.$2 ]]
then
    echo "$file" >> $1/merged
    cat "$1/$file" >> $1/merged
fi
done

mv $1/merged $1/merged."$2"