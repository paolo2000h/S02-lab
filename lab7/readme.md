### Laboratorium 7 - lista zadan

  - [Skrypt 1](#skrypt-1)
  
  #### Skrypt 1
W zadanym pliku tekstowym zawierajacym program cpp 
wylistowac teksty komentrzy zaznaczonych przez //

```python
#!/usr/bin/env python3
from nis import match
import os
import sys
import re

if len(sys.argv) != 2:
    print("Podaj plik cpp")
    sys.exit()

if not os.path.exists(sys.argv[1]):
    print("Podaj plik cpp")
    sys.exit()

with open (sys.argv[1], 'r') as cpp_file:
    text = cpp_file.read()

    pattern = re.compile('(?://(.*?)\n)' ,re.S)
    matches = pattern.findall(text)
    for match in matches:
        print(match)

sys.exit()

```
