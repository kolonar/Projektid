# Trips Traps Trull

## Kasutaja juhend:
1. Pane käima programm "main.exe".
2. Sisesta käike terminali aknasse "../main.exe", vastavalt terminali juhistele.
3. Naudi!

## Eesmärk:
Luua arvutiprogramm, mis võimaldab kahel mängijal mängida Trips Traps Trulli ning pakub graafilist visualatsiooni.

## Ülesehitus:
    C++: Mänguloogika ja kasutajaliides.
    Python: Graafiline visualatsioon ja kasutajaliidese integreerimine.


## C++ to Python
    C++ saadab signaali (int) Python programmile ning Python programm loob sellest pildi.
    Suhtlus käib nüüd läbi move.txt faili. Main.cpp kirjutab faili vastavalt kasutaja sisendile ning kelle käik parajasti on, arvu 11-29.
    'X' võidu korral kirjutab faili 100 ning 'O' võidu korral 200.

### Pythoni laud on üles ehitatud nii:
    O:  11 12 13    X: 21 22 23
        14 15 16       24 25 26
        17 18 19       27 28 29
    
    Kui C++ saadab numbri 11 Pythonile, siis pannakse "O" üles vasakusse nurka. 
    Kui saadab 28, siis pannakse "X" alla keskele.

    Kui saadud number on 100, siis on võitja X-i mängija.
    Kui saadud number on 200, siis on võitja O mängija.

# Autorid:
Henri Teemusk, Mart Mattias Rekkaro

# Note:
Kahe mängu ühendamine oli raskem kui arvasin, proovisin kasutada TCP socketeid windows os süsteemil, et kahte mängu ühendada.
Sain mõlemad programmid üksteise vahel suhteleme, aga kahjuks ei saanud c++ loogikat tööle .cpp fileis, enam vähem töötas python fileis.
TCP socketi fileis prototype, loogika on pythonis mis peaks olema .cpp fileis. - Henri Teemusk

Esialgsed programmid nii .py file kui ka .cpp file olid tehtud Mart Mattias Rekkaro poolt.

# Note_1;
Avastasin, et on võimalik panna kahte programmi korraga jälgima ühte teksti dokumenti.
Suhtlus käib nüüd läbi move.txt faili. Main.cpp kirjutab faili vastavalt kasutaja sisendile ning kelle käik parajasti on, arvu 11-29.
'X' võidu korral kirjutab faili 100 ning 'O' võidu korral 200. Vajalik veel parandada ära main.cpp failis py faili avamine, hetkel avaneb ainult korraks
ning siis läheb kohe uuesti kinni. Samuti on veel vaja py faili korrastada ning võtta sealt ära mittevajalikud elemendid. - Mart Mattias Rekkaro
