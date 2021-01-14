#include <iostream>
#include <tuple>
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

    file.close();

    return 0;
}
