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
    size_t capacity; // предполагаемое памятью кол-во вмещаемых нуклеотидов
    size_t size; //кол-во нуклеотидов
    size_t* rna_str;

    size_t* skip_rna_blocks(size_t *rna, int skip_val);

    int get_rna_block(size_t *rna, int idx);

    int find_rna_block(int idx);

    class reference{
    private:
        size_t num;
        RNA *rna;
    public:
        reference(size_t n, RNA *r1): num(n), rna(r1){};
        reference& operator=(Nucls);
        operator Nucls();
        reference& operator=(reference&);

    };
public:

    reference operator[](size_t);

    RNA(){
        this->size = 0;
        this->capacity = 0;
        this->rna_str = new size_t[1];
    };


    void put_nucl(Nucls nucl, size_t place);

    RNA split(size_t);
    bool is_complementary(const RNA&)const;

    RNA operator+ (const RNA & r1)const;
    bool operator== (const RNA & r1)const;
    bool operator!= (const RNA & r1)const;
    RNA operator! ()const;
    RNA operator= (RNA&);
    RNA(const RNA &r1): capacity(r1.capacity), size(r1.size){
        this->rna_str = new size_t[capacity/4+1];
        memcpy(rna_str, r1.rna_str, sizeof(size_t)*r1.size);
    };



    virtual ~RNA(){}
};



#endif //LAB1_RNA_H
