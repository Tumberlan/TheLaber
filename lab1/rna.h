//
// Created by Igor on 04.10.2020.
//

#ifndef LAB1_RNA_H
#define LAB1_RNA_H

#include <string>
#include <cstring>

enum Nucls{
    A = 0,
    G = 1,
    C = 2,
    T = 3
};

class RNA{

private:
    size_t capacity;
    size_t size;
    size_t* rna_str;

    unsigned char skip_rna_blocks(unsigned char rna, int skip_val){
        rna >>= 8*skip_val;
        return rna;
    }

    int get_rna_block(unsigned char rna, int idx){
        int skip_val = idx / 4;
        int idx_remain = idx % 4;
        if(idx_remain < 0 || idx_remain > 3){
            exit(0);
        }

        rna = skip_rna_blocks(rna, skip_val);

        rna >>= 2*(3-idx_remain);
        return rna & 0x03;
    }
    int find_rna_block(int idx){

        size_t byte;

        byte = this->rna_str[idx/4 + 1];

        return get_rna_block(byte, idx%4);
    }

    void put_nucl(Nucls nucl, size_t place){
        size_t new_chain_element = nucl;
        size_t skip = place/ (sizeof(size_t)/2);
        size_t rest = place - skip* (sizeof(size_t)/2);
        new_chain_element <<= 2*(sizeof(size_t)/2 - rest);
        size_t mask = (size_t) 3 << 2*(sizeof(size_t)/2 - rest);

        this->rna_str[skip] = (this->rna_str[skip] & ~mask);
        this->rna_str[skip] |= new_chain_element;
    }

public:

    class reference{
    public:
        size_t num;
        RNA & rna;
        reference(size_t n, RNA & rna) : num(n), rna(rna){}
        reference& operator=(Nucls);
        operator Nucls(){}
    };

    reference operator[](size_t num){
        return reference(num, this*);
    }

    RNA(){

    };
    void add(Nucls);

    RNA operator+ (const RNA & r1)const{
        if (this->size + r1.size == 0){
            return RNA();
        }

        RNA sum;
        sum.capacity = this->capacity + r1.capacity;
        sum.size = this->size + r1.size;
        sum.rna_str = new size_t[sum.capacity/4];

        memcpy(sum.rna_str, this->rna_str, sizeof(size_t)*(this->size));
        memcpy(&sum.rna_str[this->size], r1.rna_str, sizeof(size_t)*(r1.size));

        short move = this->size % 4;
        if(move != 0){
            for(int i = this->size/4; i < sum.size/4; i++){
                if(i >= 1){
                    sum.rna_str[i] = sum.rna_str[i] << 2*(4-move);
                }
                sum.rna_str[i] |= sum.rna_str[i+1] >> 2*move;
            }
        }
        return sum;
    }
    bool operator== (const RNA & r1)const{
        if(this->size != r1.size){
            return false;
        }
        for (int i = 0; i < this->size/4; i++){
            if(this->rna_str[i] != r1.rna_str[i]){
                return false;
            }
        }
        return true;

    };
    bool operator!= (const RNA & r1)const{
        if(this->size != r1.size){
            return true;
        }
        for (int i = 0; i < this->size/4; i++){
            if(this->rna_str[i] != r1.rna_str[i]){
                return true;
            }
        }
        return false;

    };
    RNA operator! (){
        RNA r_new;
        r_new.capacity = this->capacity;
        r_new.size = r_new.size;
        r_new.rna_str = this->rna_str;
        for(int i = 0; i < r_new.capacity/4; i++){
            r_new.rna_str[i] ^= 257;
        }

        return r_new;

    };



    virtual ~RNA(){}
};

class Complex
{

    Complex operator+(const Complex & r1)const;
    Complex&operator
}

#endif //LAB1_RNA_H
