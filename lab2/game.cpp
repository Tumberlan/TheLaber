//
// Created by Igor on 20.11.2020.
//
#include "game.h"

// РЕАЛИЗАЦИЯ ЯЧЕЙКИ

void point::draw() const {
    if(!this->state){
        std::cout << ". ";
    }else{
        std::cout << "* ";
    }
}

void point::set_state(bool a) {
    this->state = a;
}

void point::update_pre_state() {
    this->pre_state = this->state;
}

void point::update_neighbors(int amount) {
    this->alive_neigh_numb = amount;
}

bool point::check_pre_state() const {
    return this->pre_state;
}

bool point::check_state()const {
    return this->state;
}

void point::update_state() {

    if ((!this->pre_state) && this->alive_neigh_numb == 3){
        this->state = true;
    }else if(this->pre_state && ((this->alive_neigh_numb >= 2) && (this->alive_neigh_numb <= 3))){
        this->state = true;
    }else if(this->pre_state && ((this->alive_neigh_numb < 2) || (this->alive_neigh_numb > 3))){
        this->state = false;
    }else{
        this->state = false;
    }
}

void point::swap_state() {
    bool tmp = this->state;
    this->state = this->pre_state;
    this->pre_state = tmp;
}

void point::save(std::ofstream &file) const {
    file << this->state << ' ';
}
void point::load(std::ifstream &file) {
    file >> this->state;
}

// РЕАЛИЗАЦИЯ МИРА

void field::draw() {
    std::cout << "  ";
    for (int i = 0; i < FIELD_WIDTH; i++){
        char a = 'A'+i;
        std:: cout << a << " ";
    }
    std::cout << '\n';
    for(int i = 0; i < FIELD_HEIGHT; i++){
        std:: cout << 9-i << " ";
        for(int j = 0; j < FIELD_WIDTH; j++){
            this->wrld[i][j].draw();
        }
        std::cout << '\n';
    }
    std::cout << "Step " << this->step_numb;
}

void field::set(int height, int width) {
    this->wrld[9 - height][width].set_state(true);
}

void field::clear(int height, int width) {
    this->wrld[9 - height][width].set_state(false);
}

int field::check_neighbours(int height, int width) {
    int number_of_neighbours = 0;
    height = 9 - height;
    int h1 = height - 1;
    int h2 = height + 1;
    int w1 = width - 1;
    int w2 = width + 1;
    if(h1 < 0) {
        h1 = 9;
    }
    if(h2 > 9){
        h2 = 0;
    }
    if(w1 < 0){
        w1 = 9;
    }
    if(w2 > 9){
        w2 = 0;
    }

    bool arr1[3];
    bool arr2[3];
    bool arr3[3];

    arr1[0] = this->wrld[h1][w1].check_state();
    arr2[0] = this->wrld[height][w1].check_state();
    arr3[0] = this->wrld[h2][w1].check_state();
    arr1[1] = this->wrld[h1][width].check_state();
    arr2[1] = false;
    arr3[1] = this->wrld[h2][width].check_state();
    arr1[2] = this->wrld[h1][w2].check_state();
    arr2[2] = this->wrld[height][w2].check_state();
    arr3[2] = this->wrld[h2][w2].check_state();

    for (int i = 0; i < 3; i++){
        if (arr1[i]){
            number_of_neighbours++;
        }
        if (arr2[i]){
            number_of_neighbours++;
        }
        if (arr3[i]){
            number_of_neighbours++;
        }
    }
    return number_of_neighbours;
}

void field::show_states(int height, int width) {
    height = 9 - height;
    std::cout << "pre-state: " << this->wrld[height][width].check_pre_state() << " state: " << this->wrld[height][width].check_state();
}

void field::one_step() {
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            this->wrld[9-i][j].update_neighbors(this->check_neighbours(i, j));
        }
    }



    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            this->wrld[i][j].update_pre_state();
            this->wrld[i][j].update_state();
        }
    }
    this->step_numb++;
}

void field::back_step() {
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for (int j = 0; j < FIELD_WIDTH; j++){
            this->wrld[i][j].swap_state();
        }
    }
}

void field::reset() {
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            this->clear(i,j);
        }
    }
    this->step_numb = 0;
}

void field::save(const std::string &file_name) const {
    std::ofstream file(file_name + ".txt"); // берем название файла и делаем из него файл
    file.clear();
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            this->wrld[i][j].save(file);
        }
        file << '\n';
    }
    file << std::endl;
    file.close();
}

void field::load(const std::string &path) {
    std::ifstream file(path + ".txt"); // открываем файл для чтения
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            this->wrld[i][j].load(file);
        }
    }
    file.close();
    this->step_numb = 0;
}
