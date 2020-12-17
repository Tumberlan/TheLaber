//
// Created by Igor on 17.12.2020.
//

#ifndef LAB3_ROBOT_H
#define LAB3_ROBOT_H

#include "map.h"

enum move_command{
    NO,
    UP,
    DOWN,
    RIGHT,
    LEFT
};


enum robot_type{
    COLLECTOR,
    SAPPER
};

enum robot_mode{
    MANUAL,
    AUTO_SCAN,
    AUTO_COLLECT
};

class robot{
public:
    int apple_counter;
    int X;
    int Y;
    bool can_take_apple = false;
    robot_map map;

    robot();

    void move(move_command order, just_map& god_map);
    void grab(just_map& god_map);
    void scan(just_map& god_map);
    void draw_robot_map(just_map& god_map);
};



#endif //LAB3_ROBOT_H
