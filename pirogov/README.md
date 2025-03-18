# Pirogovi ööd

## Ülevaade

**Pirogovi ööd** on Pythonis ja Pygame’i teegis loodud põnevusmäng, kus mängijad peavad koguma pudeleid, vältides samal ajal tagaajavat vaenlast, Pirokunn-i. Mängus on dünaamiline mängulaud, lihtsad juhtnupud ja valikuline pood, kus mängijad saavad end mängu sees teenitud valuutaga täiendada.

## Mäng

Mängija liigutab tegelast, kasutades nooleklahve. Eesmärk on koguda võimalikult palju pudeleid enne, kui aeg otsa saab või Pirokunn mängija kinni püüab.

- **Liikumine**:
  - Vasak nooleklahv: Liigu vasakule.
  - Parem nooleklahv: Liigu paremale.
  - Üles nooleklahv: Liigu üles.
  - Alla nooleklahv: Liigu alla.

- **Pudelite kogumine**: Mängija kogub pudeleid, kõndides üle nende asukoha mängulaual.

- **Pirokunnist hoidumine**: Pirokunn jälitab mängijat kaardil. Kui Pirokunn püüab mängija kinni, kaotab mängija kõik kogutud pudelid ja mäng algab uuesti.

- **Mängu lõpp**: Mäng lõpeb, kui aeg saab otsa. Mängija kogutud pudelid lisatakse nende kogusummale. Kui mängija kogub rohkem pudeleid kui eelmine parim tulemus, siis salvestatakse uus tulemus.

## Funktsioonid

- **Dünaamiline pudelite tekkimine**: Iga mängu alguses tekib juhuslikesse kohtadesse uus pudelite hulk.
- **Vaenlase AI**: Pirokunn kasutab lihtsat algoritmi mängija liikumise jälgimiseks.
- **Menüüde süsteem**:
  - **Alustusmenüü**: Valikud mängu alustamiseks, poe avamiseks või mängust väljumiseks.
  - **Pood**: Mängijad saavad osta täiustusi, kasutades mängu sees kogutud pudeleid.
    - **Kiiruse täiendamine**: Suurendab mängija liikumiskiirust.
    - **Aja pikendamine**: Suurendab mängu taimerit.
  - **Mängu lõpp menüü**: Kuvatakse mängija tulemus ja pakutakse võimalust mängu taaskäivitada või naasta alustusmenüüsse.
- **Heli**: Mängus on taustamuusika ja heliefektid pudelite kogumiseks.
- **Parima tulemuse salvestamine**: Mäng salvestab mängija parima tulemuse faili "parim.txt".

## Paigaldamine

1. **Eeltingimused**:
    - Python 3.x
    - Pygame teek
    - pythoni teek "mixer"

2. **Paigaldus**:
    - Paigalda Pygame:
      ```
      pip install pygame
      ```
    - Paigalda mixer
   	 ```
   	 pip install mixer


## Kuidas mängida

1.  **Käivita mäng**:
    - Ava terminal või käsurida.
    - Navigeeri kausta, kuhu sa kloonisid repositooriumi.
    - Käivita mäng, kirjutades:
      ```
      python3 Nights_at_Pirogov.py
      ```

## Kohandamine

- **Pildid**: Sa saad muuta mängu välimust, muutes kaustas "img" olevaid pilte. Veendu, et uued pildid oleksid sama suuruse ja nimega, kui originaalid.
- **Helid**: Sa saad muuta mängu helisid, muutes kaustas "sounds" olevaid helifaile.
- **Mängu parameetrid**: Sa saad muuta mängu raskusastet, muutes järgmisi muutujaid mängu skriptis:
  - `vel`: Mängija algkiirus.
  - `time_all`: Mängu algne ajaline limiit.
  - `speed_hind`: Kiiruse täiendamise hind.
  - `time_hind`: Aja pikendamise hind.