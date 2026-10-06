# AES-128 Implementation

## Project Overview
- **Objective:** To implement the Advanced Encryption Standard (AES) 128-bit symmetric-key algorithm from scratch to deeply understand its cryptographic principles and internal structure.
- **Context:** Academic project for Security for IoT Edge Network at Dublin City University, first semester.

## Development Environment
- **Language:** C++ (Utilized `__int128_t` for 128-bit processing)
- **OS:** Windows 10 (PowerShell)
- **Compiler/Tool:** GCC 15.2.0 (g++)

## Features & Scope
- **Key Size:** 128-bit (16 bytes)
- **Block Size:** 128-bit (16 bytes)
- **Block Cipher Mode:** Single Block Encryption (Base ECB)
- **Core Functions Implemented:**
  - `SubBytes()`
  - `ShiftRows()`
    - `Shift1Byte()`
  - `MixColumns()`
    - `x2()`
    - `x3()`
  - `AddRoundKey()`
  - `KeyExpansion()`
    - `g()`
  - `AES128()` (Main encryption wrapper function)

## How to Run
```powershell
# Navigate to the project directory
$ cd "path/to/AES-128/"

# Compile all .cpp files into an executable named 'main'
$ g++ *.cpp -o main

# Run the executable
$ .\main
