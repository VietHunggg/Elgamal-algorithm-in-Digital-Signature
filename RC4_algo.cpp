#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

// define the size of each LFSRs and define the single keystrem bits
#define SIZEX 19
#define SIZEY 22
#define SIZEZ 23
#define BITS 9

// key stream generation functions depends on XOR operation
int maj(int x, int y, int z) {
    int XOR;
    if (x == 0){
        if (y == 0 || z == 0){
            XOR = 0;
        }
        else XOR = 1;
    }
    else {
        if (y == 1 || z == 1){
            XOR = 1;
        }
        else XOR = 0;
    }
    return XOR;
}

int main(){
    // input the information of each LFSR
    int x[SIZEX] = {0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
    int y[SIZEY] = {1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1};
    int z[SIZEZ] = {1,1,0,1,0,0,0,1,1,0,1,0,0,0,1,1,0,1,0,0,0,1,1};

    int m;
    int i,j = 0;

    for (i = 0; i < BITS; i++) {
        // use maj funtion above to check each case in A5/1 ( x[8] = m or y[10] = m or z[10] = m )
        m = maj(x[8], y[10], z[10]);
        
        // X steps: if x[0] = X[13] xor x[16] xor x[17] xor x[18] --> x[j] = x[j-1] 
        cout << "\nX: ";
        if (x[8] == m){
            int x0 = x[13]^x[16]^x[17]^x[18];
            for (j = SIZEX - 1; j >= 0; j--){
                if (j == 0) x[j] = x0;
                else x[j] = x[j-1];
            }
        }
        // print new X stream that be generated
        for (j = 0; j < SIZEX; j++){
            cout << x[j];
        }
        
        // Y steps: if y[0] = y[20] xor y[21] --> y[j] = y[j-1]
        cout << "\nY: ";
        if (y[10] == m){
            int y0 = y[20]^y[21];
            for (j = SIZEY - 1; j >= 0; j--){
                if (j == 0) y[j] = y0;
                else y[j] = y[j-1];
            }
        }
        // print new Y stream that be generated
        for(j = 0; j < SIZEY; j++){
            cout << y[j];
        }
        
        // Z steps: if z[7] xor z[20] xor x[21] xor x[22] --> z[j] = z[j-1]
        cout << "\nZ: ";
        if (z[10] == m){
            int z0 = z[7]^z[20]^z[21]^z[22];
            for (j = SIZEZ -1; j >= 0; j--){
                if (j == 0) z[j] = z0;
                else z[j] = z[j-1];
            }
        }
        // print new Z stream that be generated
        for (j = 0; j < SIZEZ; j++){
            cout << z[j];
        }
        
        // use XOR to generate the keystreams bits
        if (i < 8){
            int key = x[SIZEX-1]^y[SIZEY-1]^z[SIZEZ-1];
            cout << "\nKeystreambit: " << x[SIZEX-1] << " " << y[SIZEY-1] << " " << z[SIZEZ-1] << " " << "= " << key << endl;
        }
    }
    
        

}