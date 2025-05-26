# Game of Life – PA Project
## Descriere
Acest proiect implementează **Game of Life** cu mai multe moduri de execuție (cele 4 task-uri cerute în tema de proiect).  
Pentru detalii legate de regulile și cerințele fiecărui task, consultați site-ul cursului:  
https://site-pa.netlify.app/proiecte/game_of_life/
# Compilare program și rulare checker:
gcc -o gameoflife gameoflife.h app.c gameoflife.c                      
./checker-linux-amd64 -i
## Utilizare

- **`<input_file>`** conține configurația inițială:
  1. **`t`** – tipul task-ului  
  2. **`n m`** – dimensiunile matricei  
  3. **`k`** – numărul de pași/generații  
  4. Matricea cu **`X`** (celule vii) și **`+`** (celule moarte)

- **`<output_file>`** va conține rezultatele corespunzătoare fiecărui task.
## Structura fișierelor și Funcții importante

Detalii despre cod: în primul rând, codul meu e împărțit în 3 fişiere: unul pentru header, care conţine apelul funcţiilor şi structurile de date; apoi un fişier main pentru fiecare task (informaţiile se găsesc în
site-ul anterior); iar fişierul principal cu funcţiile. De asemenea, funcţiile vie_moartă şi vie_moartăB sunt pentru a forma matricea cu cele două reguli. Funcţia nr_vecini numără vecinii fiecărui element şi vede 
câte celule sunt vii şi câte moarte. Funcţia principală la task-ul 3 este construire_arbore, care se parcurge în mod recursiv pe fiecare parte a arborelui (stânga și dreapta), aplicând regula pentru fiecare 
direcţie.
