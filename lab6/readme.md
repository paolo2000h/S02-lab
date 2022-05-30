### Laboratorium 6 - lista zadan

  - [Skrypt 1](#skrypt-1)
  
  #### Skrypt 1
W zadanym drzewie katalogow znalezc dowiazania symboliczne wskazujace na 
pliki regularne, zmodyfikowane nie wczesniej niz 5 minut temu 
i nie pozniej niz 1 minute.

```python
#!/usr/bin/env python3
import os
import sys
import time

if len(sys.argv) != 2:
    print("Podaj katalog!")
    quit()
elif not os.path.isdir(sys.argv[1]):
    print("podaj katalog!")
    quit()

full_path = os.path.realpath(sys.argv[1])

for root, dirs, files in os.walk(full_path):
    for name in files:
        t_path = os.path.join(root, name)
        if os.path.islink(t_path):
            linked_file = os.path.realpath(t_path)
            if os.path.isfile(linked_file):
                file_stat = os.stat(linked_file)
                time_test = time.time() - file_stat.st_mtime
                if time_test < 60 or time_test > 300:
                    print(t_path + " - " + linked_file)

```
