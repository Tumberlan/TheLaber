//
// Created by Igor on 17.12.2020.
//

#ifndef LAB3_ROBOT_H
#define LAB3_ROBOT_H

#include "map.h"
#include <string>
#include <iostream>
#include <cmath>

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



class auto_command{
public:
    move_command value;
    int idx;
};

class sapper{
public:
    int X;
    int Y;
    bool ready_to_defuse;

};


class robot{
public:
    int apple_counter;
    int X;
    int Y;
    int sapper_x;
    int sapper_y;
    bool can_take_apple = false;
    bool can_smash_apple = false;
    robot_map map;
    int r_map_rad;
    bool sapp_on = false;
    robot();

    void move(move_command order, just_map& god_map);
    void grab(just_map& god_map);
    void scan(just_map& god_map);
    void draw_robot_map(just_map& god_map);
    void autobot(int N, just_map& god_map);
    void apple_collector(just_map& god_map);

    void set_sapper(just_map &god_map);
    void destroy_sapper(just_map &god_map);
    void move_sapper(move_command order, just_map &god_map);

    void add_siblings(int x, int y, int to_from, std::vector<r_search>& from, std::vector<r_search>& to);
    void shortest_way(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map);
    void shortest_coll(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map);
    void shortest_sapp(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map);

    void make_sapp_move(int tmp_sap_x, int tmp_sap_y,int maximum_x, int maximum_y, std::vector<map_cell>& bomb_positions, cell_value** tmp_map, just_map& god_map);

    void make_collector_move(int tmp_x, int tmp_y,int maximum_x, int maximum_y, std::vector<map_cell>& apple_positions, cell_value** tmp_map, just_map& god_map);
    int step_amount(std::string str, int a);
    void ask_command(just_map& god_map);

};



#endif //LAB3_ROBOT_H
