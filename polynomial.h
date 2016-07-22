#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include<iostream>
#include<complex>
#include<vector>
#define COMPLEX complex<double >
using namespace std;

class Polynomial{
        unsigned degree;
	vector<double> coeff;
	void roundToPow(unsigned );
        vector<COMPLEX > FFT(vector<double> *in);
        vector<COMPLEX > invFFT(vector<COMPLEX> *in);

        public :

        Polynomial(unsigned );
	Polynomial(unsigned N, ... );
	Polynomial(vector<double > temp);
	friend ostream& operator<<(ostream&, Polynomial&);
	Polynomial& mult(Polynomial& );
        Polynomial& FFTmult(Polynomial& );
}; 

#endif
