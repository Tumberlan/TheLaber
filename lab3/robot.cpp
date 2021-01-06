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
                if(abs(Y) >= r_map_rad-1){
                    r_map_rad = r_map_rad*2;
                }
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
                if(abs(X) >= r_map_rad-1){
                    r_map_rad = r_map_rad*2;
                }
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
                if(abs(Y) >= r_map_rad-1){
                    r_map_rad = r_map_rad*2;
                }
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
                if(abs(X) >= r_map_rad-1){
                    r_map_rad = r_map_rad*2;
                }
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
  /*  int max_x = 0;
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
*/

    int max_x = 10 + god_map.robot_x;
    int min_x = -10 + god_map.robot_x;
    int max_y = 10 + god_map.robot_y;
    int min_y = -10 + god_map.robot_y;

    int max_temp_x = god_map.set_robot_x + r_map_rad;
    if(max_temp_x > 1000){
        max_temp_x = 1000;
    }
    int min_temp_x = god_map.set_robot_x - r_map_rad;
    if(min_temp_x < 0){
        min_temp_x = 0;
    }
    int max_temp_y = god_map.set_robot_y + r_map_rad;
    if(max_temp_y > 1000){
        max_temp_y = 1000;
    }
    int min_temp_y = god_map.set_robot_y - r_map_rad;
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
            if(map.is_discovered(i-god_map.set_robot_x, j-god_map.set_robot_y)){
                if(map.get_cell(i-god_map.set_robot_x, j-god_map.set_robot_y) != BORDER) {
                    if(god_map.set_robot_x+X == i && god_map.set_robot_y+Y == j){
                        std::cout << to_map_sign(ROBOT_COLLECTOR) << " ";
                    }else {
                        std::cout << to_map_sign(map.get_cell(i - god_map.set_robot_x, j - god_map.set_robot_y))
                                  << " ";
                    }
                }
            }else if(j > min_temp_y || j < max_temp_y){
                std:: cout << "? ";
            }
        }
        std::cout << '\n';
    }

/*

    for (int i = min_temp_x; i < max_temp_x; i++){
        if(i <= max_x && i >= min_x){
            if(min_y > 0){
                for (int j = min_temp_y; j < min_y; j++){
                    std::cout << "? ";
                }
            }
            for (int j = min_y; j <= max_y; j++){
                if(map.is_discovered(i-god_map.set_robot_x, j-god_map.set_robot_y)){
                    if(map.get_cell(i-god_map.set_robot_x, j-god_map.set_robot_y) != BORDER) {
                        if(god_map.set_robot_x+X == i && god_map.set_robot_y+Y == j){
                            std::cout << to_map_sign(ROBOT_COLLECTOR) << " ";
                        }else {
                            std::cout << to_map_sign(map.get_cell(i - god_map.set_robot_x, j - god_map.set_robot_y))
                                      << " ";
                        }
                    }
                }else if(j > min_temp_y || j < max_temp_y){
                    std:: cout << "? ";
                }
            }
            for (int j = max_y+1; j < max_temp_y; j++){
                std::cout << "? ";
            }
        }else if(i > 0 || i < god_map.X){
            for (int j = min_temp_y; j < max_temp_y; j++){
                std::cout << "? ";
            }
        }
        std::cout << '\n';
    }*/
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
        if((i.X == x+1 && i.Y == y) || ((i.X == x-1 && i.Y == y)) || ((i.X == x && i.Y == y+1)) || ((i.X == x && i.Y == y-1))){
            if(is_added(X,Y,to_r)){
                if(to_from+1 < i.to_from_point){
                    i.to_from_point = to_from+1;
                    i.from_to_sum = i.to_from_point + i.to_go_point;
                    i.previous_x = x;
                    i.previous_y = y;
                }
            }else{
                r_search new_cell;
                new_cell.X = i.X;
                new_cell.Y = i.Y;
                new_cell.previous_x = x;
                new_cell.previous_y = y;
                new_cell.value = i.value;
                new_cell.to_from_point = to_from+1;
                new_cell.to_go_point = i.to_go_point;
                new_cell.from_to_sum = new_cell.to_from_point + new_cell.to_go_point;
                to_r.push_back(new_cell);
            }
        }
    }
}

