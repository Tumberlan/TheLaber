//
// Created by Igor on 17.12.2020.
//

#include "robot.h"

robot::robot(){
    map.add_cell(0, 0, ROBOT_COLLECTOR);
    X = 0;
    Y = 0;
    r_map_rad = 10;
    apple_counter = 0;
}

move_command auto_command::get_value() {
    return value;
}

void auto_command::set_value(move_command val) {
    value = val;
}

int auto_command::get_idx() {
    return idx;
}

void auto_command::set_idx(int val) {
    idx = val;
}









void robot::scan(just_map& god_map) {
    cell_value tmp;
    if(god_map.get_robot_y()+1 >= god_map.get_Y()){
        tmp = BORDER;
    }else{
        tmp = god_map.get_map(god_map.get_robot_x(),god_map.get_robot_y()+1);
    }
    if(!map.is_added(X, Y+1)){
        map.add_cell(X, Y+1, tmp);
    }
    if(god_map.get_robot_x()+1 >= god_map.get_X()){
        tmp = BORDER;
    }else{
        tmp = god_map.get_map(god_map.get_robot_x()+1,god_map.get_robot_y());
    }
    if(!map.is_added(X+1, Y)){
        map.add_cell(X+1, Y, tmp);
    }
    if(god_map.get_robot_x()-1 < 0){
        tmp = BORDER;
    }else{
        tmp = god_map.get_map(god_map.get_robot_x()-1,god_map.get_robot_y());
    }
    if(!map.is_added(X-1, Y)){
        map.add_cell(X-1, Y, tmp);
    }
    if(god_map.get_robot_y()-1 < 0){
        tmp = BORDER;
    }else{
        tmp = god_map.get_map(god_map.get_robot_x(),god_map.get_robot_y()-1);
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
            if(m.get_X() == X && m.get_Y() == Y+1){
                border_check = m.get_value();
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.get_map(god_map.get_robot_x(),god_map.get_robot_y()+1);
            if (tmp == EMPTY || tmp == APPLE) {
                bool on_apple = false;
                if (god_map.get_apple_x() == god_map.get_robot_x() && god_map.get_apple_y() == god_map.get_robot_y() && can_take_apple) {
                    god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y(), APPLE);
                    on_apple = true;
                    for (auto &m : map.data) {
                        if (m.get_X() == X && m.get_Y() == Y) {
                            m.set_value(APPLE);
                        }
                    }
                    can_take_apple = false;
                }
                if (tmp == APPLE) {
                    god_map.set_apple_x(god_map.get_robot_x());
                    god_map.set_apple_y(god_map.get_robot_y()+1);
                    can_take_apple = true;
                }
                if (!on_apple) {
                    god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y(), EMPTY);
                    for (auto &m : map.data) {
                        if (m.get_X() == X && m.get_Y() == Y) {
                            m.set_value(EMPTY);
                        }
                    }
                }
                god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y()+1, ROBOT_COLLECTOR);
                Y += 1;
                if(abs(Y) >= r_map_rad-1){
                    r_map_rad = r_map_rad*2;
                }
                for (auto &m : map.data) {
                    if (m.get_X() == X && m.get_Y() == Y) {
                        m.set_value(ROBOT_COLLECTOR);
                    }
                }
                god_map.set_robot_y(god_map.get_robot_y()+1);
            }
        }
    }
    if (order == DOWN){
        for(auto & m : map.data){
            if(m.get_X() == X+1 && m.get_Y() == Y){
                border_check = m.get_value();
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.get_map(god_map.get_robot_x()+1, god_map.get_robot_y());

            if (tmp == EMPTY || tmp == APPLE) {
                bool on_apple = false;
                if (god_map.get_apple_x() == god_map.get_robot_x() && god_map.get_apple_y() == god_map.get_robot_y() && can_take_apple) {
                    god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y(), APPLE);
                    on_apple = true;
                    for (auto &m : map.data) {
                        if (m.get_X() == X && m.get_Y() == Y) {
                            m.set_value(APPLE);
                        }
                    }
                    can_take_apple = false;
                }
                if (tmp == APPLE) {
                    god_map.set_apple_x(god_map.get_robot_x() + 1);
                    god_map.set_apple_y(god_map.get_robot_y());
                    can_take_apple = true;
                }

                if (!on_apple) {
                    god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y(), EMPTY);
                    for (auto &m : map.data) {
                        if (m.get_X() == X && m.get_Y() == Y) {
                            m.set_value(EMPTY);
                        }
                    }

                }
                god_map.set_map(god_map.get_robot_x()+1,god_map.get_robot_y(), ROBOT_COLLECTOR);
                X += 1;
                if(abs(X) >= r_map_rad-1){
                    r_map_rad = r_map_rad*2;
                }
                for (auto &m : map.data) {
                    if (m.get_X() == X && m.get_Y() == Y) {
                        m.set_value(ROBOT_COLLECTOR);
                    }
                }
                god_map.set_robot_x(god_map.get_robot_x()+1);
            }
        }
    }
    if (order == LEFT){
        for(auto & m : map.data){
            if(m.get_X() == X && m.get_Y() == Y-1){
                border_check = m.get_value();
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.get_map(god_map.get_robot_x(), god_map.get_robot_y()-1);

            if (tmp == EMPTY || tmp == APPLE) {
                bool on_apple = false;
                if (god_map.get_apple_x() == god_map.get_robot_x() && god_map.get_apple_y() == god_map.get_robot_y() && can_take_apple) {
                    god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y(), APPLE);
                    on_apple = true;
                    for (auto &m : map.data) {
                        if (m.get_X() == X && m.get_Y() == Y) {
                            m.set_value(APPLE);
                        }
                    }
                    can_take_apple = false;
                }
                if (tmp == APPLE) {
                    god_map.set_apple_x(god_map.get_robot_x());
                    god_map.set_apple_y(god_map.get_robot_y() - 1);
                    can_take_apple = true;
                }
                if (!on_apple) {
                    god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y(), EMPTY);
                    for (auto &m : map.data) {
                        if (m.get_X() == X && m.get_Y() == Y) {
                            m.set_value(EMPTY);
                        }
                    }
                }
                god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y()-1, ROBOT_COLLECTOR);
                Y -= 1;
                if(abs(Y) >= r_map_rad-1){
                    r_map_rad = r_map_rad*2;
                }
                for (auto &m : map.data) {
                    if (m.get_X() == X && m.get_Y() == Y) {
                        m.set_value(ROBOT_COLLECTOR);
                    }
                }
                god_map.set_robot_y(god_map.get_robot_y() - 1);
            }
        }
    }
    if (order == UP){
        for(auto & m : map.data){
            if(m.get_X() == X-1 && m.get_Y() == Y){
                border_check = m.get_value();
            }
        }
        if(border_check != BORDER) {

            tmp = god_map.get_map(god_map.get_robot_x()-1,god_map.get_robot_y());
            if (tmp == EMPTY || tmp == APPLE) {
                bool on_apple = false;
                if (god_map.get_apple_x() == god_map.get_robot_x() && god_map.get_apple_y() == god_map.get_robot_y() && can_take_apple) {
                    god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y(), APPLE);
                    on_apple = true;
                    for (auto &m : map.data) {
                        if (m.get_X() == X && m.get_Y() == Y) {
                            m.set_value(APPLE);
                        }
                    }
                    can_take_apple = false;
                }
                if (tmp == APPLE) {
                    god_map.set_apple_x(god_map.get_robot_x() - 1);
                    god_map.set_apple_y(god_map.get_robot_y());
                    can_take_apple = true;
                }
                if (!on_apple) {
                    god_map.set_map(god_map.get_robot_x(),god_map.get_robot_y(), EMPTY);
                    for (auto &m : map.data) {
                        if (m.get_X() == X && m.get_Y() == Y) {
                            m.set_value(EMPTY);
                        }
                    }
                }
                god_map.set_map(god_map.get_robot_x()-1,god_map.get_robot_y(), ROBOT_COLLECTOR);
                X -= 1;
                if(abs(X) >= r_map_rad-1){
                    r_map_rad = r_map_rad*2;
                }
                for (auto &m : map.data) {
                    if (m.get_X() == X && m.get_Y() == Y) {
                        m.set_value(ROBOT_COLLECTOR);
                    }
                }
                god_map.set_robot_x(god_map.get_robot_x() - 1);
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

    int max_x = 10 + god_map.get_robot_x();
    int min_x = -10 + god_map.get_robot_x();
    int max_y = 10 + god_map.get_robot_y();
    int min_y = -10 + god_map.get_robot_y();

    int max_temp_x = god_map.get_plug_robot_x() + r_map_rad;
    if(max_temp_x > 1000){
        max_temp_x = 1000;
    }
    int min_temp_x = god_map.get_plug_robot_x() - r_map_rad;
    if(min_temp_x < 0){
        min_temp_x = 0;
    }
    int max_temp_y = god_map.get_plug_robot_y() + r_map_rad;
    if(max_temp_y > 1000){
        max_temp_y = 1000;
    }
    int min_temp_y = god_map.get_plug_robot_y() - r_map_rad;
    if(min_temp_y < 0){
        min_temp_y = 0;
    }


    if(min_x < 0){
        min_x = 0;
    }
    if(max_x > 1000){
        max_x = 1000;
    }
    if(min_y < 0){
        min_y = 0;
    }
    if(max_y > 1000){
        max_y = 1000;
    }
    for(int i = min_x; i < max_x; i++){
        for(int j = min_y; j < max_y; j++){
            if(map.is_discovered(i-god_map.get_plug_robot_x(), j-god_map.get_plug_robot_y())){
                if(map.get_cell(i-god_map.get_plug_robot_x(), j-god_map.get_plug_robot_y()) != BORDER) {
                    if(god_map.get_plug_robot_x()+X == i && god_map.get_plug_robot_y()+Y == j){
                        std::cout << to_map_sign(ROBOT_COLLECTOR) << " ";
                    }else {
                        std::cout << to_map_sign(map.get_cell(i - god_map.get_plug_robot_x(), j - god_map.get_plug_robot_y()))
                                  << " ";
                    }
                }
            }else if(j > min_temp_y || j < max_temp_y){
                std:: cout << "? ";
            }
        }
        std::cout << '\n';
    }
    std::cout << "Autobot got: "<< apple_counter << " apples" << '\n';
}



int robot::step_amount(std::string str, int a){
    int mul = 1;
    if(a > 1) {
        for (int i = 0; i < a-1; i++) {
            mul = mul * 10;
        }
    }

    int result = 0;
    for (int i = 0; i < a; i++){
        result += (int)(str[i]-'0')*mul;
        mul = mul/10;
    }

    return result;
}


// РЕАЛИЗАЦИЯ СКАНЕРА
void robot::add_siblings(int x, int y, int to_from, std::vector<r_search>& from_r, std::vector<r_search>& to_r) {
    for(auto & i : from_r){
        if((i.get_X() == x+1 && i.get_Y() == y) || ((i.get_X() == x-1 && i.get_Y() == y)) || ((i.get_X() == x && i.get_Y() == y+1)) || ((i.get_X() == x && i.get_Y() == y-1))){
            if(is_added(X,Y,to_r)){
                if(to_from+1 < i.get_to_from_point()){
                    i.set_to_from_point(to_from+1);
                    i.set_from_to_sum(i.get_to_from_point() + i.get_to_go_point());
                    i.set_previous_x(x);
                    i.set_previous_y(y);
                }
            }else{
                r_search new_cell;
                new_cell.set_X(i.get_X());
                new_cell.set_Y(i.get_Y());
                new_cell.set_previous_x(x);
                new_cell.set_previous_y(y);
                new_cell.set_value(i.get_value());
                new_cell.set_to_from_point(to_from+1);
                new_cell.set_to_go_point(i.get_to_go_point());
                new_cell.set_from_to_sum(new_cell.get_to_from_point() + new_cell.get_to_go_point());
                to_r.push_back(new_cell);
            }
        }
    }
}

void take_step_back(int iterator, r_search tmp, std::vector<auto_command>& way_out){
    int x_move = tmp.get_X() - tmp.get_previous_x();
    int y_move = tmp.get_Y() - tmp.get_previous_y();
    auto_command temp_command;
    if(x_move == 1 && y_move == 0){
        temp_command.set_value(DOWN);
    }else if(x_move == -1 && y_move == 0){
        temp_command.set_value(UP);
    }else if(x_move == 0 && y_move == 1){
        temp_command.set_value(RIGHT);
    }else if(x_move == 0 && y_move == -1){
        temp_command.set_value(LEFT);
    }

    temp_command.set_idx(iterator);
    way_out.push_back(temp_command);
}




void robot::shortest_way(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map , just_map& god_map) {

    int tmp_rob_x = X + maximum_x;
    int tmp_rob_y = Y + maximum_y;

    std::vector<r_search> reach_data;



    for(auto & m : map.data){
        if(m.get_value() == APPLE){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);
            new_cell.set_Y(m.get_Y()+maximum_y);
            new_cell.set_value(APPLE);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == EMPTY){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);;
            new_cell.set_Y(m.get_Y()+maximum_y);;
            new_cell.set_value(EMPTY);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);;
            new_cell.set_Y(m.get_Y()+maximum_y);;
            new_cell.set_value(ROBOT_COLLECTOR);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
    }


    std::vector<r_search> reachable;



    add_siblings(tmp_rob_x, tmp_rob_y, 0, reach_data, reachable);



    std::vector<r_search> explored;

    for(int i = 0; i < reach_data.size(); i++){
        if(reach_data[i].get_value() == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.set_X(reach_data[i].get_X());
            new_cell.set_Y(reach_data[i].get_Y());
            new_cell.set_value(reach_data[i].get_value());
            explored.push_back(new_cell);
        }
    }





    int x_to_find;
    int y_to_find;
    int itr = 1;
    bool is_reached = false;
    while(!is_reached){
        r_search tmp;
        tmp.set_to_go_point(1000);
        tmp.set_to_from_point(1000);
        tmp.set_from_to_sum(2000);
        for(auto & i : reachable){
            if(i.get_from_to_sum() <= tmp.get_from_to_sum()){
                if(!is_added(i.get_X(), i.get_Y(), explored)) {
                    if (i.get_from_to_sum() == tmp.get_from_to_sum()) {
                        if (i.get_to_go_point() < tmp.get_to_from_point()) {
                            tmp = i;
                        }
                    }
                    if (i.get_from_to_sum() < tmp.get_from_to_sum()) {
                        tmp = i;
                    }
                }
            }
        }



        explored.push_back(tmp);
        for (int i = 0; i < reachable.size(); i++){
            if(reachable[i].get_X() == tmp.get_X() && reachable[i].get_Y() == tmp.get_Y()){
                reachable.erase(reachable.begin() + i);
            }
        }
        add_siblings(tmp.get_X(), tmp.get_Y(), tmp.get_to_from_point(), reach_data, reachable);

        if((abs(tmp.get_X() - x_in_search) + abs(tmp.get_Y() - y_in_search)) == 1){
            is_reached = true;
        }

        itr++;

    }



    // обратный путь по explored-у
    r_search tmp;
    for(auto & i : explored){
        if((abs(i.get_X() - x_in_search)  + abs(i.get_Y()- y_in_search)) == 1){
            tmp = i;
        }
    }


    std::vector<auto_command> way_out;
    int iterator = 1;
    while(tmp.get_X() != tmp_rob_x || tmp.get_Y() != tmp_rob_y){
        take_step_back(iterator, tmp, way_out);
        for (int i = 0; i < explored.size(); i++){
            if(explored[i].get_X() == tmp.get_previous_x() && explored[i].get_Y() == tmp.get_previous_y()){
                tmp = explored[i];
            }
        }
        iterator++;

    }




    iterator--;
    for (; iterator > 0; iterator--) {
        for (int i = 0; i < way_out.size(); i++) {
            if (way_out[i].get_idx() == iterator) {
                move(way_out[i].get_value(), god_map);
            }
        }
    }


    reach_data.clear();
    reachable.clear();
    explored.clear();
    way_out.clear();

}

