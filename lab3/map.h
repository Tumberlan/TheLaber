//
// Created by Igor on 17.12.2020.
//

#ifndef LAB3_MAP_H
#define LAB3_MAP_H

#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <time.h>

enum cell_value{
    ROBOT_COLLECTOR,
    ROBOT_SAPPER,
    MYSTERY,
    EMPTY,
    ROCK,
    BOMB,
    APPLE,
    BORDER,
    BLOCKED
};

cell_value random_state();

char to_map_sign(cell_value a);

class just_map{
public:
    cell_value ** map;
    int X;
    int Y;
    int robot_x;
    int robot_y;
    int apple_x;
    int apple_y;
    int sap_apple_x;
    int sap_apple_y;
    int set_robot_x;
    int set_robot_y;
    int sapper_x;
    int sapper_y;

    just_map();
    void set_robot();
};


std::ostream& operator<<(std::ostream& os, const just_map& map_t);





class map_cell{
public:
    int X;
    int Y;
    cell_value value;
    map_cell();
};

class r_search: public map_cell{
public:
    int to_from_point = 0;
    int to_go_point = 0;
    int from_to_sum = 0;
    int previous_x = NULL;
    int previous_y = NULL;
};

bool is_added(int , int, std::vector<r_search>);

class robot_map{
public:

    std::vector<map_cell> data;
    robot_map() = default;

    ~robot_map();

    void init_map();
    cell_value get_cell(int , int)const;
    bool is_discovered(int, int) const;
    void add_cell(int , int, cell_value);
    bool is_added(int , int);
    // std::ostream& operator<<(std::ostream& os, const game_map& map)
};



#endif //LAB3_MAP_H
