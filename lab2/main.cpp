#include <iostream>
#include <random>
#include <stdio.h>
#include "game.h"
#include <string>
#include <cstring>
#include <functional>
#include <Windows.h>
#include <gtest/gtest.h>


int main(int argc, char *argv[]){
    testing::InitGoogleTest(&argc,argv);
    testing::FLAGS_gtest_break_on_failure = "";
    return RUN_ALL_TESTS();
}


/*
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
}*/
