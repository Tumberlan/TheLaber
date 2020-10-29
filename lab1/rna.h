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

    size_t* skip_rna_blocks(size_t *rna, int skip_val);

    int get_rna_block(size_t *rna, int idx);

    int find_rna_block(int idx);

    void put_nucl(Nucls nucl, size_t place);

public:

    class reference{
    public:
        size_t num;
        RNA & rna;
        reference(size_t n, RNA & rna) : num(n), rna(rna){};
        reference& operator=(const Nucls);
        operator Nucls()const;
        reference& operator=(reference&);
        Nucls operator= ( reference);

    };

    reference operator[](size_t)const;

    //copy constr
    //operator=
    RNA(){
        this->size = 0;
        this->capacity = 0;
        this->rna_str = new size_t[1];
    };


    RNA split(size_t);
    bool is_complementary(const RNA&)const;

    RNA operator+ (const RNA & r1)const;
    bool operator== (const RNA & r1)const;
    bool operator!= (const RNA & r1)const;
    RNA operator! ()const;
    // operator= (const reference&)const;
    RNA operator= (const RNA & r1)const;



    virtual ~RNA(){}
};



#endif //LAB1_RNA_H
