

# AES

I built this AES implementation to strengthen my understanding of cryptography and to integrate it into my password manager.

---

# Usage

This AES implementation provides 2 main functions for evry AES (128-192-256).

---

## 1. Encryption Function (AES 128) as example :

### Header file
```c
#include "encrypt.h"

```

### Function

```cpp
aes_128_encrypt(plaintext, key, ciphertext);

```

### Example usage

```cpp
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

----------

## 2. Decryption Function

### Header file

```cpp
#include "decrypt.h"

```

### Function

```cpp
aes_128_decrypt(ciphertext, key, plaintext);

```

### Example usage

```cpp
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
