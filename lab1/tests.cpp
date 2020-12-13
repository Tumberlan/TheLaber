#include <gtest/gtest.h>
#include "rna.h"

namespace {
    class rna_testing : public testing::Test {
    public:
        RNA r1,r2,r3;
    };
}


TEST_F(rna_testing,equality){
    r1[0] = RNA::A;
    EXPECT_EQ(r1[0],RNA::A);
    r1[0] = r2[1] = RNA::T;
    EXPECT_EQ(r1[0],RNA::T);
    EXPECT_EQ(r2[1],RNA::T);
}

TEST_F(rna_testing,plus){
    for (int i = 0; i < 100; i++){
        r1[i] = RNA::G;
        r2[i] = RNA::A;
    }
    r3 = r1 + r2;
    for (int i = 0; i < 100; i++){
        ASSERT_EQ(r3[i],r1[i]);
        ASSERT_EQ(r3[i+100],r2[i]);
    }
}

TEST_F(rna_testing,one_million){
    for (int i = 0; i < 1000000; i++){
        r1[i] = RNA::G;
    }
    for (int i = 91; i < 1000000; i+=20317){
        ASSERT_EQ(r1[i],RNA::G);
    }
}

TEST_F(rna_testing,copy){
    for (int i = 0; i < 200; i+=2){
        r1[i] = RNA::G;
        r1[i+1] = RNA::T;
    }
    r2 = r1;
    ASSERT_EQ(r1,r2);
    for (int i = 0; i < 200; i++){
        ASSERT_EQ(r1[i],r2[i]);
    }
    const RNA rnk4(r1);
    ASSERT_EQ(r1,rnk4);
    for (int i = 0; i < 200; i++){
        ASSERT_EQ(rnk4[i],r1[i]);
    }
}

TEST_F(rna_testing,split){
    for (int i = 0; i < 100; i+=2){
        r1[i] = RNA::G;
        r1[i+1] = RNA::C;
    }
    r2 = r1.split(20);
    for (int i = 0; i < 100 - 20; i++){
        ASSERT_EQ(r1[i+20],r2[i]);
    }
}

TEST_F(rna_testing,empty_split){
    r2 = r1.split(100);
    for(int i = 0; i < 100; i++){
        ASSERT_EQ(r1[i],NULL);
    }
}


TEST_F(rna_testing,complementary){
    for (int i = 0; i < 200; i+=2){
        r1[i] = RNA::T;
        r1[i+1] = RNA::A;
    }
    r2 = !r1;
    ASSERT_TRUE(r2.is_complementary(r1));
    r2[10] = RNA::T;
    r2[11] = RNA::T;
    ASSERT_FALSE(r2.is_complementary(r1));
}


TEST_F(rna_testing,unavailibale_posititon){
    for(int i = 0; i < 100000; i++){
        ASSERT_EQ(r1[i],NULL);
    }
}