#include <iostream>
#include <fstream>
#include <tuple>
#include "tuple_functions.h"
#include "parser.h"


int main() {
    std::ifstream file("test.csv");

    try{
        CSV_parser<std::string, int, std::string> parser(file, 1);
        for(const auto &tuple : parser){

            std::cout << tuple << std::endl;
        }
    }

    catch (std::exception &error){
        std::cout << error.what() << std::endl;
    }

    if (file.is_open()){
        file.close();
    }

    return 0;
}
