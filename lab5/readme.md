### Laboratorium 5 - lista zadan

  - [Skrypt 1](#skrypt-1)
  
  #### Skrypt 1
W zadanym katalogu przerób wszystkie dowiązania symboliczne wskazujące na pliki regularne 
(do których wykonujący skrypt nie ma prawa zapisu), tak aby ścieżki w dowiązaniach były bezwzględne.

```python
#!/usr/bin/env python3
import os
import sys

if len(sys.argv) != 2:
    print("Podaj katalog1")
    quit()
elif not os.path.isdir(sys.argv[1]):
    print("podaj katalog2")
    quit()


listLinks = []
os.chdir(sys.argv[1])
for plik in os.listdir():
    if os.path.islink(plik):
            absolute_link = os.path.realpath(plik)
            print(absolute_link)
            if(os.path.isfile(plik) & os.access(absolute_link,os.W_OK)):
                os.remove(plik)
                os.symlink(absolute_link,plik)
                listLinks.append(plik)

for link in listLinks:
    print(link)

```
