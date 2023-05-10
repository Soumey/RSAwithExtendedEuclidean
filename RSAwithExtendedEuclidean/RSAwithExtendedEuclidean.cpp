#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;


int extended_gcd(long a, long b, long& x, long& y);
void rsa(string message);
int mod_pow(long base, long exp, long modulus);
int main() {
    
    string message = "";
    cout << "Welcom in RSA algorithm, give me an message to encrypt:\n";
    getline(cin, message);
    rsa(message);
    return 0;
}
// a ^ -1 mod m
int extended_gcd(long a, long b, long& x, long& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    long x1, y1;
    long gcd = extended_gcd(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}
int mod_pow(long base, long exp, long modulus) {
    long result = 1;
    base = base % modulus;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % modulus;
        }
        exp = exp >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

void rsa(string message) {
    
    long p = 23;
    long q = 67;

    // n & phi(n)
    long n = p * q;
    long phi = (p - 1) * (q - 1);

    // public key
    long e = 65537;
    long x, y;
    extended_gcd(e, phi, x, y);

    // d
    long d;
    extended_gcd(e, phi, d, y);
    while (d < 0) {
        d += phi;
    }

    //RSA
    cout << "p: " << p << endl;
    cout << "q: " << q << endl;
    cout << "n: " << n << endl;
    cout << "phi(n): " << phi << endl;
    cout << "e: " << e << endl;
    cout << "d: " << d << endl;

    // Msg -> Ascii
    vector<long> ascii_codes;
    for (int i = 0; i < message.length(); i++) {
        ascii_codes.push_back(long(message[i]));
    }
    

    cout << "Message:" << message << endl;

    
    cout << "Not encrypted message: ";
    for (int i = 0; i < ascii_codes.size(); i++) {
        cout << ascii_codes[i] << " ";
    }
    cout << endl;

    //Encrypt
    vector<long> encrypted_codes;
    for (int i = 0; i < ascii_codes.size(); i++) {
        long code = ascii_codes[i];
        long encrypted_code = 1;
        for (int j = 0; j < e; j++) {
            encrypted_code = (encrypted_code * code) % n;
        }
        encrypted_codes.push_back(encrypted_code);
    }

    
    cout << "Encrypted message: ";
    for (int i = 0; i < encrypted_codes.size(); i++) {
        cout << encrypted_codes[i] << " ";
    }
    cout << endl;

    //Decrypt
    vector<long> decrypted_codes;
    for (int i = 0; i < encrypted_codes.size(); i++) {
        long encrypted_code = encrypted_codes[i];
        //int decrypted_code = int(pow(encrypted_code, d)) % n;
        long decrypted_code = mod_pow(encrypted_code, d, n);
        decrypted_codes.push_back(decrypted_code);
    }
    
    cout << "Decrypted message: ";
    for (int i = 0; i < decrypted_codes.size(); i++) {
        cout << decrypted_codes[i] << " ";
        
    }
    cout << endl;

    // Decrypted ascii -> Message
    string decrypted_message = "";
    for (int i = 0; i < decrypted_codes.size(); i++) {
        char character = char(decrypted_codes[i]);
        decrypted_message += character;
    }

    cout << "Decrypted message " << decrypted_message << endl;
}