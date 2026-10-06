#include <iostream>
#include "header.hpp"
#include <cstdint>

typedef __int128_t int128;
// Table for Sbox substitution procedure.

// Store 128 bit type Plaintext or Encryption Key into 4x4 array.
void int128to4x4(uint8_t array[4][4], unsigned __int128 TextorKey){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            array[j][i] = (TextorKey >> (8*(15-(i * 4 + j)))) & 0xff;
        }
    }
}

uint8_t sbox_table[16][16] = {
    {0x63, 0x7c, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16},

};

// substitude each byte in the state array using the Sbox table.
// Splited each bytes(a) into high nibbles(row) and low nibbles(col).
// and used the high and low nibbles as a row and column of Sbox table.
void SubBytes(uint8_t state[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            uint8_t a = state[i][j];
            uint8_t row = (a >> 4)&0x0f; //Upper nibble
            uint8_t col = a & 0x0f;      //Lower nibble
            state[i][j] = sbox_table[row][col];
        }
    }
}

// Rotate a single row left by one byte.
// variable num means row number
// used for ShiftRows
void Shitft1Byte(uint8_t state[4][4], int num){
    uint8_t temp = 0;
    temp = state[num][0];
    for(int i = 0; i < 3; i++){
        state[num][i] = state[num][i+1];
    }
    state[num][3] = temp;
}

// Scramble values of array for permutation transform
// using Shift1Byte()
void ShiftRows(uint8_t state[4][4]){
    Shitft1Byte(state, 1);
    Shitft1Byte(state, 2);
    Shitft1Byte(state, 2);
    Shitft1Byte(state, 3);
    Shitft1Byte(state, 3);
    Shitft1Byte(state, 3);
}

// {02} multiply for a byte.
// used for Mixcolumns().
uint8_t x2(uint8_t element){
    if (element & 0x80){
        return (element << 1) ^ 0x1b;
    }
    else{
    return element << 1;
    }
}
// {03} multiply for 1 byte.
// used for Mixcolumns().
uint8_t x3(uint8_t element){
    return x2(element)^element;
}
// Perform transformation using given equations.
void MixColumns(uint8_t state[4][4]){
    for(int i = 0; i < 4 ; i++){
        uint8_t a0 = state[0][i];
        uint8_t a1 = state[1][i];
        uint8_t a2 = state[2][i];
        uint8_t a3 = state[3][i];
        
        state[0][i] = x2(a0) ^ x3(a1) ^ a2 ^ a3;
        state[1][i] = a0 ^ x2(a1) ^ x3(a2) ^ a3;
        state[2][i] = a0 ^ a1 ^ x2(a2) ^ x3(a3);
        state[3][i] = x3(a0) ^ a1 ^ a2 ^ x2(a3);
    }
}

// This Rcon words table has used for g function.
// used this table instead of RC[j] = 2*RC[j-1] for comfort.
// used for Key Expansion
uint8_t Rcon_table[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

//used for Key expansion
void g(uint8_t words[4], int i){
    uint8_t temp = words[0];       // RotWord - rotate input word [a0, a1, a2, a3,] transformed to [a1, a2, a3, a0]
    for(int i = 0; i < 3; i++){
        words[i] = words[i+1];
    }
    words[3] = temp;

    for(int j = 0; j < 4; j++){     // Subword - substitude on each byte of its input word, using the AES S-box.
        uint8_t temp1 = words[j];
        uint8_t upper = (temp1 >> 4)&0x0f;
        uint8_t lower = temp1 & 0x0f;
        words[j] = sbox_table[upper][lower];
    }

    words[0] ^= Rcon_table[i];       // Rcon - XOR with a round constant and Rcon[i].
}

// generate round keys for every rounds.
void KeyExpansion(uint8_t key[4][4], uint8_t expanded_key[44][4]){
    for(int i = 0; i < 4; i++){      // Encryption Key is copied into the first four words of the expanded key.
        for(int j = 0; j < 4; j++){
            expanded_key[i][j] = key[j][i];
        }
    }
    for(int i = 4; i < 44; i++){   // and generate other keys for every rounds.
        uint8_t temp[4];          // use temp[4] for applying g function.
        for(int j = 0; j<4;j++){
            temp[j] = expanded_key[i-1][j];
        }
        if((i % 4) == 0){          // if the index of w[i] is multiples of 4, perform w[i] = w[i-4] XOR g(w[i-1])
            g(temp, i/4-1);
            for(int j = 0; j < 4; j++){   
                expanded_key[i][j] = expanded_key[i-4][j]^(temp[j]);
            }
        }
        else{                     // in other case, perform w[i] = w[i-4] XOR w[i-1]
            for(int j = 0; j < 4; j++){
                expanded_key[i][j] = expanded_key[i-4][j] ^ expanded_key[i-1][j];
            }
        }
    }
}

// the 128-bit state is bitwise XORed with the 128-bit round key.
void AddRoundKey(uint8_t state[4][4], uint8_t roundkey[4][4]){
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            state[i][j] ^= roundkey[i][j];
        }
    }
}

// Perform AES-128 algorithm.
void AES128(unsigned __int128 plaintext, unsigned __int128 key){
    uint8_t state[4][4];
    uint8_t key_array[4][4];
    uint8_t expanded_key[44][4];
    uint8_t temp[4][4];
    int128to4x4(state, plaintext);     //store plaintext and key into array
    int128to4x4(key_array, key);
    KeyExpansion(key_array,expanded_key);
    
    AddRoundKey(state, key_array);        // Key Whitening

    for(int i = 1; i<10; i++){   // Rounds 1~9
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        for(int k =0;k<4;k++){
        for(int j = 0; j<4;j++){
            temp[j][k] = expanded_key[i*4+k][j];  // use temp with the same way as Key whitening, considering each round has to use 4 bytes.
        }
    }
    AddRoundKey(state, temp);
    }

    for(int i = 0; i < 4; i++){         //use temp for AddRoundKey.
        for(int j = 0; j < 4; j++){
            temp[j][i] = expanded_key[40 + i][j];
        }
    }
        SubBytes(state);                 // Perform last round(no MixColumns).
        ShiftRows(state);
        AddRoundKey(state, temp);   
        std::cout<<"Ciphertext: ";       // Print result
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                printf("%02x", state[j][i]);
            }
        }
    std::cout<<std::endl;
}