bool is_blocked(int i, int j, int max_x, int max_y, cell_value **tmp_map){
    bool left = true;
    bool down = true;
    bool right = true;
    bool up = true;
    if (i+1 > 2*max_x){
        right = false;
    }else {
        if(tmp_map[i+1][j] == BORDER || tmp_map[i+1][j] == BOMB || tmp_map[i+1][j] == ROCK || tmp_map[i+1][j] == ROBOT_SAPPER || tmp_map[i+1][j] == MYSTERY){
            right = false;
        }
    }
    if(i-1 < 0){
        left = false;
    }else{
        if(tmp_map[i-1][j] == BORDER || tmp_map[i-1][j] == BOMB || tmp_map[i-1][j] == ROCK || tmp_map[i-1][j] == ROBOT_SAPPER || tmp_map[i-1][j] == MYSTERY){
            left = false;
        }
    }
    if(j+1 > 2*max_y){
        up = false;
    }else{
        if(tmp_map[i][j+1] == BORDER || tmp_map[i][j+1] == BOMB || tmp_map[i][j+1] == ROCK || tmp_map[i][j+1] == ROBOT_SAPPER || tmp_map[i][j+1] == MYSTERY){
            up = false;
        }
    }
    if(j-1 < 0){
        down = false;
    }else {
        if(tmp_map[i][j-1] == BORDER || tmp_map[i][j-1] == BOMB || tmp_map[i][j-1] == ROCK || tmp_map[i][j-1] == ROBOT_SAPPER || tmp_map[i][j-1] == MYSTERY){
            down = false;
        }
    }

    if(!up && !down && !left && !right){
        return true;
    }
    return false;
}




