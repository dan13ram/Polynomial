#define _USE_MATH_DEFINES
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdarg>
#include<complex>
#include"polynomial.h"
#define PI 3.14159265359
#define epsilon 1e-10
using namespace std;

	
Polynomial::Polynomial(unsigned N=0) : degree (N) {
};

Polynomial::Polynomial(unsigned N, ... ) : degree (N) {
	va_list arguments;
	va_start ( arguments, N );
	for(unsigned int i=0;i<N;++i){
		coeff.push_back(va_arg(arguments, double) );
	}
	va_end( arguments );
}

Polynomial::Polynomial(vector<double > temp) : degree(temp.size()),coeff(temp){
};

void Polynomial::roundToPow(unsigned N){
	if(degree >= N ) return;
	else {
		for(unsigned n=degree;n<N;++n){
			coeff.push_back(0.0);
		}
		degree = N;
	}
}

ostream& operator<< ( ostream& os, Polynomial& a){
	if(a.degree<=0) {
		os<<"[Polynomial is empty]";
		return os;
	}
        bool flag=false;
	for(unsigned i=0;i<a.degree;++i){
                if(a.coeff[i]<=epsilon){
                        a.coeff[i]=0;
                        continue;
                }
		if(flag)os<<" + ";
		os<<"("<<a.coeff[i]<<")";
                flag=true;
		if(i>1)os<<"x^"<<i;
		else if(i==1)cout<<"x";
	}
	return os;
}
	
Polynomial& Polynomial::mult(Polynomial& other){
	vector<double> product(degree + other.degree - 1,0.0);
	for(unsigned int i=0;i<degree;++i){
		for(unsigned j=0;j<other.degree;++j){
			product[i+j] += coeff[i]*other.coeff[j];
		}
	}
	return *(new Polynomial(product));
}

Polynomial& Polynomial::FFTmult(Polynomial& other){
        unsigned ans_deg = degree + other.degree - 1;
        unsigned padd = 1;
	while(padd < ans_deg)
    		padd<<=1;
        roundToPow(padd);
        other.roundToPow(padd);
        vector<double> *t1=new vector<double>(coeff);
        vector<double> *t2=new vector<double>(other.coeff);
        vector<complex<double> > v1(FFT(t1));
        vector<complex<double> > v2(FFT(t2));
 
        vector<complex<double> > *v=new vector<COMPLEX>;
        for(size_t i = 0;i < v1.size() && i<v2.size();i++){
               v->push_back(v1[i]*v2[i]);
        } 
        
        vector<complex<double> > a(invFFT(v));
	vector<double> product;

        for(size_t i=0; i <= ans_deg;i++)
                product.push_back(a[i].real()/a.size());              //NOTE a.size() will not be (ans_deg + 1)

	return *(new Polynomial(product));
}


vector<COMPLEX > Polynomial::FFT(vector<double> *in){

        unsigned int n = in->size();
	if(n == 1 ){
                return vector<complex<double> >(1,(COMPLEX((*in)[0])));
        }
	complex<double> w = COMPLEX(1.0);
	complex<double> wn = polar(1.0,2*PI/n);
	vector<double > odd, even;
        for(unsigned i=0,j=1; (i<n) && (j<n); i+=2,j+=2){
                even.push_back((*in)[i]);
                odd.push_back((*in)[j]);
        }
        vector< complex<double> > y0 = FFT(&even);
        vector< complex<double> > y1 = FFT(&odd);
        
        vector< complex<double> > y(n,0);
        for(unsigned k=0; k < n/2 ; k++){
                y[k] = y0[k] + w*y1[k];
                y[k + n/2] =  y0[k]  - w*y1[k];
                w = w * wn;   
        }
        return y;

}

vector<COMPLEX> Polynomial::invFFT(vector<COMPLEX> *in){
        unsigned int n = in->size();
	if(n == 1 ){
                return *in;
        }
	complex<double> w = COMPLEX(1.0);
	complex<double> wn = polar(1.0,-2*PI/n);
	vector<COMPLEX> odd, even;
        for(unsigned i=0,j=1; (i<n) && (j<n); i+=2,j+=2){
                even.push_back((*in)[i]);
                odd.push_back((*in)[j]);
        }
        vector<COMPLEX> y0 = invFFT(&even);
        vector<COMPLEX> y1 = invFFT(&odd);
        
        vector< complex<double> > v(n,0);
        for(unsigned k=0; k < n/2 ; k++){
                v[k] = y0[k] + w*y1[k];
                v[k + n/2] =  y0[k]  - w*y1[k];
                w = w * wn;   
        }
        return v;

}

//int main(){
//
//	Polynomial another=Polynomial(9,2.0,0.0,7.0,11.0,18.0,0.0,9.0,1023.0);
//	Polynomial _2=Polynomial(1,2.0);
//	Polynomial test1=Polynomial(2,1.0,2.0);
//	Polynomial test2=Polynomial(2,1.0,2.0);
//	Polynomial prod1=test1.mult(test2);
//	Polynomial prod2=test1.FFTmult(test2);
//	cout<<"The polynomial is "<<prod1<<endl;
//	cout<<"The FFT polynomial is "<<prod2<<endl;
//	prod1=another.mult(_2);
//        prod2=another.FFTmult(_2);
//	cout<<"The polynomial is "<<prod1<<endl;
//	cout<<"The FFT polynomial is "<<prod2<<endl;
//        return 0;
//
//}

