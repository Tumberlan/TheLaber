//
// Created by Igor on 04.10.2020.
//

#ifndef LAB1_RNA_H
#define LAB1_RNA_H

#include <string>
#include <cstring>

enum Nucls{
    A,
    G,
    C,
    T
};

class RNA{

private:
    size_t capacity; // предполагаемое памятью кол-во вмещаемых нуклеотидов
    size_t size; //кол-во нуклеотидов
    int8_t* rna_str;

    int8_t* skip_rna_blocks(int8_t *rna, int skip_val);

    Nucls get_rna_block(int8_t *rna, int idx);


    class reference{
    private:
        int8_t num;
        RNA *rna;
    public:
        reference(int8_t n, RNA *r1): num(n), rna(r1){};
        reference& operator=(Nucls);
        operator Nucls();
        reference& operator=(reference&);
        bool operator==(const reference&)const;
        bool operator==(const Nucls)const;

    };
public:

    reference operator[](int8_t);

    RNA(){
        this->size = 0;
        this->capacity = 50;
        this->rna_str = new int8_t[50];
    };



    RNA split(int8_t);
    bool is_complementary(const RNA&)const;

    RNA operator+ (RNA & r1);
    bool operator== (const RNA & r1)const;
    bool operator!= (const RNA & r1)const;
    RNA operator! ()const;
    RNA operator= (const RNA&);
    RNA(const RNA &r1): capacity(r1.capacity), size(r1.size){
        this->rna_str = new int8_t[capacity/4+1];
        memcpy(rna_str, r1.rna_str, sizeof(int8_t)*r1.size);
    };



    virtual ~RNA(){}
};



#endif //LAB1_RNA_H
