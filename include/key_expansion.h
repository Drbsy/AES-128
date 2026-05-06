#ifndef KEY_EXPANSION_H          
#define KEY_EXPANSION_H          

#include <cstdint>

class AES_128{ 
    private:
        uint8_t round_keys[176];
        void expand_key(const uint8_t* root_key);
    public:
        AES_128(const uint8_t* master_key);
        ~AES_128();
        void get_round_key(int round_num,uint8_t* out_key);
};

#endif