//
// Created by Igor on 09.10.2020.
//
#include "rna.h"

size_t* RNA::skip_rna_blocks(size_t *rna, int skip_val){
    *rna >>= 8*skip_val;
    return rna;
}

int RNA::get_rna_block(size_t *rna, int idx){
    int skip_val = idx / 4;
    int idx_remain = idx % 4;
    if(idx_remain < 0 || idx_remain > 3){
        exit(0);
    }

    rna = skip_rna_blocks(rna, skip_val);

    *rna >>= 2*(3-idx_remain);
    return (*rna) & 0x03;
}

int RNA::find_rna_block(int idx){

    size_t byte;

    byte = this->rna_str[idx/4 + 1];

    return get_rna_block(&byte, idx%4);
}

void RNA::put_nucl(Nucls nucl, size_t place){
    size_t new_chain_element = nucl;
    size_t skip = place/ (sizeof(size_t)/2);
    size_t rest = place - skip* (sizeof(size_t)/2);
    new_chain_element <<= 2*(sizeof(size_t)/2 - rest);
    size_t mask = (size_t) 3 << 2*(sizeof(size_t)/2 - rest);

    this->rna_str[skip] = (this->rna_str[skip] & ~mask);
    this->rna_str[skip] |= new_chain_element;
}

RNA RNA::split(size_t idx) {
    RNA new_rna;
    new_rna.size = this->size - idx;
    new_rna.capacity = this->capacity - idx;
    new_rna.rna_str = new size_t[new_rna.capacity/4+1];

    int full_mv = idx/4;

    memcpy(new_rna.rna_str, &this->rna_str[full_mv], sizeof(size_t)*(capacity/4+1));

    short move = idx % 4;
    if(move!=0){
        for(int i = 0; i < new_rna.size/4+1; i++){
            if(i >= 1){
                new_rna.rna_str[i] = new_rna.rna_str[i] << 2*(move);
            }
            new_rna.rna_str[i] = new_rna.rna_str[i] >> 2*(4-move);
        }
    }
    return new_rna;
}


RNA RNA::operator+ (const RNA & r1)const{
    if (this->size + r1.size == 0){
        return RNA();
    }

    RNA sum;
    sum.capacity = this->capacity + r1.capacity;
    sum.size = this->size + r1.size;
    sum.rna_str = new size_t[sum.capacity/4+1];

    memcpy(sum.rna_str, this->rna_str, sizeof(size_t)*(this->size/4));
    memcpy(&sum.rna_str[this->size/4+1], r1.rna_str, sizeof(size_t)*(r1.size/4));

    short move = this->size % 4;
    if(move != 0){
        for(int i = this->size/4; i < sum.size/4+1; i++){
            if(i >= 1){
                sum.rna_str[i] = sum.rna_str[i] << 2*(4-move);
            }
            sum.rna_str[i] |= sum.rna_str[i+1] >> 2*move;
        }
    }
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

    for(size_t i = 0; i < r_new.size/4+1; i++){
        r_new.rna_str[i] = ~r_new.rna_str[i];
    }
    if (r_new.size%4 > 0){
        r_new.rna_str[r_new.size/4+1] >>= (4-(r_new.size%4))*2;
        r_new.rna_str[r_new.size/4+1] = ~r_new.rna_str[r_new.size/4+1];
        r_new.rna_str[r_new.size/4+1] <<= (4-(r_new.size%4))*2;
    }

    return r_new;

}
RNA::reference RNA::operator[](size_t num){
    return reference(num, this);
}


RNA::reference& RNA::reference::operator=(const Nucls nucl){

    short indoor_move = 3 - this->num%4;
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


bool RNA::is_complementary(const RNA& new_rna)const{
    return (*this == !new_rna);
}

RNA RNA::operator=(RNA &r1){
    this->size = r1.size;
    this->capacity = r1.capacity;
    this->rna_str = new size_t[capacity/4+1];
    memcpy(this->rna_str, r1.rna_str, sizeof(size_t)*(r1.size/4+1));
    return *this;
}
