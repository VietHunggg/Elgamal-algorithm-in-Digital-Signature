#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

/** 
    p, q: co-prime number
    M: message to encrypt and decrypt
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

void RSA(double p, double q, double M){
    double e, phi_n, n;
    n = p*q;
    phi_n = (p-1)*(q-1);
    // Case choose e = 3
    e = 3;

    const double k = 2;

    /**
        Find gcd to check and find e satisfy with condidtion gcd(e,phi_n) = 1 
    **/
    while (e < phi_n){
        if (gcd(e, phi_n) == 1){
            break;
        }
        else e++;
    }
    
    /** Generate private key
        we have d*e = mod phi(n)
        --> d = e^-1 = mod phi(n)
    **/   
   double d = fmod(1/e, phi_n);

   // public key
   cout << "Public key: k(pub) = " << "(" << n << "," << e << ")" << "\n"; 

   // Encryt: y = m^e mode n 
   // --> y = (m^e)%n
   double E = pow(M,e); 
   
   // Decrypt: y^d = x mod n 
   // --> x = y^d mod n
   // --> x = (y^d)%n 
   double D = pow(E, d);
   
   E = fmod(E,n);
   D = fmod(D,n);
   
   cout << "\nAfter encrypted: " << E << "\n";
   cout << "After decrypted: " << D << "\n";
}

int main(){
    double p,q,M;
    cout << "Enter prime number p: "; cin >> p;
    cout << "Enter prime number q: "; cin >> q; 
    cout << "Enter message M: "; cin >> M;
    
    RSA(p,q,M);
    

    return 0;
}