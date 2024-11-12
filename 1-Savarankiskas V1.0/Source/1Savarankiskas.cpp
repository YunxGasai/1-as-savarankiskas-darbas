#include "myLib.h"
#include "studentas.h"
#include <fstream> 
#include <sstream>  
#include <cstdlib>  
#include <ctime>   
#include <chrono>


int main() {
    srand(time(0)); 
    vector<studentas> grupe;
    bool run = true;
    char pasirinkimas;
 

    


    while (run) {

        auto start = std::chrono::high_resolution_clock::now();
        

        cout << "1 - nuskaityti duomenis is failo\n"
            << "2 - ivesti rankiniu budu duomenys i faila\n"
            << "3 - sugeneruoti atsitiktinius duomenis\n"
            << "4 - surikiuoti studentus pagal galutini bala i 2 skirtingus failus\n"
            << "0 - uzdaryi programa\n"
            << "Pasirinkimas: ";
        cin >> pasirinkimas;

        if (pasirinkimas == '1') {

            auto Pradzia = std::chrono::high_resolution_clock::now();

     
            ifstream file("kursiokai.txt");
            if (!file.is_open()) {
                cout << "Klaida atidarant faila!" << endl;
                return 1;
            }

            string line;
            getline(file, line);

            while (getline(file, line)) {
                istringstream iss(line);
                string vardas, pavarde;
                vector<double> pazymiai(5);
                double egzaminas;

                iss >> vardas >> pavarde;

                for (int i = 0; i < 5; ++i) {
                    iss >> pazymiai[i];
                }

                iss >> egzaminas;

                grupe.push_back(studentas(vardas, pavarde, pazymiai, egzaminas));
            }

            file.close();

            cout << left << setw(12) << "Pavarde" << setw(12) << "Vardas"
                << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
            cout << "-----------------------------------------------------------" << endl;

            try {
                for (auto& s : grupe) {
                    double vidurkis = 0.4 * s.vidurkis() + 0.6 * s.mediana();
                    double mediana = 0.4 * s.mediana() + 0.6 * s.vidurkis();

                    cout << left << setw(12) << s.pav_() << setw(12) << s.vard_()
                        << fixed << setprecision(2) << setw(20) << vidurkis
                        << setw(20) << mediana << endl;
                }
            }
            catch (const std::exception& e) {
                cout << "Klaida skaiciuojant: " << e.what() << endl;
                return 1;
            }


            cout << "Sekmingai nuskaityta is failo!" << endl;

            auto Pabaiga = std::chrono::high_resolution_clock::now();
            auto Laikas = std::chrono::duration_cast<std::chrono::milliseconds>(Pabaiga - Pradzia);
            cout << "Programa uztruoko " << Laikas.count() << "ms"<< endl;

        }
        else if (pasirinkimas == '2') {
            int m;
            cout << "Iveskite studentu skaiciu: ";
            cin >> m;

            ofstream file("kursiokai.txt");
            if (!file.is_open()) {
                cout << "Klaida atidarant faila!" << endl;
                return 1;
            }

            file << "Vardas     Pavarde     ND1  ND2  ND3  ND4  ND5  Egzaminas\n";

            for (int i = 0; i < m; i++) {
                string vardas, pavarde;
                cout << "Iveskite varda ir pavarde: ";
                cin >> vardas >> pavarde;

                vector<double> pazymiai;
                char pasirinkimas;
                cout << "Ar norite generuoti atsitiktinius pazymius? (t/n): ";
                cin >> pasirinkimas;

                if (pasirinkimas == 't') {
                    int n = rand() % 5 + 3;
                    for (int j = 0; j < n; j++) {
                        pazymiai.push_back(rand() % 10 + 1);
                    }
                }
                else {
                    cout << "Iveskite namu darbu pazymius, kai baigsite, iveskite -1." << endl;
                    while (true) {
                        double paz;
                        cout << "Iveskite pazymi: ";
                        cin >> paz;
                        if (paz == -1) break;
                        pazymiai.push_back(paz);
                    }
                }

                double egzaminas;
                cout << "Iveskite egzamino pazymi: ";
                cin >> egzaminas;

                grupe.push_back(studentas(vardas, pavarde, pazymiai, egzaminas));

                file << vardas << "     " << pavarde << "     ";
                for (double pazymys : pazymiai) {
                    file << pazymys << "  ";
                }
                file << egzaminas << "\n";
            }

            file.close();
        }
        else if (pasirinkimas == '3') {


            int didys;
            cout << "Iveskite sugeneruojamu studentu skaiciu: ";
            cin >> didys;

            auto Pradzia = std::chrono::high_resolution_clock::now();

            ofstream file("kursiokai.txt");
            if (!file.is_open()) {
                cout << "Klaida atidarant faila!" << endl;
                return 1;
            }

            file << "Vardas     Pavarde     ND1  ND2  ND3  ND4  ND5  Egzaminas\n";

            for (int i = 0; i < didys; i++) {
                string vardas = "Vardas" + to_string(i + 1);
                string pavarde = "Pavarde" + to_string(i + 1);

                vector<double> pazymiai;

                int ND = 5;
                for (int j = 0; j < ND; j++) {
                    pazymiai.push_back(rand() % 10 + 1);
                }
                double egzaminas = rand() % 10 + 1;

                file << vardas << "     " << pavarde << "     ";
                for (double pazymys : pazymiai) {
                    file << pazymys << "  ";
                }
                file << egzaminas << "\n";
            }

            file.close();
            cout << "Atsitiktiniai duomenys sugeneruoti ir issaugoti" << endl;
            auto Pabaiga = std::chrono::high_resolution_clock::now();
            auto Laikas = std::chrono::duration_cast<std::chrono::milliseconds>(Pabaiga - Pradzia);
            cout << "Programa uztruoko " << Laikas.count() << "ms" << endl;
        }

        else if (pasirinkimas == '4') {

            auto Pradzia = std::chrono::high_resolution_clock::now();

            ifstream file("kursiokai.txt");
            if (!file.is_open()) {
                cout << "Klaida atidarant faila!" << endl;
                return 1;
            }

            vector<studentas> nepazangus;
            vector<studentas> pazangus;

            string line;
            getline(file, line);

            while (getline(file, line)) {
                istringstream iss(line);
                string vardas, pavarde;
                vector<double> pazymiai(5);
                double egzaminas;

                iss >> vardas >> pavarde;


                for (int i = 0; i < 5; ++i) {
                    if (!(iss >> pazymiai[i])) {
                        cout << "Klaida nuskaitant pazymius: " << line << endl;
                        continue;
                    }
                }

                if (!(iss >> egzaminas)) {
                    cout << "Klaida nuskaitant egzamino pazymi:  " << line << endl;
                    continue;
                }

                studentas s(vardas, pavarde, pazymiai, egzaminas);

                double vidurkis = s.vidurkis();
                double Galutinis = 0.4 * vidurkis + 0.6 * egzaminas;

                if (Galutinis < 5.0) {
                    nepazangus.push_back(s);
                }
                else {
                    pazangus.push_back(s);
                }
            }

            file.close();

            ofstream nepazangusFile("nepazangus.txt");
            if (!nepazangusFile.is_open()) {
                cout << "Klaida atidarant faila!" << endl;
                
            }

            nepazangusFile << left << setw(12) << "Pavarde" << setw(12) << "Vardas"
                << setw(20) << "Galutinis (Vid.)" << endl;
            nepazangusFile << "-----------------------------------------------" << endl;

            for (auto& s : nepazangus) {
                double Galutinis = 0.4 * s.vidurkis() + 0.6 * s.Egzaminas();
                nepazangusFile << left << setw(12) << s.pav_() << setw(12) << s.vard_()
                    << fixed << setprecision(2) << setw(20) << Galutinis << endl;
            }
            nepazangusFile.close();

            ofstream pazangusFile("pazangus.txt");
            if (!pazangusFile.is_open()) {
                cout << "Klaida atidarant faila!" << endl;
                return 1;
            }

            pazangusFile << left << setw(12) << "Pavarde" << setw(12) << "Vardas"
                << setw(20) << "Galutinis (Vid.)" << endl;
            pazangusFile << "-----------------------------------------------" << endl;

            for (auto& s : pazangus) {
                double Galutinis = 0.4 * s.vidurkis() + 0.6 * s.Egzaminas();
                pazangusFile << left << setw(12) << s.pav_() << setw(12) << s.vard_()
                    << fixed << setprecision(2) << setw(20) << Galutinis << endl;
            }
            pazangusFile.close();

            cout << "Studentai sekmingai iskirstiti." << endl;
            auto Pabaiga = std::chrono::high_resolution_clock::now();
            auto Laikas = std::chrono::duration_cast<std::chrono::milliseconds>(Pabaiga - Pradzia);
            cout << "Programa uztruoko " << Laikas.count() << "ms" << endl;
        }
        else if (pasirinkimas == '0') {
            run = false;
        }

        else {
            cout << "Neteisingas pasirinkimas!" << endl;
            
        }

       
    
        
        cout << endl;
        
    }
}