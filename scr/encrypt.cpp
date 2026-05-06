#include "encrypt.h"
#include "key_expansion.h"
#include "round_operations.h"
#include <cstring>

void aes_128_encrypt(const uint8_t* plain_text, const uint8_t* key, uint8_t* ciphertext){
    
    if (!plain_text || !key || !ciphertext) return;
    
    uint8_t state[16];
    memcpy(state, plain_text, 16);

    AES_128 aes(key);
    uint8_t round_key[16];
    
    // Round : 0
    aes.get_round_key(0, round_key);
    add_round_key(state, round_key);

    // Round : 1 -> 9
    for (int round = 1; round <=9; round++){
        substitute_bytes(state);
        shift_rows(state);
        mix_columns(state);
        aes.get_round_key(round, round_key);
        add_round_key(state, round_key);
    }

    // Round : 10 
    substitute_bytes(state);
    shift_rows(state);
    aes.get_round_key(10, round_key);
    add_round_key(state, round_key);


    memcpy(ciphertext, state, 16);


    volatile uint8_t* wipe = state;
    for (int i = 0; i < 16; i++) wipe[i] = 0;
 
    volatile uint8_t* wipe_rk = round_key;
    for (int i = 0; i < 16; i++) wipe_rk[i] = 0;
}

