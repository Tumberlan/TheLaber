//
// Created by Igor on 17.12.2020.
//

#include "map.h"
#include <random>
#include <cmath>

void just_map::set_X(int val){
    X = val;
}

int just_map::get_X() {
    return X;
}

void just_map::set_Y(int val){
    Y = val;
}

int just_map::get_Y() {
    return Y;
}




cell_value random_state() {
    int a = rand() % 10;
    if (a == 1){
        return APPLE;
    }else if (a == 2){
        return ROCK;
    }else if (a == 3){
        return BOMB;
    }else{
        return EMPTY;
    }
}

char to_map_sign(cell_value a){
    if(a == APPLE){
        return 'A';
    }
    if(a == ROCK){
        return '0';
    }
    if(a == BOMB){
        return '*';
    }
    if(a == EMPTY){
        return '.';
    }
    if(a == ROBOT_COLLECTOR){
        return 'C';
    }
    if(a == ROBOT_SAPPER){
        return 'S';
    }
    if(a == BORDER){
        return '^';
    }
    return '?';
}

just_map::just_map() {
    int x = 1000;
    int y = 1000;

    X = x;
    Y = y;
    map = new cell_value*[x];

    for(int i = 0; i < x; i++){
        map[i] = new cell_value[y];
    }

    for (int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            map[i][j] = random_state();
        }
    }
}

void just_map::set_robot() {
    int a = rand() % X;
    int b = rand() % Y;
    while(map[a][b] != EMPTY){
        a = rand() % X;
        b = rand() % Y;
    }

    robot_x = a;
    robot_y = b;
    set_robot_x = a;
    set_robot_y = b;
    map[a][b] = ROBOT_COLLECTOR;
}


void just_map::set_map(int x, int y, cell_value val) {
    map[x][y] = val;
}

cell_value just_map::get_map(int x, int y) {
    return map[x][y];
}

robot_map::~robot_map(){
    data.clear();
}

bool robot_map::is_discovered(int x, int y) const {
    for(auto m : this->data){
        if(m.X == x && m.Y == y){
            return true;
        }
    }
    return false;
}

map_cell::map_cell() {
    X = NULL;
    Y = NULL;
    value = MYSTERY;
}

void robot_map::add_cell(int x, int y, cell_value val) {
    map_cell new_cell;
    new_cell.X = x;
    new_cell.Y = y;
    new_cell.value = val;

    this->data.push_back(new_cell);
}


cell_value robot_map::get_cell(int x, int y) const {
    for (auto m : data){
        if(m.X == x && m.Y == y){
            return m.value;
        }
    }
}

bool robot_map::is_added(int a, int b) {
    for (auto & m : data){
        if(m.X == a && m.Y == b){
            return true;
        }
    }
    return false;
}

bool is_added(int a, int b , std::vector<r_search> r_vector) {
    for (auto & m : r_vector){
        if(m.X == a && m.Y == b){
            return true;
        }
    }
    return false;
}
