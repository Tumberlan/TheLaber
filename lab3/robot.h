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

class shared_command{
private:
    move_command value;
    int X;
    int Y;
public:
    move_command get_value();
    void set_value(move_command val);
    int get_X();
    void set_X(int val);
    int get_Y();
    void set_Y(int val);

};

class auto_command{
private:
    move_command value;
    int idx;
public:

    move_command get_value();
    void set_value(move_command val);
    int get_idx();
    void set_idx(int val);
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



    int get_apple_counter();
    void set_apple_counter(int val);
    int get_X();
    void set_X(int val);
    int get_Y();
    void set_Y(int val);



    void move(move_command order, just_map& god_map);
    void grab(just_map& god_map);
    void scan(just_map& god_map);
    void draw_robot_map(just_map& god_map);
    void autobot(int N, just_map& god_map);
    void apple_collector(just_map& god_map);

    void set_sapper(just_map &god_map);
    void destroy_sapper(just_map &god_map);
    void move_sapper(move_command order, just_map &god_map);

    robot_map give_map_to_sapper();
    void take_fixes(shared_command c);

    void add_siblings(int x, int y, int to_from, std::vector<r_search>& from, std::vector<r_search>& to);
    void shortest_way(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map);
    void shortest_coll(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map);
    void shortest_sapp(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map);

    void make_sapp_move(int tmp_sap_x, int tmp_sap_y,int maximum_x, int maximum_y, std::vector<map_cell>& bomb_positions, cell_value** tmp_map, just_map& god_map);

    void make_collector_move(int tmp_x, int tmp_y,int maximum_x, int maximum_y, std::vector<map_cell>& apple_positions, cell_value** tmp_map, just_map& god_map);
    int step_amount(std::string str, int a);
    void ask_command(just_map& god_map);

};



class sapper{
public:
    int X;
    int Y;
    robot_map map;
    bool can_smash_apple = false;
    
    void set_sapper(just_map &god_map);
    void destroy_sapper(just_map &god_map);
    void move_sapper(move_command order, just_map &god_map);

    void shortest_sapp(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map);
    void make_sapp_move(int tmp_sap_x, int tmp_sap_y,int maximum_x, int maximum_y, std::vector<map_cell>& bomb_positions, cell_value** tmp_map, just_map& god_map);
    void make_collector_move(int tmp_x, int tmp_y,int maximum_x, int maximum_y, std::vector<map_cell>& apple_positions, cell_value** tmp_map, just_map& god_map);

    void get_map_from_collector(robot_map got_one);
    void take_fixes(shared_command c);
};


#endif //LAB3_ROBOT_H
