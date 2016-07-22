#include"polynomial.cpp"
#include"timer.cpp"
#include<cstdlib>
#include<sstream>

using namespace std;

int main(int argc,char **argv){

if(argc <= 1) return 0;

stringstream ss;
ss<<argv[1];
int N;
ss>>N;
vector<double > tempCoeff;
srand(time(NULL));
for(int i ; i<N; ++i){
        tempCoeff.push_back((double)(rand()));
}
Polynomial a(tempCoeff);
tempCoeff.erase(tempCoeff.begin(),tempCoeff.end());
for(int i ; i<N; ++i){
        tempCoeff.push_back((double)(rand()));
}
Polynomial b(tempCoeff);
//cout<<a<<endl;
//cout<<b<<endl;
Timer t;
t.start();
Polynomial c=a.FFTmult(b);
//cout<<c<<endl;
cout<<"Time elapsed in FFT mult = "<<t.elapsedTime()<<endl;
t.stop();
t.start();
Polynomial d=a.mult(b);
//cout<<d<<endl;
cout<<"Time elapsed in normal mult = "<<t.elapsedTime()<<endl;

return 0;
}

        