void robot::autobot(int N, just_map &god_map) {
    N = N-1;
    scan(god_map);
    draw_robot_map(god_map);
    int max_x = 0;
    int max_y = 0;
    int min_x = 0;
    int min_y = 0;
    for(int iterator = 0; iterator < N; iterator++){
        for (auto & m : map.data){
            if (m.get_X() > max_x){
                max_x = m.get_X();
            }
            if (m.get_Y() > max_y){
                max_y = m.get_Y();
            }
            if (m.get_X() < min_x){
                min_x = m.get_X();
            }
            if (m.get_Y() < min_y){
                min_y = m.get_Y();
            }
        }

        int maximum_x, maximum_y;
        if(max_x >= abs(min_x)){
            maximum_x = max_x;
        }else {
            maximum_x = abs(min_x);
        }
        if(max_y >= abs(min_y)){
            maximum_y = max_y;
        }else {
            maximum_y = abs(min_y);
        }
        cell_value ** tmp_map;
        tmp_map = new cell_value*[2*maximum_x+1];

        for(int i = 0; i < 2*maximum_x + 1; i++){
            tmp_map[i] = new cell_value[2*maximum_y+1];
        }

        for (int i = 0; i < 2 * maximum_x + 1; i++){
            for(int j = 0; j < 2 * maximum_y + 1; j++){
                tmp_map[i][j] = MYSTERY;
            }
        }


        int min_r_x = 1000;
        int min_r_y = 1000;

        int tmp_rob_x;
        int tmp_rob_y;
        for (auto & i : map.data){
            if(i.get_value() == ROBOT_COLLECTOR){
                tmp_rob_x = i.get_X() + maximum_x;
                tmp_rob_y = i.get_Y() + maximum_y;
            }
            tmp_map[i.get_X()+maximum_x][i.get_Y()+maximum_y] = i.get_value();
        }



        int tmp_sum = min_r_x+min_r_y;
        for (int i = 0; i < 2 * maximum_x + 1; i++){
            for(int j = 0; j < 2 * maximum_y + 1; j++){
                if(tmp_map[i][j] == MYSTERY){
                    if((abs(i-tmp_rob_x)+abs(j-tmp_rob_y)) < tmp_sum){
                        if(!is_blocked(i, j, max_x, max_y, tmp_map)) {
                            min_r_x = i - tmp_rob_x;
                            min_r_y = j - tmp_rob_y;
                            tmp_sum = abs(min_r_x) + abs(min_r_y);
                        }
                    }
                }
            }
        }

        int to_go_x = min_r_x + tmp_rob_x;
        int to_go_y = min_r_y + tmp_rob_y;


        shortest_way(to_go_x, to_go_y, maximum_x, maximum_y, tmp_map, god_map);
        scan(god_map);

        draw_robot_map(god_map);
    }

}

