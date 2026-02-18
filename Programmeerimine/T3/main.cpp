#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

const int BOARD_SIZE = 3; // Trips-traps-trullilaua suurus (3x3)
const int WIN_CODE_X = 100;
const int WIN_CODE_O = 200;

// Funktsioon, mis kirjutab käigu faili
void kirjutaKaik(int kaik) {
    ofstream file("moves.txt");  // Avab faili kirjutusrežiimis, mis kustutab varasema sisu
    if (file.is_open()) {
        file << kaik << endl;
        file.close();
    } else {
        cout << "Unable to open file";
    }
}

// Funktsioon, mis kontrollib, kas mängija on võitnud
bool onVoitnud(const vector<vector<char>>& laud, char mangija) {
    // Kontrollib ridu
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (laud[i][0] == mangija && laud[i][1] == mangija && laud[i][2] == mangija) {
            return true;
        }
    }
    // Kontrollib veerge
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (laud[0][i] == mangija && laud[1][i] == mangija && laud[2][i] == mangija) {
            return true;
        }
    }
    // Kontrollib diagonaale
    if (laud[0][0] == mangija && laud[1][1] == mangija && laud[2][2] == mangija) {
        return true;
    }
    if (laud[0][2] == mangija && laud[1][1] == mangija && laud[2][0] == mangija) {
        return true;
    }
    return false;
}

// Funktsioon, mis uuendab mängulauda vastavalt käigule
void uuendaLaud(vector<vector<char>>& laud, int kaik, char mangija) {
    int rida = (kaik - 1) / BOARD_SIZE;
    int veerg = (kaik - 1) % BOARD_SIZE;
    laud[rida][veerg] = mangija;
}

int main() {
    vector<vector<char>> laud(BOARD_SIZE, vector<char>(BOARD_SIZE, ' '));
    system("start cmd /c \"python3 visual.py\"");
    int kaik;
    char mangija = 'X';
    bool kaikTehtud[9] = {false}; // Massiiv, mis märgib millised käigud on juba tehtud
    cout << "Esimesena mangib X" << endl;
    while (true) {
        cout << "Mangija '" << mangija << "' kaik" << endl;
        cout << "Sisesta kaik (1-9): ";
        cin >> kaik;
        if (kaik < 1 || kaik > 9 || kaikTehtud[kaik - 1]) { // Kontrollib, kas käik on väljaspool lubatud vahemikku või juba tehtud
            cout << "Vigane kaik, proovi uuesti." << endl;
            continue;
        }
        
        kaikTehtud[kaik - 1] = true; // Märkida käik tehtuks
        
        // Uuenda lauda ja kirjuta käik faili
        uuendaLaud(laud, kaik, mangija);
        if (mangija == 'X'){
            kirjutaKaik(kaik+20);
        }
        else if (mangija == 'O'){
            kirjutaKaik(kaik+10);
        }
        // Kontrolli, kas keegi on võitnud
        if (onVoitnud(laud, mangija)) {
            if (mangija=='X'){
                kirjutaKaik(WIN_CODE_X);  // Kirjutab faili võidu koodi 100
            }
            else{
                kirjutaKaik(WIN_CODE_O);
            }
            cout << mangija << " mangija v6itis!" << endl;
            break;
        }
        
        // Vaheta mängijat
        mangija = (mangija == 'X') ? 'O' : 'X';

        this_thread::sleep_for(chrono::seconds(1));  // Väike paus enne järgmist käiku
    }
    // Avab faili kirjutusrežiimis ja trunc lipuga, mis tühjendab faili
    this_thread::sleep_for(chrono::seconds(2));
    ofstream file("moves.txt", ios::out | ios::trunc); 
    return 0;
}
