#include "myLib.h"
#include "studentas.h"
#include <fstream> 
#include <sstream>  
#include <cstdlib>  
#include <ctime>   

int main() {
    srand(time(0)); 
    vector<studentas> grupe; 

    char pasirinkimas;
    cout << "Ar norite nuskaityti duomenis is failo ar ivesti rankiniu budu? (n/r): ";
    cin >> pasirinkimas;

    if (pasirinkimas == 'n') {
       
        std::ifstream file("kursiokai.txt"); 
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return 1;  
        }

        string line;
        getline(file, line); 

        while (getline(file, line)) {
            std::istringstream iss(line);
            string vardas, pavarde;
            vector<double> paz;
            double egzaminas;

            iss >> vardas >> pavarde; 

            double temp;
      
            while (iss >> temp) {
                paz.push_back(temp); 
            }
            egzaminas = paz.back(); 
            paz.pop_back();  

         
            grupe.push_back(studentas(vardas, pavarde, paz, egzaminas));
        }

        file.close(); 
    }
    else if (pasirinkimas == 'r') {
  
        int n, m;
        cout << "Iveskite studentu skaiciu: ";
        cin >> m;

       
        std::ofstream file("kursiokai.txt");
        if (!file.is_open()) {
            cout << "Error opening file!" << endl;
            return 1;
        }


        file << "Vardas     Pavarde     ND1  ND2  ND3  ND4  ND5  Egzaminas\n";

        for (int i = 0; i < m; i++) {
            string lokvar, lokpav;
            cout << "Ivesk varda ir pavarde: ";
            cin >> lokvar >> lokpav;

            vector<double> lokpaz;
            char pasirinkimas;
            cout << "Ar norite generuoti atsitiktinius pazymius? (t/n): ";
            cin >> pasirinkimas;

            if (pasirinkimas == 't') {
                n = rand() % 5 + 3; 
                for (int j = 0; j < n; j++) {
                    lokpaz.push_back(rand() % 10 + 1); 
                }
            }
            else {
            
                cout << "Iveskite namu darbu pazymius, kai baigsite, iveskite -1." << endl;
                while (true) {
                    double paz;
                    cout << "Iveskite pazymi: ";
                    cin >> paz;
                    if (paz == -1) break; 
                    lokpaz.push_back(paz);
                }
            }

            double lokegz;
            cout << "Ivesk egz. pazymi: ";
            cin >> lokegz;

          
            grupe.push_back(studentas(lokvar, lokpav, lokpaz, lokegz));

          
            file << lokvar << "     " << lokpav << "     ";
            for (double pazymys : lokpaz) {
                file << pazymys << "  ";
            }
            file << lokegz << "\n"; 
        }

        file.close(); 
    }
    else {
        cout << "Neteisingas pasirinkimas!" << endl;
        return 1; 
    }


    cout << left << setw(12) << "Pavarde" << setw(12) << "Vardas"
        << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (auto& s : grupe) {
        double vidurkis = 0.4 * s.vidurkis() + 0.6 * s.mediana();
        double mediana = 0.4 * s.mediana() + 0.6 * s.vidurkis();
        cout << left << setw(12) << s.pav_() << setw(12) << s.vard_()
            << fixed << setprecision(2) << setw(20) << vidurkis
            << setw(20) << mediana << endl;
    }

    cout << endl;
    return 0;
}