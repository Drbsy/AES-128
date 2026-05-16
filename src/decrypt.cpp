#include "decrypt.h"
#include "key_expansion.h"
#include "round_operations.h"

#include <cstring>

void aes_128_decrypt(const uint8_t* ciphertext, const uint8_t* key, uint8_t* plain_text){

    if (!plain_text || !key || !ciphertext) return;

    uint8_t state[16];
    memcpy(state, ciphertext, 16);

    AES_128 aes(key);
    uint8_t round_key[16];

    // Inv Round : 10
    aes.get_round_key(10, round_key);
    add_round_key(state, round_key);
    inv_shift_rows(state);
    inv_substitute_bytes(state);

    // Inv Round : 9 -> 1
    for (int round = 9; round >= 1; round--) {
        aes.get_round_key(round, round_key);
        add_round_key(state, round_key);
        inv_mix_columns(state);
        inv_shift_rows(state);
        inv_substitute_bytes(state);
    }
    
    // Inv Round : 0
    aes.get_round_key(0, round_key);
    add_round_key(state, round_key);
    
    memcpy(plain_text, state, 16);

    volatile uint8_t* wipe = state;
    for (int i = 0; i < 16; i++) wipe[i] = 0;
 
    volatile uint8_t* wipe_rk = round_key;
    for (int i = 0; i < 16; i++) wipe_rk[i] = 0;

}

void aes_192_decrypt(const uint8_t* ciphertext, const uint8_t* key, uint8_t* plain_text){

    if (!plain_text || !key || !ciphertext) return;

    uint8_t state[16];
    memcpy(state, ciphertext, 16);

    AES_192 aes(key);
    uint8_t round_key[16];

    // Inv Round : 12
    aes.get_round_key(12, round_key);
    add_round_key(state, round_key);
    inv_shift_rows(state);
    inv_substitute_bytes(state);

    // Inv Round : 11 -> 1
    for (int round = 11; round >= 1; round--) {
        aes.get_round_key(round, round_key);
        add_round_key(state, round_key);
        inv_mix_columns(state);
        inv_shift_rows(state);
        inv_substitute_bytes(state);
    }
    
    // Inv Round : 0
    aes.get_round_key(0, round_key);
    add_round_key(state, round_key);
    
    memcpy(plain_text, state, 16);

    volatile uint8_t* wipe = state;
    for (int i = 0; i < 16; i++) wipe[i] = 0;
 
    volatile uint8_t* wipe_rk = round_key;
    for (int i = 0; i < 16; i++) wipe_rk[i] = 0;

}

void aes_256_decrypt(const uint8_t* ciphertext, const uint8_t* key, uint8_t* plain_text){

    if (!plain_text || !key || !ciphertext) return;

    uint8_t state[16];
    memcpy(state, ciphertext, 16);

    AES_256 aes(key);
    uint8_t round_key[16];

    // Inv Round : 14
    aes.get_round_key(14, round_key);
    add_round_key(state, round_key);
    inv_shift_rows(state);
    inv_substitute_bytes(state);

    // Inv Round : 13 -> 1
    for (int round = 13; round >= 1; round--) {
        aes.get_round_key(round, round_key);
        add_round_key(state, round_key);
        inv_mix_columns(state);
        inv_shift_rows(state);
        inv_substitute_bytes(state);
    }
    
    // Inv Round : 0
    aes.get_round_key(0, round_key);
    add_round_key(state, round_key);
    
    memcpy(plain_text, state, 16);

    volatile uint8_t* wipe = state;
    for (int i = 0; i < 16; i++) wipe[i] = 0;
 
    volatile uint8_t* wipe_rk = round_key;
    for (int i = 0; i < 16; i++) wipe_rk[i] = 0;

}
