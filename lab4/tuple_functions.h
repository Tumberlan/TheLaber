//
// Created by Igor on 11.01.2021.
//

#ifndef LAB4_TUPLE_FUNCTIONS_H
#define LAB4_TUPLE_FUNCTIONS_H
#include <iostream>
#include <tuple>
#include <vector>
#include <sstream>


template<typename Type>

Type from_string(const std::string &str){
    std::stringstream ss(str);
    Type val;
    if(!(ss >> val)){  //из ss вытягиваем в val (преобразование строки в нужный нам тип)
        throw std::exception(); // инициализируем исключение
    }
    return val;
}

// особый случай когда нужный тип сама строка
template<>

std::string from_string<std::string>(const std::string &str){
    return str;
}



template<size_t N, typename Type>

class tuple_print{
public:
    static void print(std::ostream &os, const Type &tuple){
        tuple_print<N-1, Type>::print(os, tuple);
        if(N != 1){
            os << ", ";
        }
        os << " " << std::get<N-1>(tuple); // std::get<N-1>(tuple) берет из tuple N-1 элемент
    }
};


// особый случай для 0 итерации
template<typename Type>

class tuple_print<0, Type>{
public:
    static void print(std::ostream &os, const Type &tuple){}
};


template <typename... Arguments> //набор параметров
std::ostream& operator<<(std::ostream& os, const std::tuple<Arguments...>& tuple) { //распаковка параметров
    os << "(";
    tuple_print<sizeof...(Arguments), std::tuple<Arguments...>>::print(os, tuple);
    os << ")";
    return os;
}

//для std::vector<std::string>
template<size_t N, typename Type>

class tuple_add_strings{
public:
    static void convertor(Type &tuple, const std::vector<std::string> &strings){

        try{
            std::get<N-1>(tuple) = from_string<typename std::tuple_element<N-1, Type>::type>(strings[N-1]); // пытаемся к строке приравнять строку
        }
        catch (std::exception&){
            throw std::invalid_argument(std::to_string(N)); // в какой ячейке в строке неподдерживаемый символ
        }
        tuple_add_strings<N-1, Type>::convertor(tuple, strings);
    }
};

// особый случай для 0 итерации
template<typename Type>

class tuple_add_strings<0, Type>{
public:
    static void convertor(Type &tuple, const std::vector<std::string> &strings){}
};


template<typename... Arguments>

std::tuple<Arguments...> tuple_parse(const std::vector<std::string> &strings){
    std::tuple<Arguments...> tuple;
    tuple_add_strings<sizeof...(Arguments), std::tuple<Arguments...>>::convertor(tuple, strings); // sizeof...(Arguments) возвращает количество аргументов
    return tuple;
}


#endif //LAB4_TUPLE_FUNCTIONS_H
