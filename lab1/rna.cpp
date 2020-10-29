//
// Created by Igor on 09.10.2020.
//
#include "rna.h"
#include <stdio.h>
#include <iostream>

int8_t* RNA::skip_rna_blocks(int8_t *rna, int skip_val){
    *rna <<= 8*skip_val;
    return rna;
}

Nucls RNA::get_rna_block(int8_t *rna, int idx){

    return Nucls(0x03 & (rna[idx/4] >> 2*(3-idx%4)));
}

RNA::reference RNA::operator[](int8_t num){

    if(num > this->size){
        this->size = num;
    }
    if(this->size > this->capacity){
        int8_t* new_rna = new int8_t[sizeof(int8_t)*this->capacity*2];
        for (int i = 0; i < this->capacity/4+1; i++){
            new_rna[i] = this->rna_str[i];
        }
        delete this->rna_str;
        this->rna_str = new_rna;
        this->capacity = this->capacity*2;
    }
    return reference(num, this);
}


RNA::reference& RNA::reference::operator=(const Nucls nucl){

    short indoor_move = 4-1 - this->num%4;
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
    std:: cout << this->rna->get_rna_block( this->rna->rna_str, this->num);
    std:: cout << ' '  << r1.rna->get_rna_block(r1.rna->rna_str, r1.num) << '\n';
    if(this->rna->get_rna_block(this->rna->rna_str, this->num) == r1.rna->get_rna_block(r1.rna->rna_str, r1.num)){
        return true;
    }
    return false;
}
bool RNA::reference::operator==(const Nucls nucl)const{
    std:: cout << this->rna->get_rna_block( this->rna->rna_str, this->num);
    std:: cout << " " << nucl << '\n';
    if(this->rna->get_rna_block(this->rna->rna_str, this->num) == nucl){
        return true;
    }
    return false;
}


RNA RNA::split(int8_t idx) {
    RNA new_rna;
    new_rna.size = this->size - idx;
    new_rna.capacity = this->capacity - idx;
    new_rna.rna_str = new int8_t[new_rna.capacity/4+1];

    int full_mv = idx/4;

    memcpy(new_rna.rna_str, &this->rna_str[full_mv], sizeof(int8_t)*(capacity/4+1));

    short move = idx % 4;
    if(move!=0){
        for(int i = 0; i < new_rna.size/4+1; i++){
            if(i >= 1){
                new_rna.rna_str[i] = new_rna.rna_str[i] << 2*(move);
            }
            new_rna.rna_str[i] = new_rna.rna_str[i] >> 2*(4-1-move);
        }
    }
    return new_rna;
}



RNA RNA::operator+ (RNA & r1){
    if (this->size + r1.size == 0){
        return RNA();
    }
    std:: cout << "crash";

    RNA sum;
    sum.capacity = this->capacity + r1.capacity;
    sum.size = this->size + r1.size;
    sum.rna_str = new int8_t[sum.capacity*4+1];

    std:: cout << sum.capacity<< '\n';
    for(int i = 0; i < this->size; i++){
        std:: cout << i << " ";
        sum.operator[](i) = this->operator[](i);
    }
    std:: cout << "crash" << '\n';
    for(int i = 0; i < r1.size; i++){
        std:: cout << this->size+i << " ";
        sum.operator[](this->size+1+i) = r1.operator[](i);
    }
    std:: cout << "crash";
    return sum;

}
//rna=rna
bool RNA::operator== (const RNA & r1) const{
    if(this->size != r1.size){
        return false;
    }
    for (int i = 0; i < this->size/4+1; i++){
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
    for (int i = 0; i < this->size/4+1; i++){
        if(this->rna_str[i] != r1.rna_str[i]){
            return true;
        }
    }
    return false;

}

RNA RNA::operator! ()const{
    RNA r_new;

    r_new.capacity = this->capacity;
    r_new.size = r_new.size;
    r_new.rna_str = this->rna_str;

    for(int8_t i = 0; i < r_new.size/4+1; i++){
        r_new.rna_str[i] = ~r_new.rna_str[i];
    }
    if (r_new.size%4 > 0){
        r_new.rna_str[r_new.size/4+1] >>= (4-(r_new.size%4))*2;
        r_new.rna_str[r_new.size/4+1] = ~r_new.rna_str[r_new.size/4+1];
        r_new.rna_str[r_new.size/4+1] <<= (4-(r_new.size%4))*2;
    }

    return r_new;

}


bool RNA::is_complementary(const RNA& new_rna)const{
    return (*this == !new_rna);
}

RNA RNA::operator=(const RNA &r1){
    this->size = r1.size;
    this->capacity = r1.capacity;
    this->rna_str = new int8_t[capacity/4+1];
    memcpy(this->rna_str, r1.rna_str, sizeof(int8_t)*(r1.size/4+1));
    return *this;
}
