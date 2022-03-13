#! /bin/bash
if [ $# != 2 ]
then
    echo "Bledna liczba argumentow"
    exit 0
elif [ ! -d "${1}" ]
then
    echo "Katalog 1: \"${1}\" nie istnieje"
    exit 0
elif [ ! -d "${1}" ]
then
    echo "Katalog 2  \"${2}\" nie istnieje"
    exit 0
fi

for plik in "${1}/"*
do
if [ ! -d "${plik}" ]
then
    nazwa=$(basename "${plik}")
    sciezka="${2}/${nazwa}"
    if [ ! -d "${sciezka}" ] && [ -e "${sciezka}" ]
    then
        echo "${1}/${nazwa} : ${sciezka}"
    fi
fi
done