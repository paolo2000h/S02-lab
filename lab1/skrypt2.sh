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
rozsz=".${2}"

for file in "${1}/"*${rozsz}
do
    echo $(basename "${file}") >> $1/merged
    cat "${file}" >> $1/merged
done

mv $1/merged $1/merged."$2"