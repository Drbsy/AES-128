#ifndef ROUND_OPERATIONS_H
#define ROUND_OPERATIONS_H

#include <cstdint>

void add_round_key(uint8_t* state, const uint8_t* round_key);
void substitute_bytes(uint8_t* state);
void shift_rows(uint8_t* state);
void mix_columns(uint8_t* state);

void inv_shift_rows(uint8_t* state);
void inv_substitute_bytes(uint8_t* state);
void inv_mix_columns(uint8_t* state);

#endif