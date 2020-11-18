#include <gtest/gtest.h>
#include "rna.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

int main(){

    RNA a;
    RNA b;
    for (int i = 0; i < 49; i++){
        a[i] = T;
    }
    for (int i = 0; i < 49; i++){
        std:: cout << a[i];
    }
    std:: cout << '\n';
    for (int i = 0; i < 49; i++){
        b[i] = G;
    }
    for (int i = 0; i < 49; i++){
        std:: cout << b[i];
    }

    std:: cout << '\n';
    RNA sum = a+b;
    for (int i = 0; i < 50; i++) {
        std::cout << sum[i];
    }
    /*RNA a;
    RNA b;

    for (int i = 0; i < 49; i++){
        a[i] = T;
    }
    for (int i = 0; i < 49; i++){
        std:: cout << a[i];
    }
    std:: cout << '\n';
    for (int i = 0; i < 49; i++){
        b[i] = G;
    }
    for (int i = 0; i < 49; i++){
        std:: cout << b[i];
    }
    std:: cout << '\n';
    RNA sum = a+b;
    for (int i = 0; i < 50; i++){
        std:: cout << sum[i];
    }
*/
    std:: cout << '\n' << "123";
    return 0;

}




/*
int main(int argc, char *argv[]){



    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}*/
