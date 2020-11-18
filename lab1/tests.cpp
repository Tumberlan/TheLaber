//
// Created by Igor on 29.10.2020.
//

#include <gtest/gtest.h>
#include "rna.h"

namespace {
    class ClassDeclaration : public testing::Test {
    public:
        RNA rnk1,rnk2,rnk3;
    };
}

TEST_F(ClassDeclaration,test_eq){
    rnk1[0] = A;
    EXPECT_EQ(rnk1[0],A);
    rnk1[0] = rnk2[1] = G;
    EXPECT_EQ(rnk1[0],G);
    EXPECT_EQ(rnk2[1],G);
}

TEST_F(ClassDeclaration,test_plus){
    std:: cout << "dash";
    for (int i = 0; i < 100; i++){
        rnk1[i] = C;
        rnk2[i] = T;
    }
    std:: cout << "dash";
    rnk3 = rnk1 + rnk2;
    std:: cout << "dash";
    for (int i = 0; i < 100; i++){
        EXPECT_EQ(rnk3[i],rnk1[i]);
        EXPECT_EQ(rnk3[i+100],rnk2[i]);
    }
    std:: cout << "dash";
}
/*
TEST_F(ClassDeclaration,test_100mil){
    for (int i = 0; i < 100000000; i++){
        rnk1[i] = C;
    }
    for (int i = 91; i < 100000000; i+=20317){
        EXPECT_EQ(rnk1[i],C);
    }

}*/

TEST_F(ClassDeclaration,test_cpy){
    for (int i = 0; i < 1000; i+=3){
        rnk1[i] = G;
        rnk1[i+1] = A;
        rnk1[i+2] = C;
    }
    rnk2 = rnk1;
    EXPECT_EQ(rnk1,rnk2);
    for (int i = 0; i < 1000; i++){
        EXPECT_EQ(rnk1[i],rnk2[i]);
    }
}

TEST_F(ClassDeclaration,test_split){
    for (int i = 0; i < 1000; i+=3){
        rnk1[i] = G;
        rnk1[i+1] = A;
        rnk1[i+2] = C;
    }
    rnk2 = rnk1.split(100);
    for (int i = 0; i < 1000 - 100; i++){
        EXPECT_EQ(rnk1[i+100],rnk2[i]);
    }
}

TEST_F(ClassDeclaration,test_isComplementary){
    for (int i = 0; i < 1000; i+=3){
        rnk1[i] = G;
        rnk1[i+1] = A;
        rnk1[i+2] = C;
    }
    rnk2 = !rnk1;
    EXPECT_TRUE(rnk2.is_complementary(rnk1));
    rnk2[10] = T;
    rnk2[11] = T;
    EXPECT_FALSE(rnk2.is_complementary(rnk1));
}
/*
TEST_F(ClassDeclaration,test_big_rad){
    rnk1[0] = C;
    rnk1[1000000000] = rnk1[0];
    EXPECT_EQ(rnk1[0],C);
    EXPECT_EQ(rnk1[1000000000],C);
}*/