void take_step_back(int iterator, r_search tmp, std::vector<auto_command>& way_out){
    int x_move = tmp.X - tmp.previous_x;
    int y_move = tmp.Y - tmp.previous_y;
    auto_command temp_command;
    if(x_move == 1 && y_move == 0){
        temp_command.value = DOWN;
    }else if(x_move == -1 && y_move == 0){
        temp_command.value = UP;
    }else if(x_move == 0 && y_move == 1){
        temp_command.value = RIGHT;
    }else if(x_move == 0 && y_move == -1){
        temp_command.value = LEFT;
    }

    temp_command.idx = iterator;
    way_out.push_back(temp_command);
}




void robot::shortest_way(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map , just_map& god_map) {

    int tmp_rob_x = X + maximum_x;
    int tmp_rob_y = Y + maximum_y;

    std::vector<r_search> reach_data;



    for(auto & m : map.data){
        if(m.value == APPLE){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;
            new_cell.Y = m.Y+maximum_y;
            new_cell.value = APPLE;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
        if(m.value == EMPTY){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;;
            new_cell.Y = m.Y+maximum_y;;
            new_cell.value = EMPTY;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
        if(m.value == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;;
            new_cell.Y = m.Y+maximum_y;;
            new_cell.value = ROBOT_COLLECTOR;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
    }


    std::vector<r_search> reachable;



    add_siblings(tmp_rob_x, tmp_rob_y, 0, reach_data, reachable);



    std::vector<r_search> explored;

    for(int i = 0; i < reach_data.size(); i++){
        if(reach_data[i].value == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.X = reach_data[i].X;
            new_cell.Y = reach_data[i].Y;
            new_cell.value = reach_data[i].value;
            explored.push_back(new_cell);
        }
    }





    int x_to_find;
    int y_to_find;
    int itr = 1;
    bool is_reached = false;
    while(!is_reached){
        r_search tmp;
        tmp.to_go_point = 1000;
        tmp.to_from_point = 1000;
        tmp.from_to_sum = 2000;
        for(auto & i : reachable){
            if(i.from_to_sum <= tmp.from_to_sum){
                if(!is_added(i.X, i.Y, explored)) {
                    if (i.from_to_sum == tmp.from_to_sum) {
                        if (i.to_go_point < tmp.to_from_point) {
                            tmp = i;
                        }
                    }
                    if (i.from_to_sum < tmp.from_to_sum) {
                        tmp = i;
                    }
                }
            }
        }



        explored.push_back(tmp);
        for (int i = 0; i < reachable.size(); i++){
            if(reachable[i].X == tmp.X && reachable[i].Y == tmp.Y){
                reachable.erase(reachable.begin() + i);
            }
        }
        add_siblings(tmp.X, tmp.Y, tmp.to_from_point, reach_data, reachable);

        if((abs(tmp.X - x_in_search) + abs(tmp.Y - y_in_search)) == 1){
            is_reached = true;
        }

        itr++;

    }



    // обратный путь по explored-у
    r_search tmp;
    for(auto & i : explored){
        if((abs(i.X - x_in_search)  + abs(i.Y- y_in_search)) == 1){
            tmp = i;
        }
    }


    std::vector<auto_command> way_out;
    int iterator = 1;
    while(tmp.X != tmp_rob_x || tmp.Y != tmp_rob_y){
        take_step_back(iterator, tmp, way_out);
        for (int i = 0; i < explored.size(); i++){
            if(explored[i].X == tmp.previous_x && explored[i].Y == tmp.previous_y){
                tmp = explored[i];
            }
        }
        iterator++;

    }




    iterator--;
    for (; iterator > 0; iterator--) {
        for (int i = 0; i < way_out.size(); i++) {
            if (way_out[i].idx == iterator) {
                move(way_out[i].value, god_map);
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
            if (m.X > max_x){
                max_x = m.X;
            }
            if (m.Y > max_y){
                max_y = m.Y;
            }
            if (m.X < min_x){
                min_x = m.X;
            }
            if (m.Y < min_y){
                min_y = m.Y;
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
            if(i.value == ROBOT_COLLECTOR){
                tmp_rob_x = i.X + maximum_x;
                tmp_rob_y = i.Y + maximum_y;
            }
            tmp_map[i.X+maximum_x][i.Y+maximum_y] = i.value;
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
        if(m.value == APPLE){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;
            new_cell.Y = m.Y+maximum_y;
            new_cell.value = BOMB;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
        if(m.value == EMPTY){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;;
            new_cell.Y = m.Y+maximum_y;;
            new_cell.value = EMPTY;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
        if(m.value == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;;
            new_cell.Y = m.Y+maximum_y;;
            new_cell.value = ROBOT_COLLECTOR;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
    }


    std::vector<r_search> reachable;



    add_siblings(tmp_rob_x, tmp_rob_y, 0, reach_data, reachable);



    std::vector<r_search> explored;

    for(int i = 0; i < reach_data.size(); i++){
        if(reach_data[i].value == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.X = reach_data[i].X;
            new_cell.Y = reach_data[i].Y;
            new_cell.value = reach_data[i].value;
            explored.push_back(new_cell);
        }
    }





    int x_to_find;
    int y_to_find;
    int itr = 1;
    bool is_reached = false;
    while(!is_reached){
        r_search tmp;
        tmp.to_go_point = 1000;
        tmp.to_from_point = 1000;
        tmp.from_to_sum = 2000;
        for(auto & i : reachable){
            if(i.from_to_sum <= tmp.from_to_sum){
                if(!is_added(i.X, i.Y, explored)) {
                    if (i.from_to_sum == tmp.from_to_sum) {
                        if (i.to_go_point < tmp.to_from_point) {
                            tmp = i;
                        }
                    }
                    if (i.from_to_sum < tmp.from_to_sum) {
                        tmp = i;
                    }
                }
            }
        }


        explored.push_back(tmp);
        for (int i = 0; i < reachable.size(); i++){
            if(reachable[i].X == tmp.X && reachable[i].Y == tmp.Y){
                reachable.erase(reachable.begin() + i);
            }
        }
        add_siblings(tmp.X, tmp.Y, tmp.to_from_point, reach_data, reachable);

        if((abs(tmp.X - x_in_search) + abs(tmp.Y - y_in_search)) == 1){
            is_reached = true;
        }

        itr++;

    }


    // обратный путь по explored-у
    r_search tmp;
    for(auto & i : explored){
        if((abs(i.X - x_in_search)  + abs(i.Y- y_in_search)) == 1){
            tmp = i;
        }
    }

    std::vector<auto_command> way_out;
    int iterator = 1;
    while(tmp.X != tmp_rob_x || tmp.Y != tmp_rob_y){
        take_step_back(iterator, tmp, way_out);
        for (int i = 0; i < explored.size(); i++){
            if(explored[i].X == tmp.previous_x && explored[i].Y == tmp.previous_y){
                tmp = explored[i];
            }
        }
        iterator++;

    }



    iterator--;
    for(int i = 0; i < way_out.size(); i++){
        if(way_out[i].idx == iterator){
            move(way_out[i].value, god_map);
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
        if ((abs(apple_positions[iterator].X - (tmp_rob_x+maximum_x)) + abs(apple_positions[iterator].Y - (tmp_rob_y + maximum_y)) <
             tmp_sum ||
             tmp_sum == -1) && apple_positions[iterator].value == APPLE) {
            tmp_sum = abs(apple_positions[iterator].X - (tmp_rob_x+maximum_x)) + abs(apple_positions[iterator].Y - (tmp_rob_y + maximum_y));
            tmp = apple_positions[iterator];
        }
    }

    //std::cout << tmp.X << " " << tmp.Y << " rob " << (tmp_rob_x+maximum_x) << " " << (tmp_rob_y+maximum_y) << '\n';
    if(abs(tmp.X - (tmp_rob_x+maximum_x)) + abs(tmp.Y - (tmp_rob_y+maximum_y)) > 1){
        shortest_coll(tmp.X, tmp.Y, maximum_x, maximum_y, tmp_map, god_map);
    }else{
        int x_move = tmp.X - (X + maximum_x);
        int y_move = tmp.Y - (Y + maximum_y);
        if(x_move == 1 && y_move == 0){
            move(DOWN, god_map);
        }else if(x_move == -1 && y_move == 0){
            move(UP, god_map);
        }else if(x_move == 0 && y_move == 1){
            move(RIGHT, god_map);
        }else if(x_move == 0 && y_move == -1){
            move(LEFT, god_map);
        }

        grab(god_map);

        for (int i = 0; i < apple_positions.size(); i++) {
            if (apple_positions[i].X == tmp.X && apple_positions[i].Y == tmp.Y) {
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

        if (map.data[i].X > max_x){
            max_x = map.data[i].X;
        }
        if (map.data[i].Y > max_y){
            max_y = map.data[i].Y;
        }
        if (map.data[i].X < min_x){
            min_x = map.data[i].X;
        }
        if (map.data[i].Y < min_y){
            min_y = map.data[i].Y;
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
        if(i.value == ROBOT_COLLECTOR){
            tmp_rob_x = i.X + maximum_x;
            tmp_rob_y = i.Y + maximum_y;
        }
        if(i.value == ROBOT_SAPPER){
            tmp_sap_x = i.X + maximum_x;
            tmp_sap_y = i.Y + maximum_y;
        }
        tmp_map[i.X+maximum_x][i.Y+maximum_y] = i.value;
    }


    std::vector<map_cell> apple_positions;
    for(int i = 0 ; i < map.data.size(); i++){
        if(map.data[i].value == APPLE){
            map_cell new_cell;
            new_cell.value = APPLE;
            new_cell.X = map.data[i].X + maximum_x;
            new_cell.Y = map.data[i].Y + maximum_y;
            apple_positions.push_back(new_cell);
        }
    }

    std::vector<map_cell> bomb_positions;
    for(int i = 0 ; i < map.data.size(); i++){
        if(map.data[i].value == BOMB){
            map_cell new_cell;
            new_cell.value = BOMB;
            new_cell.X = map.data[i].X + maximum_x;
            new_cell.Y = map.data[i].Y + maximum_y;
            bomb_positions.push_back(new_cell);
        }
    }


        while (apple_positions.size() != 0) {

            make_collector_move(X, Y, maximum_x, maximum_y, apple_positions, tmp_map,god_map);
            if(sapp_on) {
                make_sapp_move(sapper_x, sapper_y, maximum_x, maximum_y, bomb_positions, tmp_map, god_map);
            }
            //std::cout << apple_positions.size() << '\n';

            draw_robot_map(god_map);
        }


}


// САПЁР

void robot::set_sapper(just_map &god_map) {
    int tmp_x;
    int tmp_y;
    int tmp_idx;
    for(int i = 0; i < map.data.size(); i++){
        int iter = rand()%50;
        if(map.data[i].value == EMPTY && iter>0){
            tmp_x = map.data[i].X;
            tmp_y = map.data[i].Y;
            tmp_idx = i;
            iter--;
        }
    }

    map.data[tmp_idx].value = ROBOT_SAPPER;
    god_map.sapper_x = tmp_x+god_map.set_robot_x;
    god_map.sapper_y = tmp_y+god_map.set_robot_y;
    god_map.map[god_map.sapper_x][god_map.sapper_y] = ROBOT_SAPPER;
    sapper_x = tmp_x;
    sapper_y = tmp_y;
    sapp_on = true;
}

void robot::destroy_sapper(just_map &god_map){
    int tmp_x;
    int tmp_y;
    for(int i = 0; i < map.data.size(); i++){

        if(map.data[i].value == ROBOT_SAPPER){
            tmp_x = map.data[i].X;
            tmp_y = map.data[i].Y;
            map.data[i].value = EMPTY;
            continue;
        }
    }

    god_map.sapper_x = -1;
    god_map.sapper_y = -1;
    god_map.map[tmp_x+god_map.set_robot_x][tmp_y+god_map.set_robot_y] = EMPTY;
    sapper_x = -1;
    sapper_y = -1;
    sapp_on = false;
}

void robot::move_sapper(move_command order, just_map &god_map) {
    cell_value tmp;
    cell_value border_check;
    if (order == RIGHT){
        for(auto & m : map.data){
            if(m.X == sapper_x && m.Y == sapper_y+1){
                border_check = m.value;
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.map[god_map.sapper_x][god_map.sapper_y + 1];
            if(tmp == ROBOT_COLLECTOR){
                move(RIGHT, god_map);
            }
            tmp = god_map.map[god_map.sapper_x][god_map.sapper_y + 1];
            if (tmp == EMPTY || tmp == BOMB || tmp == APPLE) {

                bool on_apple = false;
               // std::cout << god_map.sap_apple_x << " " << god_map.sap_apple_y << " sap " << god_map.sapper_x << " " << god_map.sapper_y << '\n';
                if(god_map.sap_apple_x == god_map.sapper_x && god_map.sap_apple_y == god_map.sapper_y && can_smash_apple){
                    god_map.map[god_map.sapper_x][god_map.sapper_y] = APPLE;
                    on_apple = true;
                    for(auto &m : map.data){
                        if(m.X == sapper_x && m.Y == sapper_y){
                            m.value = APPLE;
                        }
                    }
                    can_smash_apple = false;
                }

                if(tmp == APPLE){
                    god_map.sap_apple_x = god_map.sapper_x;
                    god_map.sap_apple_y = god_map.sapper_y + 1;
                    can_smash_apple = true;
                }


                if(!on_apple){
                    god_map.map[god_map.sapper_x][god_map.sapper_y] = EMPTY;
                    for (auto &m : map.data) {
                        if (m.X == sapper_x && m.Y == sapper_y) {
                            m.value = EMPTY;
                        }
                    }
                }
                for (auto &m : map.data) {
                    if (m.value == ROBOT_SAPPER) {
                    }
                }

                god_map.map[god_map.sapper_x][god_map.sapper_y + 1] = ROBOT_SAPPER;
                sapper_y += 1;

                for (auto &m : map.data) {
                    if (m.X == sapper_x && m.Y == sapper_y) {
                        m.value = ROBOT_SAPPER;
                    }
                }
                god_map.sapper_y += 1;
            }
        }
    }
    if (order == DOWN){
        for(auto & m : map.data){
            if(m.X == sapper_x+1 && m.Y == sapper_y){
                border_check = m.value;
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.map[god_map.sapper_x+1][god_map.sapper_y];
            if(tmp == ROBOT_COLLECTOR){
                move(DOWN, god_map);
            }
            tmp = god_map.map[god_map.sapper_x+1][god_map.sapper_y];
            if (tmp == EMPTY || tmp == BOMB || tmp == APPLE) {

                bool on_apple = false;
                //std::cout << god_map.sap_apple_x << " " << god_map.sap_apple_y << " sap " << god_map.sapper_x << " " << god_map.sapper_y << '\n';
                if(god_map.sap_apple_x == god_map.sapper_x && god_map.sap_apple_y == god_map.sapper_y && can_smash_apple){
                    god_map.map[god_map.sapper_x][god_map.sapper_y] = APPLE;
                    on_apple = true;
                    for(auto &m : map.data){
                        if(m.X == sapper_x && m.Y == sapper_y){
                            m.value = APPLE;
                        }
                    }
                    can_smash_apple = false;
                }

                if(tmp == APPLE){
                    god_map.sap_apple_x = god_map.sapper_x + 1;
                    god_map.sap_apple_y = god_map.sapper_y;
                    can_smash_apple = true;
                }


                if(!on_apple){
                    god_map.map[god_map.sapper_x][god_map.sapper_y] = EMPTY;
                    for (auto &m : map.data) {
                        if (m.X == sapper_x && m.Y == sapper_y) {
                            m.value = EMPTY;
                        }
                    }
                }
                god_map.map[god_map.sapper_x + 1][god_map.sapper_y] = ROBOT_SAPPER;
                sapper_x += 1;

                for (auto &m : map.data) {
                    if (m.X == sapper_x && m.Y == sapper_y) {
                        m.value = ROBOT_SAPPER;
                    }
                }
                god_map.sapper_x += 1;
            }
        }
    }
    if (order == LEFT){
        for(auto & m : map.data){
            if(m.X == sapper_x && m.Y == sapper_y-1){
                border_check = m.value;
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.map[god_map.sapper_x][god_map.sapper_y - 1];
            if(tmp == ROBOT_COLLECTOR){
                move(LEFT, god_map);
            }
            tmp = god_map.map[god_map.sapper_x][god_map.sapper_y - 1];

            if (tmp == EMPTY || tmp == BOMB || tmp == APPLE) {
                bool on_apple = false;
                //std::cout << god_map.sap_apple_x << " " << god_map.sap_apple_y << " sap " << god_map.sapper_x << " " << god_map.sapper_y << '\n';
                if(god_map.sap_apple_x == god_map.sapper_x && god_map.sap_apple_y == god_map.sapper_y && can_smash_apple){
                    god_map.map[god_map.sapper_x][god_map.sapper_y] = APPLE;
                    on_apple = true;
                    for(auto &m : map.data){
                        if(m.X == sapper_x && m.Y == sapper_y){
                            m.value = APPLE;
                        }
                    }
                    can_smash_apple = false;
                }

                if(tmp == APPLE){
                    god_map.sap_apple_x = god_map.sapper_x;
                    god_map.sap_apple_y = god_map.sapper_y -1;
                    can_smash_apple = true;
                }

                if(!on_apple){
                    god_map.map[god_map.sapper_x][god_map.sapper_y] = EMPTY;
                    for (auto &m : map.data) {
                        if (m.X == sapper_x && m.Y == sapper_y) {
                            m.value = EMPTY;
                        }
                    }
                }

                god_map.map[god_map.sapper_x][god_map.sapper_y - 1] = ROBOT_SAPPER;
                sapper_y -= 1;

                for (auto &m : map.data) {
                    if (m.X == sapper_x && m.Y == sapper_y) {
                        m.value = ROBOT_SAPPER;
                    }
                }
                god_map.sapper_y -= 1;
            }
        }
    }
    if (order == UP){
        for(auto & m : map.data){
            if(m.X == sapper_x-1 && m.Y == sapper_y){
                border_check = m.value;
            }
        }
        if(border_check != BORDER) {
            tmp = god_map.map[god_map.sapper_x-1][god_map.sapper_y];
            if(tmp == ROBOT_COLLECTOR){
                move(UP, god_map);
            }
            tmp = god_map.map[god_map.sapper_x-1][god_map.sapper_y];
            if (tmp == EMPTY || tmp == BOMB || tmp == APPLE) {

                bool on_apple = false;
                //std::cout << god_map.sap_apple_x << " " << god_map.sap_apple_y << " sap " << god_map.sapper_x << " " << god_map.sapper_y << '\n';
                if(god_map.sap_apple_x == god_map.sapper_x && god_map.sap_apple_y == god_map.sapper_y && can_smash_apple){
                    god_map.map[god_map.sapper_x][god_map.sapper_y] = APPLE;
                    on_apple = true;
                    for(auto &m : map.data){
                        if(m.X == sapper_x && m.Y == sapper_y){
                            m.value = APPLE;
                        }
                    }
                    can_smash_apple = false;
                }

                if(tmp == APPLE){
                    god_map.sap_apple_x = god_map.sapper_x - 1;
                    god_map.sap_apple_y = god_map.sapper_y;
                    can_smash_apple = true;
                }


                if(!on_apple){
                    god_map.map[god_map.sapper_x][god_map.sapper_y] = EMPTY;
                    for (auto &m : map.data) {
                        if (m.X == sapper_x && m.Y == sapper_y) {
                            m.value = EMPTY;
                        }
                    }
                }

                god_map.map[god_map.sapper_x - 1][god_map.sapper_y] = ROBOT_SAPPER;
                sapper_x -= 1;

                for (auto &m : map.data) {
                    if (m.X == sapper_x && m.Y == sapper_y) {
                        m.value = ROBOT_SAPPER;
                    }
                }
                god_map.sapper_x -= 1;
            }
        }
    }
}






void robot::shortest_sapp(int x_in_search, int y_in_search,int maximum_x, int maximum_y, cell_value** tmp_map, just_map& god_map){


    int tmp_rob_x = sapper_x + maximum_x;
    int tmp_rob_y = sapper_y + maximum_y;

    std::vector<r_search> reach_data;

    for(auto & m : map.data){
        if(m.value == BOMB){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;
            new_cell.Y = m.Y+maximum_y;
            new_cell.value = BOMB;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
        if(m.value == APPLE){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;
            new_cell.Y = m.Y+maximum_y;
            new_cell.value = APPLE;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
        if(m.value == EMPTY){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;;
            new_cell.Y = m.Y+maximum_y;;
            new_cell.value = EMPTY;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
        if(m.value == ROBOT_COLLECTOR){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;;
            new_cell.Y = m.Y+maximum_y;;
            new_cell.value = ROBOT_COLLECTOR;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
        if(m.value == ROBOT_SAPPER){
            r_search new_cell;
            new_cell.X = m.X+maximum_x;;
            new_cell.Y = m.Y+maximum_y;;
            new_cell.value = ROBOT_SAPPER;
            new_cell.to_go_point = abs(new_cell.X - x_in_search)+abs(new_cell.Y - y_in_search);
            reach_data.push_back(new_cell);
        }
    }


    std::vector<r_search> reachable;



    add_siblings(tmp_rob_x, tmp_rob_y, 0, reach_data, reachable);



    std::vector<r_search> explored;

    for(int i = 0; i < reach_data.size(); i++){
        if(reach_data[i].value == ROBOT_SAPPER){
            r_search new_cell;
            new_cell.X = reach_data[i].X;
            new_cell.Y = reach_data[i].Y;
            new_cell.value = reach_data[i].value;
            explored.push_back(new_cell);
        }
    }





    int x_to_find;
    int y_to_find;
    int itr = 1;
    bool is_reached = false;
    while(!is_reached){
        r_search tmp;
        tmp.to_go_point = 1000;
        tmp.to_from_point = 1000;
        tmp.from_to_sum = 2000;
        for(auto & i : reachable){
            if(i.from_to_sum <= tmp.from_to_sum){
                if(!is_added(i.X, i.Y, explored)) {
                    if (i.from_to_sum == tmp.from_to_sum) {
                        if (i.to_go_point < tmp.to_from_point) {
                            tmp = i;
                        }
                    }
                    if (i.from_to_sum < tmp.from_to_sum) {
                        tmp = i;
                    }
                }
            }
        }


        explored.push_back(tmp);
        for (int i = 0; i < reachable.size(); i++){
            if(reachable[i].X == tmp.X && reachable[i].Y == tmp.Y){
                reachable.erase(reachable.begin() + i);
            }
        }
        add_siblings(tmp.X, tmp.Y, tmp.to_from_point, reach_data, reachable);

        if((abs(tmp.X - x_in_search) + abs(tmp.Y - y_in_search)) == 1){
            is_reached = true;
        }

        itr++;

    }


    // обратный путь по explored-у
    r_search tmp;
    for(auto & i : explored){
        if((abs(i.X - x_in_search)  + abs(i.Y- y_in_search)) == 1){
            tmp = i;
        }
    }

    std::vector<auto_command> way_out;
    int iterator = 1;
    while(tmp.X != tmp_rob_x || tmp.Y != tmp_rob_y){
        take_step_back(iterator, tmp, way_out);
        for (int i = 0; i < explored.size(); i++){
            if(explored[i].X == tmp.previous_x && explored[i].Y == tmp.previous_y){
                tmp = explored[i];
            }
        }
        iterator++;

    }



    iterator--;
    for(int i = 0; i < way_out.size(); i++){
        if(way_out[i].idx == iterator){
            move_sapper(way_out[i].value, god_map);
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
            if ((abs(bomb_positions[iterator].X - (tmp_sap_x + maximum_x)) +
                 abs(bomb_positions[iterator].Y - (tmp_sap_y + maximum_y)) <
                 tmp_bomb_sum ||
                 tmp_bomb_sum == -1) && bomb_positions[iterator].value == BOMB) {
                tmp_bomb_sum =
                        abs(bomb_positions[iterator].X - (tmp_sap_x + maximum_x)) +
                        abs(bomb_positions[iterator].Y - (tmp_sap_y + maximum_y));
                tmp_bomb = bomb_positions[iterator];
            }
        }

        if (abs(tmp_bomb.X - (tmp_sap_x + maximum_x)) + abs(tmp_bomb.Y - (tmp_sap_y + maximum_y)) > 1) {
            shortest_sapp(tmp_bomb.X, tmp_bomb.Y, maximum_x, maximum_y, tmp_map, god_map);
        } else {
            int x_move = tmp_bomb.X - (sapper_x + maximum_x);
            int y_move = tmp_bomb.Y - (sapper_y + maximum_y);
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
                if (bomb_positions[i].X == tmp_bomb.X && bomb_positions[i].Y == tmp_bomb.Y) {
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

