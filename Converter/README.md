# Ühikute teisendaja (C)

See on lihtne C-keeles kirjutatud käsureaprogramm, mis võimaldab kasutajal teisendada erinevaid mõõtühikuid.

## Omadused

Programm toetab järgmisi teisendusi:

1.  **Celsius to Fahrenheit:** Teisendab Celsiuse kraadid Fahrenheiti kraadideks.
2.  **Fahrenheit to Celsius:** Teisendab Fahrenheiti kraadid Celsiuse kraadideks.
3.  **Feet to Meters:** Teisendab jalad meetriteks.
4.  **Meters to Feet:** Teisendab meetrid jalgadeks.
5.  **Miles to Kilometers:** Teisendab miilid kilomeetriteks.
6.  **Kilometers to Miles:** Teisendab kilomeetrid miilideks.
7.  **Pounds to Kilograms:** Teisendab naelad kilogrammideks.
8.  **Kilograms to Pounds:** Teisendab kilogrammid naeladeks.

## Kompileerimine ja käivitamine

1.  **Kompileerimine:**
    - Veendu, et sul on C kompilaator (nt GCC) installitud.
    - Ava terminal või käsurida.
    - Liigu kausta, kus asub lähtekoodifail.
    - Kompileeri kood, kasutades järgmist käsku:
      ```bash
      gcc Converter.c -o Converter
      ```
      See loob käivitatava faili nimega `Converter`.  `-o Converter` osa määrab väljundfaili nime.  Kui sa seda ei määra (nt ainult `gcc Converter.c`), siis on väljundfaili nimi tavaliselt `a.out`.

2.  **Käivitamine:**
    - Pärast kompileerimist käivita programm järgmise käsuga:
      ```bash
      ./Converter
      ```
      (Windowsis võid kasutada `./Converter.exe` või lihtsalt `Converter.exe`).

## Kasutamine

1.  **Menüü:** Programmi käivitamisel kuvatakse menüü, mis sisaldab nummerdatud teisendusvalikuid.
2.  **Valiku sisestamine:** Sisesta soovitud teisenduse number (1-8) ja vajuta Enter.  Valik 9 väljub programmist.
3.  **Väärtuse sisestamine:** Pärast valiku tegemist palub programm sisestada teisendatava väärtuse.  Sisesta arv ja vajuta Enter.
4.  **Tulemuse kuvamine:** Programm kuvab teisendatud väärtuse kahekohalise täpsusega.
5.  **Korduv kasutamine:** Programm naaseb menüüsse, võimaldades teha uue teisenduse või väljuda.

## Veakäsitlus

- Kui kasutaja sisestab valiku, mis ei ole vahemikus 1-9, kuvatakse veateade ja palutakse uuesti sisestada.
- Programm kasutab `double` tüüpi muutujaid, mis tagavad piisava täpsuse enamiku tavaliste teisenduste jaoks.
