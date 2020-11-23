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
    uint8_t* rna_str;

    uint8_t* skip_rna_blocks(uint8_t *rna, int skip_val);


    Nucls get_rna_block(uint8_t *rna, int idx);


    class reference{
    private:
        uint8_t num;
        RNA *rna;
    public:
        reference(uint8_t n, RNA *r1): num(n), rna(r1){};
        reference& operator=(Nucls);
        operator Nucls();
        reference& operator=(reference&);
        bool operator==(const reference&)const;
        bool operator==(const Nucls)const;

    };
public:

    reference operator[](size_t);

    RNA();



    RNA split(int32_t);
    bool is_complementary(const RNA&)const;

    RNA operator+ (const RNA & r1)const;
    bool operator== (const RNA & r1)const;
    bool operator!= (const RNA & r1)const;
    RNA operator! ()const;
    RNA operator= (const RNA& r1);
    RNA(const RNA &r1){
        if(this == &r1){
            return ;
        }
        this->capacity = r1.capacity;
        this->size = r1.size;
        this->rna_str = new uint8_t[capacity/4+1];
        memcpy(rna_str, r1.rna_str, sizeof(uint8_t)*r1.size);
    };



    virtual ~RNA();
};



#endif //LAB1_RNA_H
