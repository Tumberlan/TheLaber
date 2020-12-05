//
// Created by Igor on 04.12.2020.
//

#include <gtest/gtest.h>
#include "game.h"

namespace {
    class GameFixture : public testing::Test {
    public:
        field wrld;
    };
}


TEST_F(GameFixture,set){

    wrld.set(1, 1);
    wrld.set(1,2);
    wrld.set(1,3);

    ASSERT_TRUE(wrld.show_states(1,1) && wrld.show_states(1,2) && wrld.show_states(1,3));
}


TEST_F(GameFixture,clear){
    wrld.set(1, 1);
    wrld.set(1,2);
    wrld.set(1,3);
    wrld.clear(1,2);

    ASSERT_TRUE(wrld.show_states(1,1) && !wrld.show_states(1,2) && wrld.show_states(1,3));
}

TEST_F(GameFixture,step){

    wrld.set(1, 1);
    wrld.set(1,2);
    wrld.set(1,3);
    wrld.one_step();

    ASSERT_TRUE(wrld.show_states(0,2) && wrld.show_states(1,2) && wrld.show_states(2,2));
}

TEST_F(GameFixture,back){
    wrld.set(1, 1);
    wrld.set(1,2);
    wrld.set(1,3);
    wrld.one_step();
    wrld.back_step();

    ASSERT_TRUE(wrld.show_states(1,1) && wrld.show_states(1,2) && wrld.show_states(1,3));
}


TEST_F(GameFixture,reset){
    wrld.set(1, 1);
    wrld.set(1,2);
    wrld.set(1,3);
    wrld.reset();

    ASSERT_TRUE(!wrld.show_states(1,1) && !wrld.show_states(1,2) && !wrld.show_states(1,3));
}

TEST_F(GameFixture,large){
    wrld.set(1, 1);
    wrld.set(1,2);
    wrld.set(1,3);

    for(int i = 0; i < 1000000; i++){
        wrld.one_step();
    }

    ASSERT_TRUE(wrld.show_states(1,1) && wrld.show_states(1,2) && wrld.show_states(1,3));
}