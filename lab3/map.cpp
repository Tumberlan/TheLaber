//
// Created by Igor on 17.12.2020.
//

#include "map.h"
#include <random>
#include <cmath>

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
        return '$';
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
        return '*';
    }
    return '?';
}

just_map::just_map() {
    int x = rand() % 2 + 10;
    int y = rand() % 2 + 10;

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

    a = X-1;
    b = Y-1;
    robot_x = a;
    robot_y = b;
    set_robot_x = a;
    set_robot_y = b;
    map[a][b] = ROBOT_COLLECTOR;
}



std::ostream& operator<<(std::ostream& os, const just_map& map_t){

    for(int i = 0; i < map_t.X; i++){
        for(int j = 0; j < map_t.Y; j++){
            std::cout << to_map_sign(map_t.map[i][j]) << " ";
        }
        std::cout << '\n';
    }

    std::cout << '\n';
    return os;
}


robot_map::~robot_map(){
    data.clear();
}

void robot_map::init_map() {

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


