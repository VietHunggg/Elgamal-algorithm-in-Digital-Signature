#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX 100

int FastExponentiation(int x, int powr, int mod) {
    //check the condition of decimal power
    int base = x;
    if (powr == 0) return 1;

    /** 
        Change power to binary 
    **/ 
    // Guess the size of binary array              
    int Bi_len = (log2(powr) + 1);
    int binary[Bi_len];
    // start change power from decimal to binary 
    for (int i=0; i < Bi_len; i++){
        binary[i] = powr%2;
        powr = powr/2;
    }      
    // print the binary of power 
    cout << "The binary of: ";
    for (int i=0; i < Bi_len; i++){
        cout << binary[i];
    }

    /** Fast exponentiation:
            if idx = 0 --> Square
            if idx = 1 --> Multiplay current result with x by x is executed previous Squaring
     **/
    for (int idx = 0; idx < Bi_len; idx++){
        if (binary[idx] == 0){
            x = (x*x) % mod; 
        }
        else if (binary[idx] == 1){
            x = (((x*x) % mod) * base) % mod;
        }
    }
    cout << "\n" << x;
    return x;
}

int main(){
    int x, powr, mod;
    cout << "input x: "; 
    cin >> x;
    cout << "input pow: ";
    cin >> powr;
    cout << "input mod: ";
    cin >> mod;
    FastExponentiation(x, powr, mod);

    return 0;
}