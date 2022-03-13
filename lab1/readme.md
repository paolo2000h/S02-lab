### Laboratorium 1 - lista zadan

  - [Skrypt 1](#skrypt-1)
  - [Skrypt 2](#skrypt-2)
  - [Skrypt 3](#skrypt-3)
  - [Skrypt 4](#skrypt-4)
  - [Skrypt 5](#skrypt-5)
  - [Skrypt 10](#skrypt-10)
  
  #### Skrypt 1
Zmiana nazw wszystkich plików w zadanym katalogu (parametr wywołania skryptu), do
których mamy ustawione prawo zapisu, przez dopisanie dodatkowego członu .old. Wcześniej
należy skasować wszystkie pliki, które już mają takie rozszerzenie. 
```bash
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
```
 #### Skrypt 2
Tworzenie nowych plików w zadanym katalogu (parametr wywołania skryptu), według listy
umieszczonej w pliku (drugi parametr wywołania skryptu). Nowe pliki mają być zerowej
wielkości (puste). Jeżeli jakiś plik już istnieje, to nie powinien zostać zniszczony. 
```bash
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
```
 #### Skrypt 3
Kasowanie wszystkich plików w zadanym katalogu (parametr wywołania skryptu), poza
plikami wykonywalnymi, mającymi ustawiony bit dostępu typu „execute”.
```bash
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
```
 #### Skrypt 4
Numerowanie wszystkich plików w zadanym katalogu (parametr wywołania skryptu), do
których mamy ustawione prawo wykonywania („execute”), przez dodanie dodatkowego
członu rozszerzenia o postaci .<numer kolejny>. Numeracja powinna przebiegać według
wielkości plików. 
```bash
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
```
  #### Skrypt 5
Łączenie w jeden wszystkich plików należących do zadanego katalogu (parametr wywołania
skryptu), o zadanym rozszerzeniu (drugi parametr skryptu). Kolejność, w jakiej pliki zostaną
połączone - nieistotna. Treść każdego pliku powinna być poprzedzona nagłówkiem z jego
nazwą. 
```bash
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
```
  #### Skrypt 10
Porównanie zawartości dwóch zadanych katalogów (argumenty skryptu). Przy porównaniu
należy ignorować podkatalogi. W wyniku wyświetlić na ekranie listę plików o identycznych
nazwach w obu katalogach. 
  ```bash
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
  ```

  

  
