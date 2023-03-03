#include<iostream>
#include<cstdlib>
using namespace std;
int main(int argc , char *argv[]){

    float sum=0 , avrg;
    if(argc < 2){
        cout << "Please input numbers to find average.";
    }
    else{
        for(int i=0; i < argc-1 ; i++){
            sum += atof(argv[i+1]);
        }
        avrg = sum / (argc-1);

        cout << "---------------------------------\n";
        cout <<"Average of " << argc-1 << " numbers = " << avrg;
        cout << "\n---------------------------------";
    }
}

