//
// Created by Igor on 04.10.2020.
//

#ifndef LAB1_RNA_H
#define LAB1_RNA_H

#include <string>
#include <cstring>




class RNA{
public:
    enum Nucls{
        A,
        G,
        C,
        T
    };

private:
    size_t size = 0; //кол-во элементов в массиве
    size_t * rna_str = nullptr;
    size_t last_nucl_position = 0;

    class const_reference;
    class reference{
    private:
        size_t num;
        size_t pos_in_arr;
        size_t pos_in_byte;
        RNA *rna;
        void put_nucl(size_t);
    public:
        int get_nucl() const;
        reference(RNA*, size_t , size_t, size_t);
        Nucls operator!() const;
        reference& operator=(Nucls);
        reference& operator=(const reference&);
        reference& operator=(const const_reference&);
        operator Nucls()const;
        bool operator==(const reference&)const;
        bool operator==(const const_reference&) const;
    };

    class const_reference{
    private:
        size_t num;
        size_t pos_in_arr;
        size_t pos_in_byte;
        const RNA *rna;

    public:
        int get_nucl() const;
        const_reference(const RNA*, size_t , size_t, size_t);

        Nucls operator!() const;
        operator Nucls()const;
        bool operator==(const reference&)const;
        bool operator==(const const_reference&) const;
    };

public:
    RNA();
    ~RNA();
    RNA(const RNA &r1);

    reference operator[](size_t);
    const_reference operator[](size_t)const;
    RNA& operator= (const RNA&);
    RNA& operator+=(const RNA&);
    RNA operator+(const RNA&) const;
    bool operator==(const RNA&) const;
    bool operator!=(const RNA&) const;
    RNA operator!() const;
    RNA split(size_t) const;
    bool is_complementary(const RNA&) const;
};



#endif //LAB1_RNA_H
