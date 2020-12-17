#include <iostream>
#include <time.h>
#include "map.h"
#include "robot.h"
int main() {
    srand(time(nullptr));
    just_map map;

    map.set_robot();
    std::cout << map;

    robot r;
    r.draw_robot_map(map);

    r.scan(map);
    std::cout << map;
    r.draw_robot_map(map);
    r.move(UP, map);
    r.grab(map);
    std::cout << r.apple_counter << '\n';
    r.scan(map);
    std::cout << map;
    r.draw_robot_map(map);
    r.move(DOWN, map);
    r.grab(map);
    std::cout << map;
    r.draw_robot_map(map);

    std::cout << r.apple_counter;
    return 0;
}





