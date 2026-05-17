
<div align="center">

<br/>

```
 █████╗ ███████╗███████╗
██╔══██╗██╔════╝██╔════╝
███████║█████╗  ███████╗
██╔══██║██╔══╝  ╚════██║
██║  ██║███████╗███████║
╚═╝  ╚═╝╚══════╝╚══════╝
```

### Advanced Encryption Standard
<br/>

[![Language](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=cplusplus)](https://isocpp.org/) [![Build](https://img.shields.io/badge/CMake-3.16+-064F8C?style=flat-square&logo=cmake)](https://cmake.org/) [![License](https://img.shields.io/badge/License-MIT-brightgreen?style=flat-square)](LICENSE) [![AES-128](https://img.shields.io/badge/AES--128-✓-blueviolet?style=flat-square)]() [![AES-192](https://img.shields.io/badge/AES--192-✓-blueviolet?style=flat-square)]() [![AES-256](https://img.shields.io/badge/AES--256-✓-blueviolet?style=flat-square)]()

</div>

---


## Table of Contents

- [Overview](#overview)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation](#installation)
- [API Reference](#api-reference)
- [Usage](#usage)
  - [AES-128 Encrypt](#aes-128--encrypt)
  - [AES-128 Decrypt](#aes-128--decrypt)
  - [AES-192 Encrypt](#aes-192--encrypt)
  - [AES-192 Decrypt](#aes-192--decrypt)
  - [AES-256 Encrypt](#aes-256--encrypt)
  - [AES-256 Decrypt](#aes-256--decrypt)
- [License](#license)

---

## Overview

This library implements the **FIPS 197** AES specification supporting all three standardized key lengths. Each function encrypts or decrypts a single **16-byte (128-bit) block**.

| Variant  | Key length | Rounds | Block size |
|----------|-----------|--------|------------|
| AES-128  | 128 bits (16 bytes) | 10 | 128 bits |
| AES-192  | 192 bits (24 bytes) | 12 | 128 bits |
| AES-256  | 256 bits (32 bytes) | 14 | 128 bits |

---

## Project Structure

```
AES/
├── include/
│   ├── encrypt.h          # Public encryption API
│   └── decrypt.h          # Public decryption API
├── src/
│   └── *.cpp              # AES core implementation
├── CMakeLists.txt          # Build configuration (CMake 3.16+, C++17)
├── LICENSE                 # MIT License
└── README.md
```

---

## Requirements

| Dependency | Version | Notes |
|-----------|---------|-------|
| C++ compiler | C++17 | GCC 7+, Clang 5+, MSVC 2017+ |
| CMake | 3.16+ | Build system |

No external libraries required.

---

## Installation

### Clone and build

```bash
git clone https://github.com/Drbsy/AES.git
cd AES

mkdir build && cd build
cmake ..
make
```

The binary `AES_Tool` is output to `build/`.

### Integrate into your project

Add to your `CMakeLists.txt`:

```cmake
add_subdirectory(path/to/AES)

target_include_directories(your_target PRIVATE path/to/AES/include)
target_sources(your_target PRIVATE
    path/to/AES/src/encrypt.cpp
    path/to/AES/src/decrypt.cpp
)
```

---

## API Reference

### Headers

```cpp
#include "encrypt.h"   // aes_128/192/256_encrypt
#include "decrypt.h"   // aes_128/192/256_decrypt
```

### Function signatures

```cpp
// AES-128  (key: 16 bytes)
void aes_128_encrypt(const uint8_t* plaintext,  const uint8_t* key, uint8_t* ciphertext);
void aes_128_decrypt(const uint8_t* ciphertext, const uint8_t* key, uint8_t* plaintext);

// AES-192  (key: 24 bytes)
void aes_192_encrypt(const uint8_t* plaintext,  const uint8_t* key, uint8_t* ciphertext);
void aes_192_decrypt(const uint8_t* ciphertext, const uint8_t* key, uint8_t* plaintext);

// AES-256  (key: 32 bytes)
void aes_256_encrypt(const uint8_t* plaintext,  const uint8_t* key, uint8_t* ciphertext);
void aes_256_decrypt(const uint8_t* ciphertext, const uint8_t* key, uint8_t* plaintext);
```

### Parameters

| Parameter    | Type           | Direction | Size             | Description              |
|-------------|----------------|-----------|------------------|--------------------------|
| `plaintext`  | `uint8_t*`     | in        | 16 bytes         | Input block to encrypt   |
| `ciphertext` | `uint8_t*`     | in / out  | 16 bytes         | Encrypted output block   |
| `key`        | `uint8_t*`     | in        | 16 / 24 / 32 B   | Secret key               |

> All buffers must be exactly **16 bytes**. The key buffer must match the variant (16 / 24 / 32 bytes). No return value; output is written directly to the output buffer.

---

## Usage

### AES-128 · Encrypt

```cpp
#include "encrypt.h"

uint8_t key[16] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f
};
uint8_t plaintext[16] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f
};
uint8_t ciphertext[16] = {0};

aes_128_encrypt(plaintext, key, ciphertext);
```

---

### AES-128 · Decrypt

```cpp
#include "decrypt.h"

uint8_t key[16] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f
};
uint8_t ciphertext_in[16] = {
    0x0a, 0x94, 0x0b, 0xb5,
    0x41, 0x6e, 0xf0, 0x45,
    0xf1, 0xc3, 0x94, 0x58,
    0xc6, 0x53, 0xea, 0x5a
};
uint8_t plaintext[16] = {0};

aes_128_decrypt(ciphertext_in, key, plaintext);
```

---

### AES-192 · Encrypt

```cpp
#include "encrypt.h"

uint8_t key[24] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17
};
uint8_t plaintext[16] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f
};
uint8_t ciphertext[16] = {0};

aes_192_encrypt(plaintext, key, ciphertext);
```

---

### AES-192 · Decrypt

```cpp
#include "decrypt.h"

uint8_t key[24] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17
};
uint8_t ciphertext_in[16] = {
    0x0a, 0x94, 0x0b, 0xb5,
    0x41, 0x6e, 0xf0, 0x45,
    0xf1, 0xc3, 0x94, 0x58,
    0xc6, 0x53, 0xea, 0x5a
};
uint8_t plaintext[16] = {0};

aes_192_decrypt(ciphertext_in, key, plaintext);
```

---

### AES-256 · Encrypt

```cpp
#include "encrypt.h"

uint8_t key[32] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b,
    0x1c, 0x1d, 0x1e, 0x1f
};
uint8_t plaintext[16] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f
};
uint8_t ciphertext[16] = {0};

aes_256_encrypt(plaintext, key, ciphertext);
```

---

### AES-256 · Decrypt

```cpp
#include "decrypt.h"

uint8_t key[32] = {
    0x00, 0x01, 0x02, 0x03,
    0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b,
    0x1c, 0x1d, 0x1e, 0x1f
};
uint8_t ciphertext_in[16] = {
    0x0a, 0x94, 0x0b, 0xb5,
    0x41, 0x6e, 0xf0, 0x45,
    0xf1, 0xc3, 0x94, 0x58,
    0xc6, 0x53, 0xea, 0x5a
};
uint8_t plaintext[16] = {0};

aes_256_decrypt(ciphertext_in, key, plaintext);
```

---

## License

```
MIT License

Copyright (c) 2026 Drbsy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
```