// РЕАЛИЗАЦИЯ СБОРЩИКА ЯБЛОК

void robot::shortest_coll(int x_in_search, int y_in_search, int maximum_x, int maximum_y, cell_value **tmp_map,just_map &god_map) {
    int tmp_rob_x = X + maximum_x;
    int tmp_rob_y = Y + maximum_y;

    std::vector<r_search> reach_data;

    for(auto & m : map.data){
        if(m.get_value() == APPLE){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);
            new_cell.set_Y(m.get_Y()+maximum_y);
            new_cell.set_value(APPLE);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == EMPTY){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);;
            new_cell.set_Y(m.get_Y()+maximum_y);;
            new_cell.set_value(EMPTY);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);;
            new_cell.set_Y(m.get_Y()+maximum_y);;
            new_cell.set_value(ROBOT_COLLECTOR);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == ROBOT_SAPPER){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);;
            new_cell.set_Y(m.get_Y()+maximum_y);;
            new_cell.set_value(ROBOT_SAPPER);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
    }


    std::vector<r_search> reachable;



    add_siblings(tmp_rob_x, tmp_rob_y, 0, reach_data, reachable);



    std::vector<r_search> explored;

    for(int i = 0; i < reach_data.size(); i++){
        if(reach_data[i].get_value() == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.set_X(reach_data[i].get_X());
            new_cell.set_Y(reach_data[i].get_Y());
            new_cell.set_value(reach_data[i].get_value());
            explored.push_back(new_cell);
        }
    }





    int x_to_find;
    int y_to_find;
    int itr = 1;
    bool is_reached = false;
    while(!is_reached){
        r_search tmp;
        tmp.set_to_go_point(1000);
        tmp.set_to_from_point(1000);
        tmp.set_from_to_sum(2000);
        for(auto & i : reachable){
            if(i.get_from_to_sum() <= tmp.get_from_to_sum()){
                if(!is_added(i.get_X(), i.get_Y(), explored)) {
                    if (i.get_from_to_sum() == tmp.get_from_to_sum()) {
                        if (i.get_to_go_point() < tmp.get_to_from_point()) {
                            tmp = i;
                        }
                    }
                    if (i.get_from_to_sum() < tmp.get_from_to_sum()) {
                        tmp = i;
                    }
                }
            }
        }


        explored.push_back(tmp);
        for (int i = 0; i < reachable.size(); i++){
            if(reachable[i].get_X() == tmp.get_X() && reachable[i].get_Y() == tmp.get_Y()){
                reachable.erase(reachable.begin() + i);
            }
        }
        add_siblings(tmp.get_X(), tmp.get_Y(), tmp.get_to_from_point(), reach_data, reachable);

        if((abs(tmp.get_X() - x_in_search) + abs(tmp.get_Y() - y_in_search)) == 1){
            is_reached = true;
        }

        itr++;

    }


    // обратный путь по explored-у
    r_search tmp;
    for(auto & i : explored){
        if((abs(i.get_X() - x_in_search)  + abs(i.get_Y()- y_in_search)) == 1){
            tmp = i;
        }
    }

    std::vector<auto_command> way_out;
    int iterator = 1;
    while(tmp.get_X() != tmp_rob_x || tmp.get_Y() != tmp_rob_y){
        take_step_back(iterator, tmp, way_out);
        for (int i = 0; i < explored.size(); i++){
            if(explored[i].get_X() == tmp.get_previous_x() && explored[i].get_Y() == tmp.get_previous_y()){
                tmp = explored[i];
            }
        }
        iterator++;

    }



    iterator--;
    for(int i = 0; i < way_out.size(); i++){
        if(way_out[i].get_idx() == iterator){
            move(way_out[i].get_value(), god_map);
        }
    }

    reach_data.clear();
    reachable.clear();
    explored.clear();
    way_out.clear();
}

