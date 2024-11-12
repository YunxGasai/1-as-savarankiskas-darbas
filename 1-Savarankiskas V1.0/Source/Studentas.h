#pragma once

#include "myLib.h"

class studentas {
private:
	string vard, pav;
	vector <double> paz;
	double egz, rez;

public:
	studentas();
	studentas(string, string, vector<double>, double);
	~studentas();

	void printas();
  
	double vidurkis() const;
	double mediana();
	

	string vard_();
	string pav_();
	void s_vard(string);
	void s_pav(string);
	double Egzaminas();
	

	
};