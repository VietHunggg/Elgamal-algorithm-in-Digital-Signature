#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

/**
    p: large prime number
    alpha: a primitive element of Z group
    d: random number from {2, 3,..., p - 2}
    beta: = alpha^d mod p

    kpub form: kpub = (p,alpha,beta)
    kpri form: kpri = d  
**/

int gcd(int x, int y){
    int tpm;
    while(1){
        tpm = x%y;
        if (tpm == 0){
            return y;
        }
        else {
            x = y;
            y = tpm;
        }
    }
}

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

double Random(int min, int max){
    return min + (int)(rand()*(max - min+1.0)/(1.0 + RAND_MAX));
}


void Elgamal(double p, double alpha){
    //double d = Random(2, p - 2);
    double d = 127;
    double msg = 8022;

    double ke = 215;
    
    /**
        Choose a random ephemeral key "ke" in {0,1,2,..., p - 2} <=> gcd(ke, p-1) = 1
    */
    while (ke <= p - 2){
        if (gcd(ke, p - 1) == 1){
            break;
        }
        else ke++;
    }
    
    // Key Generation for Elgamal Digital Signature
    double beta = FastExponentiation(alpha,d,p);
    
    /**
        r = alpha^ke mod p
        s = (msg - d*r) * ke^(-1) mod p - 1
        --> s = (x - d*r)/ke mod p - 1
    **/
    double r = FastExponentiation(alpha,ke,p);
    double s = fmod((msg - d*r)/ke, p - 1);


    /**
       Verification:
       t = beta^r * r*s mod p;
    **/
    double tpm = pow(beta, r) * pow(r,s);
    double t = fmod(tpm, p);

    double alphaPowX = FastExponentiation(alpha,msg,p);

    cout << "p: " << p << "\n";
    cout << "alpha: " << alpha << "\n";
    cout << "d: " << d << "\n";
    cout << "beta: " << beta << "\n";
    cout << "original message: " << msg << "\n";
    cout << "ke: " << ke << "\n";
    cout << "r: " << r << "\n";
    cout << "s: " << s << "\n";
    cout << "t: " << t << "\n";
    cout << "alpha power msg" << alphaPowX << "\n";
    if (t = alphaPowX){
        cout << "valid signature" << endl;
    }
}

int main(){
    double p, alpha;
    cout << "enter p"; cin >> p;
    cout << "enter alpha"; cin >> alpha;
    Elgamal(p, alpha);

    return 0;
}