//
// Created by Igor on 17.12.2020.
//

#include "robot.h"

robot::robot(){
    map.add_cell(0, 0, ROBOT_COLLECTOR);
    X = 0;
    Y = 0;
    apple_counter = 0;
}

void robot::scan(just_map& god_map) {
    cell_value tmp;
    if(god_map.robot_y+1 >= god_map.Y){
        tmp = BORDER;
    }else{
        tmp = god_map.map[god_map.robot_x][god_map.robot_y+1];
    }
    if(!map.is_added(X, Y+1)){
        map.add_cell(X, Y+1, tmp);
    }
    if(god_map.robot_x+1 >= god_map.X){
        tmp = BORDER;
    }else{
        tmp = god_map.map[god_map.robot_x+1][god_map.robot_y];
    }
    if(!map.is_added(X+1, Y)){
        map.add_cell(X+1, Y, tmp);
    }
    if(god_map.robot_x-1 < 0){
        tmp = BORDER;
    }else{
        tmp = god_map.map[god_map.robot_x-1][god_map.robot_y];
    }
    if(!map.is_added(X-1, Y)){
        map.add_cell(X-1, Y, tmp);
    }
    if(god_map.robot_y-1 < 0){
        tmp = BORDER;
    }else{
        tmp = god_map.map[god_map.robot_x][god_map.robot_y-1];
    }
    if(!map.is_added(X, Y-1)){
        map.add_cell(X, Y-1, tmp);
    }
}


