#include <iostream>
#include <ctime>
using namespace std;

class Timer {
        private:
                unsigned long begTime;
        public:
                Timer(){
                        begTime = 0;
                }
                void start() {
                        begTime = clock();
                }
                
                void stop() {
                        begTime = 0;
                }

                float elapsedTime() {
                        unsigned long temp = (unsigned long)(clock() - begTime) ;
                        return temp*1.0/CLOCKS_PER_SEC;
                }

                bool isTimeout(unsigned long seconds) {
                        return seconds >= elapsedTime();
                }
};


//int main() {
//        cout<< CLOCKS_PER_SEC;
//        unsigned long seconds = 1;
//        Timer t;
//        int i=1;
//        t.start();
//        cout << "timer started . . ." << endl;
//        while(true) {
//                if(t.elapsedTime() >= seconds) {
//                        break;
//                }
//                else {
//                        cout<<t.elapsedTime()<<endl;
//                }
//        }
//        cout << seconds <<  " seconds elapsed" << endl;
//        return 0;
//}
