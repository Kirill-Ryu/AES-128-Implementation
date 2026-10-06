#include <iostream>
#include "header.hpp"
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <format>

typedef __int128_t int128;
using namespace std;
string hex128(unsigned __int128 n) {
    if (n == 0) return "0";
    string s = "";
    char hex_chars[] = "0123456789abcdef";
    while (n > 0) {
        s += hex_chars[n % 16];
        n /= 16;
    }
    reverse(s.begin(), s.end());
    return "0x" + s;
}



int main(){

    __int128_t key = (__int128_t)0xa2e2fa9baf7d2082ULL << 64 | 0x2ca9f0542f764a41ULL;
    __int128_t plaintext = (__int128_t) 0x00ULL << 64 | 0x00ULL;

    cout << "Plaintext : " << hex128(plaintext) << endl;
    cout << "Key : " << hex128(key) << endl;
    AES128(plaintext, key);




    //const int iterations = 10;
    //auto start = std::chrono::high_resolution_clock::now();
    //for(int i = 0; i < iterations; i++){
    //    AES128(plaintext, key);
    //}
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> diff = end - start;
    //std::cout << "Total Time : " << diff.count() << "s" << std::endl;
    //std::cout << "Average Time per call : " << (diff.count() / iterations) << "s" << std::endl;

    return 0;
}