void robot::move(move_command order, just_map& god_map) {
    cell_value tmp;
    cell_value border_check;
    if (order == RIGHT){
        for(auto & m : map.data){
            if(m.X == X && m.Y == Y+1){
                border_check = m.value;
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.map[god_map.robot_x][god_map.robot_y + 1];
            if (tmp == EMPTY || tmp == APPLE) {
                bool on_apple = false;
                if (god_map.apple_x == god_map.robot_x && god_map.apple_y == god_map.robot_y && can_take_apple) {
                    god_map.map[god_map.robot_x][god_map.robot_y] = APPLE;
                    on_apple = true;
                    for (auto &m : map.data) {
                        if (m.X == X && m.Y == Y) {
                            m.value = APPLE;
                        }
                    }
                    can_take_apple = false;
                }
                if (tmp == APPLE) {
                    god_map.apple_x = god_map.robot_x;
                    god_map.apple_y = god_map.robot_y + 1;
                    can_take_apple = true;
                }
                if (!on_apple) {
                    god_map.map[god_map.robot_x][god_map.robot_y] = EMPTY;
                    for (auto &m : map.data) {
                        if (m.X == X && m.Y == Y) {
                            m.value = EMPTY;
                        }
                    }
                }
                god_map.map[god_map.robot_x][god_map.robot_y + 1] = ROBOT_COLLECTOR;
                Y += 1;
                for (auto &m : map.data) {
                    if (m.X == X && m.Y == Y) {
                        m.value = ROBOT_COLLECTOR;
                    }
                }
                god_map.robot_y += 1;
            }
        }
    }
    if (order == DOWN){
        for(auto & m : map.data){
            if(m.X == X+1 && m.Y == Y){
                border_check = m.value;
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.map[god_map.robot_x + 1][god_map.robot_y];

            if (tmp == EMPTY || tmp == APPLE) {
                bool on_apple = false;
                if (god_map.apple_x == god_map.robot_x && god_map.apple_y == god_map.robot_y && can_take_apple) {
                    god_map.map[god_map.robot_x][god_map.robot_y] = APPLE;
                    on_apple = true;
                    for (auto &m : map.data) {
                        if (m.X == X && m.Y == Y) {
                            m.value = APPLE;
                        }
                    }
                    can_take_apple = false;
                }
                if (tmp == APPLE) {
                    god_map.apple_x = god_map.robot_x + 1;
                    god_map.apple_y = god_map.robot_y;
                    can_take_apple = true;
                }

                if (!on_apple) {
                    god_map.map[god_map.robot_x][god_map.robot_y] = EMPTY;
                    for (auto &m : map.data) {
                        if (m.X == X && m.Y == Y) {
                            m.value = EMPTY;
                        }
                    }

                }
                god_map.map[god_map.robot_x + 1][god_map.robot_y] = ROBOT_COLLECTOR;
                X += 1;
                for (auto &m : map.data) {
                    if (m.X == X && m.Y == Y) {
                        m.value = ROBOT_COLLECTOR;
                    }
                }
                god_map.robot_x += 1;
            }
        }
    }
    if (order == LEFT){
        for(auto & m : map.data){
            if(m.X == X && m.Y == Y-1){
                border_check = m.value;
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.map[god_map.robot_x][god_map.robot_y-1];

            if (tmp == EMPTY || tmp == APPLE) {
                bool on_apple = false;
                if (god_map.apple_x == god_map.robot_x && god_map.apple_y == god_map.robot_y && can_take_apple) {
                    god_map.map[god_map.robot_x][god_map.robot_y] = APPLE;
                    on_apple = true;
                    for (auto &m : map.data) {
                        if (m.X == X && m.Y == Y) {
                            m.value = APPLE;
                        }
                    }
                    can_take_apple = false;
                }
                if (tmp == APPLE) {
                    god_map.apple_x = god_map.robot_x;
                    god_map.apple_y = god_map.robot_y - 1;
                    can_take_apple = true;
                }
                if (!on_apple) {
                    god_map.map[god_map.robot_x][god_map.robot_y] = EMPTY;
                    for (auto &m : map.data) {
                        if (m.X == X && m.Y == Y) {
                            m.value = EMPTY;
                        }
                    }
                }
                god_map.map[god_map.robot_x][god_map.robot_y - 1] = ROBOT_COLLECTOR;
                Y -= 1;
                for (auto &m : map.data) {
                    if (m.X == X && m.Y == Y) {
                        m.value = ROBOT_COLLECTOR;
                    }
                }
                god_map.robot_y -= 1;
            }
        }
    }
    if (order == UP){
        for(auto & m : map.data){
            if(m.X == X-1 && m.Y == Y){
                border_check = m.value;
            }
        }
        if(border_check != BORDER) {

            tmp = god_map.map[god_map.robot_x-1][god_map.robot_y];
            if (tmp == EMPTY || tmp == APPLE) {
                bool on_apple = false;
                if (god_map.apple_x == god_map.robot_x && god_map.apple_y == god_map.robot_y && can_take_apple) {
                    god_map.map[god_map.robot_x][god_map.robot_y] = APPLE;
                    on_apple = true;
                    for (auto &m : map.data) {
                        if (m.X == X && m.Y == Y) {
                            m.value = APPLE;
                        }
                    }
                    can_take_apple = false;
                }
                if (tmp == APPLE) {
                    god_map.apple_x = god_map.robot_x - 1;
                    god_map.apple_y = god_map.robot_y;
                    can_take_apple = true;
                }
                if (!on_apple) {
                    god_map.map[god_map.robot_x][god_map.robot_y] = EMPTY;
                    for (auto &m : map.data) {
                        if (m.X == X && m.Y == Y) {
                            m.value = EMPTY;
                        }
                    }
                }
                god_map.map[god_map.robot_x - 1][god_map.robot_y] = ROBOT_COLLECTOR;
                X -= 1;
                for (auto &m : map.data) {
                    if (m.X == X && m.Y == Y) {
                        m.value = ROBOT_COLLECTOR;
                    }
                }
                god_map.robot_x -= 1;
            }
        }
    }
}

void robot::grab(just_map &god_map) {
    if(can_take_apple){
        apple_counter++;
        can_take_apple = false;
    }
}


void robot::draw_robot_map(just_map &god_map) {
    int max_x = 0;
    int max_y = 0;
    int min_x = 0;
    int min_y = 0;
    for(auto & m : map.data){
        if (m.value != BORDER) {
            if (m.X < min_x) {
                min_x = m.X;
            }
            if (m.X > max_x) {
                max_x = m.X;
            }
            if (m.Y < min_y) {
                min_y = m.Y;
            }
            if (m.Y > max_y) {
                max_y = m.Y;
            }
        }
    }


    max_x += god_map.set_robot_x;
    min_x += god_map.set_robot_x;
    max_y += god_map.set_robot_y;
    min_y += god_map.set_robot_y;

    for (int i = 0; i < god_map.X; i++){
        if(i <= max_x && i >= min_x){
            if(min_y > 0){
                for (int j = 0; j < min_y; j++){
                    std::cout << "? ";
                }
            }
            for (int j = min_y; j <= max_y; j++){
                if(map.is_discovered(i-god_map.set_robot_x, j-god_map.set_robot_y)){
                    if(map.get_cell(i-god_map.set_robot_x, j-god_map.set_robot_y) != BORDER) {
                        std::cout << to_map_sign(map.get_cell(i - god_map.set_robot_x, j - god_map.set_robot_y)) << " ";
                    }
                }else if(j > 0 || j < god_map.Y){
                    std:: cout << "? ";
                }
            }
            for (int j = max_y+1; j < god_map.Y; j++){
                std::cout << "? ";
            }
        }else if(i > 0 || i < god_map.X){
            for (int j = 0; j < god_map.Y; j++){
                std::cout << "? ";
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}