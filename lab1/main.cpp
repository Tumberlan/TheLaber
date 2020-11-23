#include <gtest/gtest.h>
#include "rna.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdbool.h>

int main() {

    RNA rnk1;
    for (int i = 0; i < 200; i+=2){
        rnk1[i] = G;
        rnk1[i+1] = A;
    }
    for (int i = 0; i < 200; i++){
        std:: cout << rnk1[i];
    }
    std:: cout << '\n';
    RNA sp = !rnk1;
    for (int i = 0; i < 200; i++){
        std:: cout << sp[i];
    }
    std:: cout << '\n';

    RNA ad = !sp;
    std:: cout << (rnk1.operator==(ad));
    //if(rnk1.is_complementary(sp)){
      //  std:: cout << "123";
    //}
    return 0;
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

    std:: cout << '\n' << "123";
    return 0;

}*/

/*
int main(int argc, char *argv[]){



    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}*/
