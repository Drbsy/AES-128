#include "key_expansion.h"
#include "common.h"



static const uint8_t Rcon[10]{
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

AES_128::AES_128(const uint8_t* master_key) {
    expand_key(master_key);
}

AES_192::AES_192(const uint8_t* master_key){
    expand_key(master_key);
}

AES_256::AES_256(const uint8_t* master_key){
    expand_key(master_key);
}

AES_128::~AES_128() {
    volatile uint8_t* p = round_keys;
    for (int i = 0; i < 176; i++) p[i] = 0;
}

AES_192::~AES_192() {
    volatile uint8_t* p = round_keys;
    for (int i = 0; i < 208; i++) p[i] = 0;
}

AES_256::~AES_256(){
    volatile uint8_t* p = round_keys;
    for (int i = 0; i < 240; i++) p[i] = 0;
}


void AES_128::get_round_key(int round_num, uint8_t* out_key) const {
    if (!out_key) return;
    for (int i = 0; i < 16; i++) {
        out_key[i] = round_keys[round_num * 16 + i];
    }
}

void AES_192::get_round_key(int round_num, uint8_t* out_key) const { 
    if (!out_key) return;
    for (int i = 0; i < 16; i ++){
        out_key[i] = round_keys[round_num * 16 + i];
    }
}

void AES_256::get_round_key(int round_num, uint8_t* out_key) const {
    if (!out_key) return;
    for (int i = 0; i < 16; i++){
        out_key[i] = round_keys[round_num * 16 + i];
    }
}

void AES_128::expand_key(const uint8_t* root_key) {
    for (int i = 0; i < 16; i++){
        round_keys[i] = root_key[i];
    }

    int current_bytes = 16;
    
    
    while (current_bytes < 176){

        int i = current_bytes / 4;
        uint8_t temp[4];
        
        // Grap the last word
        for (int j = 0; j < 4; j++){
            temp[j] = round_keys[(i-1)*4 +j];
        }

        if (i % 4 == 0){
            
            // Rotate bytes to left by 1
            uint8_t first = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = first;


            // Substitute 
            for (int j = 0; j < 4; j++){
                temp[j] = s_box[temp[j]];
            }

            // XOR first byte with Rcon
            temp[0] ^= Rcon[i/4 -1];
        }

        //W[i] = W[i-4] XOR temp
        for (int j = 0; j < 4; j++){
            round_keys[current_bytes + j] = temp[j] ^ round_keys[(i-4)*4 + j];
        }

        volatile uint8_t* wipe_temp = temp;
        for (int k = 0; k < 4; k++) wipe_temp[k] = 0;

        current_bytes +=4;

    };
    
};

void AES_192::expand_key(const uint8_t* root_key) {
    for (int i = 0; i < 24; i++){
        round_keys[i] = root_key[i];
    }

    int current_bytes = 24;
    
    
    while (current_bytes < 208){

        int i = current_bytes / 4;
        uint8_t temp[4];
        
        // Grap the last word
        for (int j = 0; j < 4; j++){
            temp[j] = round_keys[(i-1)*4 +j];
        }

        if (i % 6 == 0){
            
            // Rotate bytes to left by 1
            uint8_t first = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = first;


            // Substitute 
            for (int j = 0; j < 4; j++){
                temp[j] = s_box[temp[j]];
            }

            // XOR first byte with Rcon
            temp[0] ^= Rcon[i/6 -1];
        }

        //W[i] = W[i-6] XOR temp
        for (int j = 0; j < 4; j++){
            round_keys[current_bytes + j] = temp[j] ^ round_keys[(i-6)*4 + j];
        }

        volatile uint8_t* wipe_temp = temp;
        for (int k = 0; k < 4; k++) wipe_temp[k] = 0;

        current_bytes +=4;

    };
};

void AES_256:: expand_key(const uint8_t* root_key){
    for (int i = 0; i < 32; i++){
        round_keys[i] = root_key[i];
    }

    int current_bytes = 32;
    
    while (current_bytes < 240){

        int i = current_bytes / 4;
        uint8_t temp[4];
        
        // Grap the last word
        for (int j = 0; j < 4; j++){
            temp[j] = round_keys[(i-1)*4 +j];
        }

        if (i % 8 == 0){
            
            // Rotate bytes toy left by 1
            uint8_t first = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = first;

        
            // Substitute 
            for (int j = 0; j < 4; j++){
                temp[j] = s_box[temp[j]];
            }

            // XOR first byte with Rcon
            temp[0] ^= Rcon[i/8 -1];
        }
        else if (i % 8 == 4){
            for (int j = 0; j < 4; j++){
                temp[j] = s_box[temp[j]];
            }
        }
        //W[i] = W[i-8] XOR temp
        for (int j = 0; j < 4; j++){
            round_keys[current_bytes + j] = temp[j] ^ round_keys[(i-8)*4 + j];
        }

        volatile uint8_t* wipe_temp = temp;
        for (int k = 0; k < 4; k++) wipe_temp[k] = 0;

        current_bytes +=4;

    };
};