void robot::make_collector_move(int tmp_rob_x, int tmp_rob_y, int maximum_x, int maximum_y,std::vector<map_cell> &apple_positions, cell_value **tmp_map, just_map &god_map) {


    int tmp_sum = -1;
    map_cell tmp;



    for (int iterator = 0; iterator < apple_positions.size(); iterator++) {
        if ((abs(apple_positions[iterator].get_X() - (X+maximum_x)) + abs(apple_positions[iterator].get_Y() - (Y + maximum_y)) <tmp_sum || tmp_sum == -1) && apple_positions[iterator].get_value() == APPLE) {
            tmp_sum = abs(apple_positions[iterator].get_X() - (X+maximum_x)) + abs(apple_positions[iterator].get_Y() - (Y + maximum_y));
            tmp = apple_positions[iterator];
        }
    }




    if (abs(tmp.get_X() - (X + maximum_x)) + abs(tmp.get_Y() - (Y + maximum_y)) > 1) {
        shortest_coll(tmp.get_X(), tmp.get_Y(), maximum_x, maximum_y, tmp_map, god_map);
    } else {
        int x_move = tmp.get_X() - (X + maximum_x);
        int y_move = tmp.get_Y() - (Y + maximum_y);
        if (x_move == 1 && y_move == 0) {
            move(DOWN, god_map);
        } else if (x_move == -1 && y_move == 0) {
            move(UP, god_map);
        } else if (x_move == 0 && y_move == 1) {
            move(RIGHT, god_map);
        } else if (x_move == 0 && y_move == -1) {
            move(LEFT, god_map);
        }
        grab(god_map);
        for (int i = 0; i < apple_positions.size(); i++) {
            if (apple_positions[i].get_X() == tmp.get_X() && apple_positions[i].get_Y() == tmp.get_Y()) {
                apple_positions.erase(apple_positions.begin() + i);
            }
        }

    }

   // std:: cout <<" NOT COLL MOVE"<<'\n';
}



void robot::apple_collector(just_map& god_map){

    if(can_take_apple){
        grab(god_map);
    }

    int max_y = 0;
    int min_y = 0;
    int max_x = 0;
    int min_x = 0;


    for(int i = 0; i < map.data.size(); i++){

        if (map.data[i].get_X() > max_x){
            max_x = map.data[i].get_X();
        }
        if (map.data[i].get_Y() > max_y){
            max_y = map.data[i].get_Y();
        }
        if (map.data[i].get_X() < min_x){
            min_x = map.data[i].get_X();
        }
        if (map.data[i].get_Y() < min_y){
            min_y = map.data[i].get_Y();
        }

    }



    int maximum_x, maximum_y;
    if(max_x >= abs(min_x)){
        maximum_x = max_x;
    }else {
        maximum_x = abs(min_x);
    }
    if(max_y >= abs(min_y)){
        maximum_y = max_y;
    }else {
        maximum_y = abs(min_y);
    }
    cell_value ** tmp_map;
    tmp_map = new cell_value*[2*maximum_x+1];

    for(int i = 0; i < 2*maximum_x + 1; i++){
        tmp_map[i] = new cell_value[2*maximum_y+1];
    }

    for (int i = 0; i < 2 * maximum_x + 1; i++){
        for(int j = 0; j < 2 * maximum_y + 1; j++){
            tmp_map[i][j] = MYSTERY;
        }
    }


    int tmp_rob_x;
    int tmp_rob_y;
    int tmp_sap_x;
    int tmp_sap_y;
    for (auto & i : map.data){
        if(i.get_value() == ROBOT_COLLECTOR){
            tmp_rob_x = i.get_X() + maximum_x;
            tmp_rob_y = i.get_Y() + maximum_y;
        }
        if(i.get_value() == ROBOT_SAPPER){
            tmp_sap_x = i.get_X() + maximum_x;
            tmp_sap_y = i.get_Y() + maximum_y;
        }
        tmp_map[i.get_X()+maximum_x][i.get_Y()+maximum_y] = i.get_value();
    }


    std::vector<map_cell> apple_positions;
    for(int i = 0 ; i < map.data.size(); i++){
        if(map.data[i].get_value() == APPLE){
            map_cell new_cell;
            new_cell.set_value(APPLE);
            new_cell.set_X(map.data[i].get_X() + maximum_x);
            new_cell.set_Y(map.data[i].get_Y() + maximum_y);
            apple_positions.push_back(new_cell);
        }
    }

    for (int i = 0; i < apple_positions.size(); i++){
        std::cout << apple_positions[i].get_X() << " " << apple_positions[i].get_Y() << '\n';
    }
    std::vector<map_cell> bomb_positions;
    for(int i = 0 ; i < map.data.size(); i++){
        if(map.data[i].get_value() == BOMB){
            map_cell new_cell;
            new_cell.set_value(BOMB);
            new_cell.set_X(map.data[i].get_X() + maximum_x);
            new_cell.set_Y(map.data[i].get_Y() + maximum_y);
            bomb_positions.push_back(new_cell);
        }
    }



    while (apple_positions.size() != 0) {

        make_collector_move(X, Y, maximum_x, maximum_y, apple_positions, tmp_map,god_map);
        if(sapp_on) {
            make_sapp_move(sapper_x, sapper_y, maximum_x, maximum_y, bomb_positions, tmp_map, god_map);
        }
        draw_robot_map(god_map);
    }



    apple_positions.clear();
    bomb_positions.clear();
}


// САПЁР

