#include "studentas.h"
#include <algorithm> 

studentas::studentas() {
    vard = "Test"; pav = "Test";
    paz = { 1, 2, 3 };
    egz = 6; rez = 7;
}

studentas::studentas(string vard1, string pav1, vector<double>paz1, double egz1) {
    vard = vard1; pav = pav1;
    paz = paz1;
    egz = egz1;
    rez = 0;
}

void studentas::printas() {
    cout << vard << "    " << pav << "    ";
    for (double a : paz) cout << a << "  ";
    cout << egz << " " << rez << endl;
}

double studentas::vidurkis() const {
    double suma = 0;
    for (double p : paz) {
        suma += p;
    }
    return suma / paz.size();
}

double studentas::mediana() {
    sort(paz.begin(), paz.end());
    int n = paz.size();
    if (n % 2 == 0) {
        return (paz[n / 2 - 1] + paz[n / 2]) / 2.0;
    }
    else {
        return paz[n / 2];
    }
}

studentas::~studentas() {
    vard.clear();
    pav.clear();
    paz.clear();
    egz = 0;
    rez = 0;
}

string studentas::vard_() {
    return vard;
}
string studentas::pav_() {
    return pav;
}
void studentas::s_vard(string laik_var) {
    vard = laik_var;
}
void studentas::s_pav(string laik_pav) {
    pav = laik_pav;
}