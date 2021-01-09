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
private:
    int X;
    int Y;
    cell_value ** map;
    int robot_x;
    int robot_y;
    int apple_x;
    int apple_y;
    int sap_apple_x;
    int sap_apple_y;
    int plug_robot_x;
    int plug_robot_y;
    int sapper_x;
    int sapper_y;
public:

    just_map();
    void set_X(int val);
    int get_X();
    void set_Y(int val);
    int get_Y();
    void set_robot_x(int val);
    int get_robot_x();
    void set_robot_y(int val);
    int get_robot_y();
    void set_apple_x(int val);
    int get_apple_x();
    void set_apple_y(int val);
    int get_apple_y();
    void set_sap_apple_x(int val);
    int get_sap_apple_x();
    void set_sap_apple_y(int val);
    int get_sap_apple_y();
    void set_plug_robot_x(int val);
    int get_plug_robot_x();
    void set_plug_robot_y(int val);
    int get_plug_robot_y();
    void set_sapper_x(int val);
    int get_sapper_x();
    void set_sapper_y(int val);
    int get_sapper_y();

    void set_map(int x, int y, cell_value val);
    cell_value get_map(int x, int y);
    void set_robot();
};


std::ostream& operator<<(std::ostream& os, const just_map& map_t);





class map_cell{
private:
    int X;
    int Y;
    cell_value value;
public:
    int get_X();
    void set_X(int val);
    int get_Y();
    void set_Y(int val);
    cell_value get_value();
    void set_value(cell_value val);


    map_cell();
};

class r_search: public map_cell{
private:
    int to_from_point = 0;
    int to_go_point = 0;
    int from_to_sum = 0;
    int previous_x = NULL;
    int previous_y = NULL;
public:
    int get_to_from_point();
    void set_to_from_point(int val);
    int get_to_go_point();
    void set_to_go_point(int val);
    int get_from_to_sum();
    void set_from_to_sum(int val);
    int get_previous_x();
    void set_previous_x(int val);
    int get_previous_y();
    void set_previous_y(int val);

};

bool is_added(int , int, std::vector<r_search>);

class robot_map{
public:
    std::vector<map_cell> data;
    robot_map() = default;

    ~robot_map();

    cell_value get_cell(int , int)const;
    bool is_discovered(int, int) const;
    void add_cell(int , int, cell_value);
    bool is_added(int , int);
    // std::ostream& operator<<(std::ostream& os, const game_map& map)
};



#endif //LAB3_MAP_H