void robot::set_sapper(just_map &god_map) {
    int tmp_x;
    int tmp_y;
    int tmp_idx;
    for(int i = 0; i < map.data.size(); i++){
        int iter = rand()%50;
        if(map.data[i].get_value() == EMPTY && iter>0){
            tmp_x = map.data[i].get_X();
            tmp_y = map.data[i].get_Y();
            tmp_idx = i;
            iter--;
        }
    }

    map.data[tmp_idx].set_value(ROBOT_SAPPER);
    god_map.set_sapper_x(tmp_x+god_map.get_plug_robot_x());
    god_map.set_sapper_y(tmp_y+god_map.get_plug_robot_y());
    god_map.set_map(god_map.get_sapper_x(), god_map.get_sapper_y(), ROBOT_SAPPER);
    sapper_x = tmp_x;
    sapper_y = tmp_y;
    sapp_on = true;
}

void robot::destroy_sapper(just_map &god_map){
    int tmp_x;
    int tmp_y;
    for(int i = 0; i < map.data.size(); i++){

        if(map.data[i].get_value() == ROBOT_SAPPER){
            tmp_x = map.data[i].get_X();
            tmp_y = map.data[i].get_Y();
            map.data[i].set_value(EMPTY);
            continue;
        }
    }

    god_map.set_sapper_x(-1);
    god_map.set_sapper_y(-1);
    god_map.set_map(tmp_x+god_map.get_plug_robot_x(), tmp_y+god_map.get_plug_robot_y(), EMPTY);
    sapper_x = -1;
    sapper_y = -1;
    sapp_on = false;
}

