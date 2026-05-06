#include "round_operations.h"
#include "common.h"
#include "mix_columns.h"



void add_round_key(uint8_t* state, const uint8_t* round_key){
    for (int i = 0; i <16 ; i++){
        state[i] ^= round_key[i];
    }
}


/*
    ######################
    ### ENCRYPT ROUNDS ###
    ######################
*/

int get_index(int col, int row ){
    return (col*4) + row;
}

void substitute_bytes(uint8_t* state){
    for (int i = 0; i < 16; i++){
        state[i] = s_box[state[i]];
    }
}

void shift_one_row(uint8_t* state, int row, int shift_amount){
    uint8_t temp[4];

    for (int col = 0; col < 4; col++){
        temp[col] = state[get_index((col + shift_amount) % 4, row)];
    }

    for (int i = 0; i < 4; i++){
        state[get_index(i, row)] = temp[i];
    }

}

void shift_rows(uint8_t* state){
    shift_one_row(state, 1, 1);
    shift_one_row(state, 2, 2);
    shift_one_row(state, 3, 3);
}

void mix_columns(uint8_t* state){
    uint8_t temp[16];
    
    for (int i = 0; i < 4; i++ ){
        uint8_t s0 = state[i * 4 + 0];
        uint8_t s1 = state[i * 4 + 1];
        uint8_t s2 = state[i * 4 + 2];
        uint8_t s3 = state[i * 4 + 3];

        temp[i * 4 + 0] = mc_2[s0] ^ mc_3[s1] ^ s2 ^ s3;
        temp[i * 4 + 1] = s0 ^ mc_2[s1] ^ mc_3[s2] ^ s3;
        temp[i * 4 + 2] = s0 ^ s1 ^ mc_2[s2] ^ mc_3[s3];
        temp[i * 4 + 3] = mc_3[s0] ^ s1 ^ s2 ^ mc_2[s3];
    }

    for (int i = 0; i < 16; i++) {
        state[i] = temp[i];
    }
}

/*
    #########################
    ### DECRYPT ROUNDS OP ###
    #########################
*/


void inv_shift_rows(uint8_t* state){
    uint8_t  temp[16];

    for (int i = 0; i < 16; i++) {
        temp[i] = state[i];
    }

    // Row 1: right shift by 1
    state[1] = temp[13];
    state[5] = temp[1];
    state[9] = temp[5];
    state[13] = temp[9];
    
    // Row 2: right shift by 2
    state[2] = temp[10];
    state[6] = temp[14];
    state[10] = temp[2];
    state[14] = temp[6];
    
    // Row 3: right shift by 3
    state[3] = temp[7];
    state[7] = temp[11];
    state[11] = temp[15];
    state[15] = temp[3];
}

void inv_substitute_bytes(uint8_t* state) {
    for (int i = 0; i < 16; i++) {
        state[i] = inv_s_box[state[i]];
    }
}

void inv_mix_columns(uint8_t* state) {
    uint8_t  temp[16];
    
    for (int col = 0; col < 4; col++) {
        uint8_t s0 = state[col * 4 + 0];
        uint8_t s1 = state[col * 4 + 1];
        uint8_t s2 = state[col * 4 + 2];
        uint8_t s3 = state[col * 4 + 3];
        
        temp[col * 4 + 0] = imc_0e[s0] ^ imc_0b[s1] ^ imc_0d[s2] ^ imc_09[s3];
        temp[col * 4 + 1] = imc_09[s0] ^ imc_0e[s1] ^ imc_0b[s2] ^ imc_0d[s3];
        temp[col * 4 + 2] = imc_0d[s0] ^ imc_09[s1] ^ imc_0e[s2] ^ imc_0b[s3];
        temp[col * 4 + 3] = imc_0b[s0] ^ imc_0d[s1] ^ imc_09[s2] ^ imc_0e[s3];
    }
    
    for (int i = 0; i < 16; i++) {
        state[i] = temp[i];
    }
}