//
// Created by Igor on 20.11.2020.
//

#ifndef LAB2_GAME_H
#define LAB2_GAME_H
#include <iostream>
#include <fstream>
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 10
#define NEIGHBOR_NUMB 8

class point{
private:
    bool state = false;
    bool pre_state = false;
    int alive_neigh_numb = 0;
public:
    void update_neighbors(int amount);
    void update_pre_state();
    void update_state();
    void draw() const;
    void set_state(bool a);
    void swap_state();
    bool check_pre_state()const;
    bool check_state()const;
    void save(std::ofstream &file) const;
    void load(std::ifstream &file);

};


class field{
private:
    int step_numb = 0;
    point wrld[FIELD_HEIGHT][FIELD_WIDTH];
public:
    void draw();
    void set(int height, int width);
    void clear(int height, int width);
    int check_neighbours(int height, int width);
    void one_step();
    void back_step();
    void show_states(int height, int width);
    void reset();
    void save(const std::string& path) const;
    void load(const std::string& path);
};



#endif //LAB2_GAME_H
