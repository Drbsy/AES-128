#ifndef DECRYPT_H
#define DECRYPT_H

#include <cstdint>

void aes_128_decrypt(const uint8_t* ciphertext, const uint8_t* key, uint8_t* plain_text);

#endif