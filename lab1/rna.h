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

    unsigned char skip_rna_blocks(unsigned char rna, int skip_val);

    int get_rna_block(unsigned char rna, int idx);

    int find_rna_block(int idx);

    void put_nucl(Nucls nucl, size_t place);

public:

    class reference{
    public:
        size_t num;
        RNA & rna;
        reference(size_t n, RNA & rna) : num(n), rna(rna){}
        reference& operator=(Nucls);
        operator Nucls(){}
    };

    reference operator[](size_t num);

    RNA(){

    };

    RNA operator+ (const RNA & r1)const;
    bool operator== (const RNA & r1)const;
    bool operator!= (const RNA & r1)const;
    RNA operator! ();



    virtual ~RNA(){}
};



#endif //LAB1_RNA_H
