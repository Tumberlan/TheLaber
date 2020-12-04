#include <iostream>
#include <random>
#include <stdio.h>
#include "game.h"
#include <string>
#include <cstring>
#include <functional>
#include <Windows.h>


int check_step(std::string str, int a){
    int mul = 1;
    if(a > 1) {
        for (int i = 0; i < a-1; i++);
        mul = mul * 10;
    }

    int result = 0;
    for (int i = 0; i < a; i++){
        result += (str[i]-'0')*mul;
        mul = mul/10;
    }

    return result;
}

bool f_command(field wrld){
    std::string input;
    std:: cin >> input;

    if (input == "reset"){
        wrld.reset();
        return true;
    }
    if (input == "set"){
        std::cin >> input;
        wrld.set( (input[1] - '0'), (input[0] - 'A'));
        return true;
    }
    if (input == "clear"){
        std::cin >> input;
        wrld.clear((input[1] - '0'), (input[0] - 'A'));
        return true;
    }
    if (input == "step"){
        std::cin >> input;
        for(int i = 0; i < check_step(input, input.length()); i++){
            wrld.one_step();
        }
        return true;
    }
    if (input == "back"){
        wrld.back_step();
        return true;
    }
    if (input == "save"){
        std::cin >> input;
        wrld.save(input);
        return true;
    }
    if (input == "load"){
        std::cin >> input;
        wrld.load(input);
        return true;
    }
    return false;
}






int main() {

    field wrld;
    wrld.set(1,1);
    wrld.set(1,2);
    wrld.set('3' - '0', 'B' - 'A');
    std::cout << wrld.nei_num(2, 2);
    std::cout << wrld.nei_num(2, 1);
    std::cout << '\n';
    std::cout << '\n';
    //wrld.draw();
    std::cout << wrld;
    wrld.one_step();
    std::cout << '\n';
    //wrld.draw();
    std::cout << wrld;
    wrld.one_step();
    std::cout << '\n';
    //wrld.draw();
    std::cout << wrld;
    wrld.save("file");

    return 0;
}