void robot::move_sapper(move_command order, just_map &god_map) {
    cell_value tmp;
    cell_value border_check;
    if (order == RIGHT){
        for(auto & m : map.data){
            if(m.get_X() == sapper_x && m.get_Y() == sapper_y+1){
                border_check = m.get_value();
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.get_map(god_map.get_sapper_x(), god_map.get_sapper_y() + 1);
            if(tmp == ROBOT_COLLECTOR){
                move(RIGHT, god_map);
            }
            tmp = god_map.get_map(god_map.get_sapper_x(), god_map.get_sapper_y() + 1);
            if (tmp == EMPTY || tmp == BOMB || tmp == APPLE) {

                bool on_apple = false;
               // std::cout << god_map.sap_apple_x << " " << god_map.sap_apple_y << " sap " << god_map.sapper_x << " " << god_map.sapper_y << '\n';
                if(god_map.get_sap_apple_x() == god_map.get_sapper_x() && god_map.get_sap_apple_y() == god_map.get_sapper_y() && can_smash_apple){
                    god_map.set_map(god_map.get_sapper_x(),god_map.get_sapper_y(), APPLE);
                    on_apple = true;
                    for(auto &m : map.data){
                        if(m.get_X() == sapper_x && m.get_Y() == sapper_y){
                            m.set_value(APPLE);
                        }
                    }
                    can_smash_apple = false;
                }

                if(tmp == APPLE){
                    god_map.set_sap_apple_x(god_map.get_sapper_x());
                    god_map.set_sap_apple_y(god_map.get_sapper_y() + 1);
                    can_smash_apple = true;
                }


                if(!on_apple){
                    god_map.set_map(god_map.get_sapper_x(), god_map.get_sapper_y(), EMPTY);
                    for (auto &m : map.data) {
                        if (m.get_X() == sapper_x && m.get_Y() == sapper_y) {
                            m.set_value(EMPTY);
                        }
                    }
                }
                for (auto &m : map.data) {
                    if (m.get_value() == ROBOT_SAPPER) {
                    }
                }

                god_map.set_map(god_map.get_sapper_x(), god_map.get_sapper_y()+1, ROBOT_SAPPER);
                sapper_y += 1;

                for (auto &m : map.data) {
                    if (m.get_X() == sapper_x && m.get_Y() == sapper_y) {
                        m.set_value(ROBOT_SAPPER);
                    }
                }
                god_map.set_sapper_y(god_map.get_sapper_y() + 1);
            }
        }
    }
    if (order == DOWN){
        for(auto & m : map.data){
            if(m.get_X() == sapper_x+1 && m.get_Y() == sapper_y){
                border_check = m.get_value();
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.get_map(god_map.get_sapper_x()+1, god_map.get_sapper_y());
            if(tmp == ROBOT_COLLECTOR){
                move(DOWN, god_map);
            }
            tmp = god_map.get_map(god_map.get_sapper_x()+1, god_map.get_sapper_y());
            if (tmp == EMPTY || tmp == BOMB || tmp == APPLE) {

                bool on_apple = false;
                //std::cout << god_map.sap_apple_x << " " << god_map.sap_apple_y << " sap " << god_map.sapper_x << " " << god_map.sapper_y << '\n';
                if(god_map.get_sap_apple_x() == god_map.get_sapper_x() && god_map.get_sap_apple_y() == god_map.get_sapper_y() && can_smash_apple){
                    god_map.set_map(god_map.get_sapper_x(), god_map.get_sapper_y(), APPLE);
                    on_apple = true;
                    for(auto &m : map.data){
                        if(m.get_X() == sapper_x && m.get_Y() == sapper_y){
                            m.set_value(APPLE);
                        }
                    }
                    can_smash_apple = false;
                }

                if(tmp == APPLE){
                    god_map.set_sap_apple_x(god_map.get_sapper_x() + 1);
                    god_map.set_sap_apple_y(god_map.get_sapper_y());
                    can_smash_apple = true;
                }


                if(!on_apple){
                    god_map.set_map(god_map.get_sapper_x(), god_map.get_sapper_y(), EMPTY);
                    for (auto &m : map.data) {
                        if (m.get_X() == sapper_x && m.get_Y() == sapper_y) {
                            m.set_value(EMPTY);
                        }
                    }
                }
                god_map.set_map(god_map.get_sapper_x()+1, god_map.get_sapper_y(), ROBOT_SAPPER);
                sapper_x += 1;

                for (auto &m : map.data) {
                    if (m.get_X() == sapper_x && m.get_Y() == sapper_y) {
                        m.set_value(ROBOT_SAPPER);
                    }
                }
                god_map.set_sapper_x(god_map.get_sapper_x() + 1);
            }
        }
    }
    if (order == LEFT){
        for(auto & m : map.data){
            if(m.get_X() == sapper_x && m.get_Y() == sapper_y-1){
                border_check = m.get_value();
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.get_map(god_map.get_sapper_x(), god_map.get_sapper_y()-1);
            if(tmp == ROBOT_COLLECTOR){
                move(LEFT, god_map);
            }
            tmp = god_map.get_map(god_map.get_sapper_x(), god_map.get_sapper_y()-1);

            if (tmp == EMPTY || tmp == BOMB || tmp == APPLE) {
                bool on_apple = false;
                //std::cout << god_map.sap_apple_x << " " << god_map.sap_apple_y << " sap " << god_map.sapper_x << " " << god_map.sapper_y << '\n';
                if(god_map.get_sap_apple_x() == god_map.get_sapper_x() && god_map.get_sap_apple_y() == god_map.get_sapper_y() && can_smash_apple){
                    god_map.set_map(god_map.get_sapper_x(), god_map.get_sapper_y(), APPLE);
                    on_apple = true;
                    for(auto &m : map.data){
                        if(m.get_X() == sapper_x && m.get_Y() == sapper_y){
                            m.set_value(APPLE);
                        }
                    }
                    can_smash_apple = false;
                }

                if(tmp == APPLE){
                    god_map.set_sap_apple_x(god_map.get_sapper_x());
                    god_map.set_sap_apple_y( god_map.get_sapper_y() -1);
                    can_smash_apple = true;
                }

                if(!on_apple){
                    god_map.set_map(god_map.get_sapper_x(), god_map.get_sapper_y(), EMPTY);
                    for (auto &m : map.data) {
                        if (m.get_X() == sapper_x && m.get_Y() == sapper_y) {
                            m.set_value(EMPTY);
                        }
                    }
                }

                god_map.set_map(god_map.get_sapper_x(), god_map.get_sapper_y()-1, ROBOT_SAPPER);
                sapper_y -= 1;

                for (auto &m : map.data) {
                    if (m.get_X() == sapper_x && m.get_Y() == sapper_y) {
                        m.set_value(ROBOT_SAPPER);
                    }
                }
                god_map.set_sapper_y(god_map.get_sapper_y() - 1);
            }
        }
    }
    if (order == UP){
        for(auto & m : map.data){
            if(m.get_X() == sapper_x-1 && m.get_Y() == sapper_y){
                border_check = m.get_value();
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.get_map(god_map.get_sapper_x()-1, god_map.get_sapper_y());
            if(tmp == ROBOT_COLLECTOR){
                move(UP, god_map);
            }
            tmp = god_map.get_map(god_map.get_sapper_x()-1, god_map.get_sapper_y());
            if (tmp == EMPTY || tmp == BOMB || tmp == APPLE) {

                bool on_apple = false;
                //std::cout << god_map.sap_apple_x << " " << god_map.sap_apple_y << " sap " << god_map.sapper_x << " " << god_map.sapper_y << '\n';
                if(god_map.get_sap_apple_x() == god_map.get_sapper_x() && god_map.get_sap_apple_y() == god_map.get_sapper_y() && can_smash_apple){
                    god_map.set_map(god_map.get_sapper_x(),god_map.get_sapper_y(), APPLE);
                    on_apple = true;
                    for(auto &m : map.data){
                        if(m.get_X() == sapper_x && m.get_Y() == sapper_y){
                            m.set_value(APPLE);
                        }
                    }
                    can_smash_apple = false;
                }

                if(tmp == APPLE){
                    god_map.set_sap_apple_x(god_map.get_sapper_x() - 1);
                    god_map.set_sap_apple_y(god_map.get_sapper_y());
                    can_smash_apple = true;
                }


                if(!on_apple){
                    god_map.set_map(god_map.get_sapper_x(),god_map.get_sapper_y(), EMPTY);
                    for (auto &m : map.data) {
                        if (m.get_X() == sapper_x && m.get_Y() == sapper_y) {
                            m.set_value(EMPTY);
                        }
                    }
                }

                god_map.set_map(god_map.get_sapper_x()-1,god_map.get_sapper_y(), ROBOT_SAPPER);
                sapper_x -= 1;

                for (auto &m : map.data) {
                    if (m.get_X() == sapper_x && m.get_Y() == sapper_y) {
                        m.set_value(ROBOT_SAPPER);
                    }
                }
                god_map.set_sapper_x(god_map.get_sapper_x() - 1);
            }
        }
    }
}






void robot::shortest_sapp(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map){


    int tmp_rob_x = sapper_x + maximum_x;
    int tmp_rob_y = sapper_y + maximum_y;

    std::vector<r_search> reach_data;

    for(auto & m : map.data){
        if(m.get_value() == BOMB){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);
            new_cell.set_Y(m.get_Y()+maximum_y);
            new_cell.set_value(BOMB);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == APPLE){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);
            new_cell.set_Y(m.get_Y()+maximum_y);
            new_cell.set_value(APPLE);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == EMPTY){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);
            new_cell.set_Y(m.get_Y()+maximum_y);
            new_cell.set_value(EMPTY);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);
            new_cell.set_Y(m.get_Y()+maximum_y);
            new_cell.set_value(ROBOT_COLLECTOR);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
        if(m.get_value() == ROBOT_SAPPER){
            r_search new_cell;
            new_cell.set_X(m.get_X()+maximum_x);
            new_cell.set_Y(m.get_Y()+maximum_y);
            new_cell.set_value(ROBOT_SAPPER);
            new_cell.set_to_go_point(abs(new_cell.get_X() - x_in_search)+abs(new_cell.get_Y() - y_in_search));
            reach_data.push_back(new_cell);
        }
    }


    std::vector<r_search> reachable;



    add_siblings(tmp_rob_x, tmp_rob_y, 0, reach_data, reachable);



    std::vector<r_search> explored;

    for(int i = 0; i < reach_data.size(); i++){
        if(reach_data[i].get_value() == ROBOT_SAPPER){
            r_search new_cell;
            new_cell.set_X(reach_data[i].get_X());
            new_cell.set_Y(reach_data[i].get_Y());
            new_cell.set_value(reach_data[i].get_value());
            explored.push_back(new_cell);
        }
    }





    int x_to_find;
    int y_to_find;
    int itr = 1;
    bool is_reached = false;
    while(!is_reached){
        r_search tmp;
        tmp.set_to_go_point(1000);
        tmp.set_to_from_point(1000);
        tmp.set_from_to_sum(2000);
        for(auto & i : reachable){
                if (i.get_from_to_sum() <= tmp.get_from_to_sum()) {
                    if (!is_added(i.get_X(), i.get_Y(), explored)) {
                        if (i.get_from_to_sum() == tmp.get_from_to_sum()) {
                            if (i.get_to_from_point() < tmp.get_to_from_point()) {
                                tmp = i;
                            }
                        }
                        if (i.get_from_to_sum() < tmp.get_from_to_sum()) {
                            tmp = i;
                        }
                    }
                }

        }


        explored.push_back(tmp);
        for (int i = 0; i < reachable.size(); i++){
            if(reachable[i].get_X() == tmp.get_X() && reachable[i].get_Y() == tmp.get_Y()){
                reachable.erase(reachable.begin() + i);
            }
        }
        add_siblings(tmp.get_X(), tmp.get_Y(), tmp.get_to_from_point(), reach_data, reachable);

        if((abs(tmp.get_X() - x_in_search) + abs(tmp.get_Y() - y_in_search)) == 1){
            is_reached = true;
        }

        itr++;

    }


    // обратный путь по explored-у
    r_search tmp;
    for(auto & i : explored){
        if((abs(i.get_X() - x_in_search)  + abs(i.get_Y()- y_in_search)) == 1){
            tmp = i;
        }
    }

    std::vector<auto_command> way_out;
    int iterator = 1;
    while(tmp.get_X() != tmp_rob_x || tmp.get_Y() != tmp_rob_y){
        take_step_back(iterator, tmp, way_out);
        for (int i = 0; i < explored.size(); i++){
            if(explored[i].get_X() == tmp.get_previous_x() && explored[i].get_Y() == tmp.get_previous_y()){
                tmp = explored[i];
            }
        }
        iterator++;

    }



    iterator--;
    for(int i = 0; i < way_out.size(); i++){
        if(way_out[i].get_idx() == iterator){
            move_sapper(way_out[i].get_value(), god_map);
        }
    }

    reach_data.clear();
    reachable.clear();
    explored.clear();
    way_out.clear();

}

void robot::make_sapp_move(int tmp_sap_x, int tmp_sap_y,int maximum_x, int maximum_y, std::vector<map_cell>& bomb_positions, cell_value** tmp_map, just_map& god_map){


    if(bomb_positions.size() > 0) {
        std::vector<auto_command> bomb_way;
        int tmp_bomb_sum = -1;
        map_cell tmp_bomb;
        for (int iterator = 0; iterator < bomb_positions.size(); iterator++) {
            if ((abs(bomb_positions[iterator].get_X() - (sapper_x + maximum_x)) +abs(bomb_positions[iterator].get_Y() - (sapper_y + maximum_y)) < tmp_bomb_sum ||tmp_bomb_sum == -1) && bomb_positions[iterator].get_value() == BOMB) {
                tmp_bomb_sum =abs(bomb_positions[iterator].get_X() - (sapper_x + maximum_x)) + abs(bomb_positions[iterator].get_Y() - (sapper_y + maximum_y));
                tmp_bomb = bomb_positions[iterator];
            }
        }

        if (abs(tmp_bomb.get_X() - (sapper_x + maximum_x)) + abs(tmp_bomb.get_Y() - (sapper_y + maximum_y)) > 1) {
            shortest_sapp(tmp_bomb.get_X(), tmp_bomb.get_Y(), maximum_x, maximum_y, tmp_map, god_map);
        } else {
            int x_move = tmp_bomb.get_X() - (sapper_x + maximum_x);
            int y_move = tmp_bomb.get_Y() - (sapper_y + maximum_y);
            if (x_move == 1 && y_move == 0) {
                move_sapper(DOWN, god_map);
            } else if (x_move == -1 && y_move == 0) {
                move_sapper(UP, god_map);
            } else if (x_move == 0 && y_move == 1) {
                move_sapper(RIGHT, god_map);
            } else if (x_move == 0 && y_move == -1) {
                move_sapper(LEFT, god_map);
            }

            for (int i = 0; i < bomb_positions.size(); i++) {
                if (bomb_positions[i].get_X() == tmp_bomb.get_X() && bomb_positions[i].get_Y() == tmp_bomb.get_Y()) {
                    bomb_positions.erase(bomb_positions.begin() + i);
                }
            }

        }

    }
    //std::cout << " NO SAPP MOVE" << '\n';
}




void robot::ask_command(just_map& god_map) {

    draw_robot_map(god_map);
    bool switcher = true;

    while(switcher) {
        std::string str;
        std::cin >> str;

        if (str == "set_mode") {
            std::cin >> str;
            if (str == "manual") {
                continue;
            } else if (str == "scan") {
                std::cin >> str;
                autobot(step_amount(str, str.length()), god_map);
            } else if (str == "auto") {
                apple_collector(god_map);
            }
        } else if (str == "move") {
            std::cin >> str;
            if (str == "up") {
                move(UP, god_map);
            } else if (str == "down") {
                move(DOWN, god_map);
            } else if (str == "right") {
                move(RIGHT, god_map);
            } else if (str == "left") {
                move(LEFT, god_map);
            }
            draw_robot_map(god_map);
        } else if (str == "scan") {
            scan(god_map);
            draw_robot_map(god_map);
        } else if (str == "grab") {
            grab(god_map);
            draw_robot_map(god_map);
        } else if (str == "sapper") {
            std::cin >> str;
            if (str == "on") {
                set_sapper(god_map);
            } else if (str == "off") {
                destroy_sapper(god_map);
            }else if (str == "up") {
                move_sapper(UP, god_map);
            } else if (str == "down") {
                move_sapper(DOWN, god_map);
            } else if (str == "right") {
                move_sapper(RIGHT, god_map);
            } else if (str == "left") {
                move_sapper(LEFT, god_map);
            }
            draw_robot_map(god_map);
        }else if (str == "end") {
            switcher = false;
        }
    }
}

