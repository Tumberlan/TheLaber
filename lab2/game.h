//
// Created by Igor on 20.11.2020.
//
#ifndef LAB2_GAME_H
#define LAB2_GAME_H
#include <iostream>
#include <fstream>
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 10

class field{
private:
    int step_numb = 0;
    bool** wrld;
    bool** pre_wrld;
    int alive_neigh_numb(int height, int width)const;
    int pre_alive_neigh_numb(int height, int width)const;
    void update_state(int a, int b);
public:
    field();
    ~field();
    void draw(int a, int b)const;
    int nei_num(int a, int b)const;
    friend std::ostream& operator<<(std::ostream& os, const field& game);
    void set(int height, int width);
    void clear(int height, int width);
    void one_step();
    void back_step();
    void show_states(int height, int width);
    void reset();
    void save(const std::string& path) const;
    void load(const std::string& path);
};


class game_life{
private:
    field game;
public:
    int check_step(std::string str, int a);
    void f_command();
};


#endif //LAB2_GAME_H
