//
// Created by Igor on 09.10.2020.
//
#include "rna.h"
#include <stdio.h>
#include <iostream>
#include <math.h>

RNA:: RNA(){
    size = 0;
    capacity = 0;
    rna_str = nullptr;
};

RNA:: ~RNA(){
    delete rna_str;
}


uint8_t* RNA::skip_rna_blocks(uint8_t *rna, int32_t skip_val){
    *rna <<= 8*skip_val;
    return rna;
}

Nucls RNA::get_rna_block(uint8_t *rna, int32_t idx){

    return Nucls(0x03 & (rna[idx/4] >> 2*(3-idx%4)));
}

RNA::reference RNA::operator[](size_t num){

    size_t old_size = this->size;
    if(old_size == 0){
        old_size = 1;
    }

    if(num+1 > this->size){
        this->size = num+1;
    }
    if(this->rna_str == nullptr){
        this->rna_str = new uint8_t[(int32_t)ceil((double)this->size/4)];
    }
    if(this->size > this->capacity){
        if(this->capacity == 0){
            this->capacity = 1;
        }
        this->capacity = this->capacity*2;
        uint8_t *str_new = new uint8_t[(int32_t)ceil((double)this->capacity/4)];
        memcpy(str_new, this->rna_str, sizeof(uint8_t)*((int32_t)ceil((double)this->capacity/4)));
        delete[] this->rna_str;
        this->rna_str = str_new;

    }
    //
    // std:: cout << &this[num] << " ";
    return reference(num, this);
}


RNA::reference& RNA::reference::operator=(const Nucls nucl){

    int8_t indoor_move = 4-1 - this->num%4;
    this->rna->rna_str[this->num/4] &= (0xFF- (0x03 << 2*indoor_move));
    this->rna->rna_str[this->num/4] |= nucl << 2*indoor_move;

    return *this;
}

RNA::reference::operator Nucls(){
    return (Nucls)this->rna->get_rna_block(this->rna->rna_str, this->num);
}

RNA::reference& RNA::reference::operator=(reference& r1){

    return this->operator=((Nucls)r1);
}

bool RNA::reference::operator==(const reference & r1)const{
    if(this->rna->get_rna_block(this->rna->rna_str, this->num) == r1.rna->get_rna_block(r1.rna->rna_str, r1.num)){
        return true;
    }
    return false;
}
bool RNA::reference::operator==(const Nucls nucl)const{
    if(this->rna->get_rna_block(this->rna->rna_str, this->num) == nucl){
        return true;
    }
    return false;
}


RNA RNA::split(int32_t idx) {

        RNA new_rna;
        new_rna.size = this->size - idx;
        new_rna.capacity = this->capacity - idx;
        new_rna.rna_str = new uint8_t[(int32_t)ceil((double)new_rna.capacity/4)];

        memcpy(new_rna.rna_str, &this->rna_str[idx/4], sizeof(uint8_t) * (int32_t)ceil((double)new_rna.size / 4));

        int8_t move = idx % 4;
        if (move != 0) {
            for (int32_t i = 0; i < (int32_t)ceil((double)new_rna.size/4); ++i) {
                new_rna.rna_str[i] <<= 2 * move;
                if(i < (int32_t)ceil((double)new_rna.size/4)-1) {
                    new_rna.rna_str[i] |= new_rna.rna_str[i + 1] >> 2 * (4 - move);
                }
            }
        }


        return new_rna;
    }



RNA RNA::operator=(const RNA &r1){
    this->size = r1.size;
    this->capacity = r1.capacity;
    this->rna_str = new uint8_t[capacity/4+1];
    memcpy(this->rna_str, r1.rna_str, sizeof(uint8_t)*(r1.size/4+1));
    return *this;
}



RNA RNA::operator+ (const RNA & r1)const{

    RNA sum;
    sum.capacity = this->capacity + r1.capacity;
    sum.size = this->size + r1.size;
    sum.rna_str = new uint8_t[(int32_t)ceil((double)sum.capacity/4)];



    memcpy(sum.rna_str, this->rna_str, sizeof(uint8_t)*((int32_t)ceil((double)this->size/4)));
    memcpy(&sum.rna_str[(int32_t)ceil((double)this->size/4)], r1.rna_str, sizeof(uint8_t)*((int32_t)ceil((double)r1.size/4)));


    int8_t rest = this->size%4;
    int32_t first_len = this->size/4;
    if(rest != 0) {

        sum.rna_str[first_len] |= sum.rna_str[first_len+1] >> 2*rest;
        for (int32_t i = first_len+1; i < (int32_t)ceil((double)sum.size / 4 - 1); i++) {
            sum.rna_str[i] = sum.rna_str[i] << 2*(4 - rest);
            sum.rna_str[i] |= sum.rna_str[i+1] >> 2*rest;
        }
        sum.rna_str[(int32_t)ceil((double)sum.size/4)] = sum.rna_str[(int32_t)ceil((double)sum.size/4)] << 2*(4 - rest);
    }


    return sum;
}

bool RNA::operator== (const RNA & r1) const{

    for (int32_t i = 0; i < this->size/4; i++){
        if(this->rna_str[i] != r1.rna_str[i]){
            return false;
        }
    }
    return true;

};
bool RNA::operator!= (const RNA & r1)const{
    if(this->size != r1.size){
        return true;
    }
    for (int32_t i = 0; i < this->size/4+1; i++){
        if(this->rna_str[i] != r1.rna_str[i]){
            return true;
        }
    }
    return false;

}

RNA RNA::operator! ()const{
    RNA r1 = *this;

    for (int32_t i=0; i < (int32_t)ceil((double)r1.size/4); i++) {
        r1.rna_str[i] = ~r1.rna_str[i];
    }

    // Обнуление хвоста последнего байта
    r1.rna_str[r1.size/4] >>= 2*(4 - r1.size%4);
    r1.rna_str[r1.size/4] <<= 2*(4 - r1.size%4);

    return r1;
}


bool RNA::is_complementary(const RNA& new_rna)const{
    if (*this == !new_rna){
        return true;
    }
    return false;
}



