//
// Created by Igor on 09.10.2020.
//
#include "rna.h"
#include <stdio.h>

// РЕАЛИЗАЦИЯ REFERENCE

void RNA::reference::put_nucl(size_t value) {

    while(this->pos_in_arr > this->rna->size){
        auto *new_rna = new size_t[this->rna->size*2];
        for(int i = 0; i < this->rna->size+1; i++){
            new_rna[i] = this->rna->rna_str[i];
        }
        for(int i = this->rna->size; i < this->rna->size * 2; i++){
            new_rna[i] = 0;
        }
        delete[] this->rna->rna_str;
        this->rna->rna_str = new_rna;
        this->rna->size = this->rna->size*2;
    }
    if(this->num > this->rna->last_nucl_position){
        this->rna->last_nucl_position = this->num;
    }


    size_t move = 8*sizeof(size_t) - this->pos_in_byte * 2 - 2;
    size_t mask = (size_t)3 << (move);
    this->rna->rna_str[pos_in_arr] = (this->rna->rna_str[pos_in_arr] & (~mask)) | (value << move);
}

int RNA::reference::get_nucl() const {
    if (this->num > this->rna->last_nucl_position){
        return static_cast<Nucls>(NULL);
    }
    size_t move = 8 * sizeof(size_t) - this->pos_in_byte*2 - 2;
    return (int)(((this->rna->rna_str[this->pos_in_arr]) >> move) & 3u);
}


RNA::reference::reference(RNA *ptr, size_t position_in_arr, size_t position_in_byte, size_t number) : rna(nullptr) {
    this->rna = ptr;
    this->pos_in_arr = position_in_arr;
    this->pos_in_byte = position_in_byte;
    this->num = number;
}

RNA::Nucls RNA::reference::operator!() const{
    return (Nucls)(3 - get_nucl());
}

RNA::reference& RNA::reference::operator=(Nucls nucl) {
    put_nucl(nucl);
    return *this;
}

RNA::reference& RNA::reference::operator=(const RNA::reference &r1) {
    if(this == &r1){
        return *this;
    }
    this->put_nucl(r1.get_nucl());
    return *this;
}


RNA::reference& RNA::reference::operator=(const RNA::const_reference &r1){
    this->put_nucl(r1.get_nucl());
    return *this;
}

bool RNA::reference::operator==(const RNA::reference& r1) const{
    return this->get_nucl() == r1.get_nucl();
}

bool RNA::reference::operator==(const RNA::const_reference& r1) const{
    return this->get_nucl() == r1.get_nucl();
}

RNA::reference::operator Nucls() const{
    return (Nucls)this->get_nucl();
}


// РЕАЛИЗАЦИЯ CONST_REFERENCE

RNA::const_reference::const_reference(const RNA *ptr, size_t position_in_arr, size_t position_in_byte, size_t number) : rna(nullptr){
    this->rna = ptr;
    this->pos_in_arr = position_in_arr;
    this->pos_in_byte = position_in_byte;
    this->num = number;
}

int RNA::const_reference::get_nucl() const{
    if (this->num > this->rna->last_nucl_position) {
        return 0;
    }
    size_t move = 8 * sizeof(size_t) - this->pos_in_byte * 2 - 2;
    return (int)(((this->rna->rna_str[this->pos_in_arr]) >> move) & 3u);
}

RNA::Nucls RNA::const_reference::operator!() const{
    return (Nucls)(3 - get_nucl());
}

bool RNA::const_reference::operator==(const RNA::reference& r1) const{
    return this->get_nucl() == r1.get_nucl();
}

bool RNA::const_reference::operator==(const RNA::const_reference& r1) const{
    return this->get_nucl() == r1.get_nucl();
}

RNA::const_reference::operator Nucls() const{
    return (Nucls)this->get_nucl();
}


// РЕАЛИЗАЦИЯ RNA

RNA::RNA() {
    this->rna_str = new size_t[10];
    this->size = 10;
    this->last_nucl_position = 0;
    for (int i = 0; i < this->size; i++){
        this->rna_str[i] = 0;
    }
}


RNA::~RNA() {
    delete[] this->rna_str;
}

RNA::RNA(const RNA &r1) {
    if (this == &r1){
        return;
    }

    delete[] this->rna_str;
    this->rna_str = new size_t[r1.size];
    this->size = r1.size;
    this->last_nucl_position = r1.last_nucl_position;
    for(int i = 0; i < this->size; i++){
        this->rna_str[i] = r1.rna_str[i];
    }
}

RNA::reference RNA::operator[](size_t position) {
    reference ref(this, position/(4*sizeof(size_t)), position % (4* sizeof(size_t)), position);
    return ref;
}

RNA::const_reference RNA::operator[](size_t position) const{
    const_reference ref(this, position/(4*sizeof(size_t)), position % (4* sizeof(size_t)), position);
    return ref;
}

RNA& RNA::operator=(const RNA & r1) {

    this->rna_str = new size_t[r1.size];
    this->size = r1.size;
    this->last_nucl_position = r1.last_nucl_position;
    for(int i = 0; i < this->size; i++){
        this->rna_str[i] = r1.rna_str[i];
    }
    return *this;
}


RNA& RNA::operator+=(const RNA &r1) {
    size_t tmp = this->last_nucl_position;
    for(int i = 0; i < r1.size * 4 * sizeof(size_t); i++){
        this->operator[](tmp+i+1) = r1.operator[](i);
    }
    return *this;
}

RNA RNA::operator+(const RNA &r1) const {
    RNA new_rna;
    for(int i = 0; i < this->last_nucl_position + 1; i++){
        new_rna[i] = this->operator[](i);
    }
    for(int i = 0; i < r1.last_nucl_position + 1; i++){
        new_rna[this->last_nucl_position + i + 1] = r1[i];
    }
    return new_rna;
}

bool RNA::operator==(const RNA& r1) const{
    for (int i = 0; i < this->size; i++) {
        if (this->rna_str[i] != r1.rna_str[i]){
            return false;
        }
    }
    return true;
}

bool RNA::operator!=(const RNA &r1) const {
    return !(*this == r1);
}

RNA RNA::operator!() const {
    RNA new_rna;
    for(int i = 0; i < this->last_nucl_position + 1; i++){
        new_rna[i] = !this->operator[](i);
    }
    return new_rna;
}

RNA RNA::split(size_t position) const {
    RNA new_rna;
    if (position >= this->last_nucl_position){
        for(int i = 0; i <= this->last_nucl_position; i++){
            new_rna[i] = this->operator[](i);
        }
    }else{
        for(int i = 0; i <= this->last_nucl_position - position; i++){
            new_rna[i] = this->operator[](i + position);
        }
    }
    return new_rna;
}

bool RNA::is_complementary(const RNA &r1) const {
    if (this->last_nucl_position != r1.last_nucl_position){
        return false;
    }
    for(int i = 0; i < this->last_nucl_position; i++){
        if(this->operator[](i) != !(r1[i])){
            return false;
        }
    }
    return true;
}

