#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <cstdint>

void aes_128_encrypt(const uint8_t* plain_text, const uint8_t* key, uint8_t* ciphertext);
void aes_192_encrypt(const uint8_t* plain_text, const uint8_t* key, uint8_t* ciphertext);
void aes_256_encrypt(const uint8_t* plain_text, const uint8_t* key, uint8_t* ciphertext);

#endif