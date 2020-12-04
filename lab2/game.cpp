//
// Created by Igor on 20.11.2020.
//
#include "game.h"

// РЕАЛИЗАЦИЯ МИРА

field::field() {
    this->wrld = new bool*[FIELD_WIDTH];
    this->pre_wrld = new bool*[FIELD_WIDTH];

    for(int i = 0; i < FIELD_HEIGHT; i++){
        this->wrld[i] = new bool[FIELD_HEIGHT];
        this->pre_wrld[i] = new bool[FIELD_HEIGHT];
    }

    for (int i = 0; i < FIELD_HEIGHT; i++){
        for (int j = 0; j < FIELD_WIDTH; j++){
            wrld[i][j] = false;
            pre_wrld[i][j] = false;
        }
    }
}

field::~field() {
    for (int i = 0; i < FIELD_HEIGHT; i++){
        delete[] this->wrld[i];
        delete[] this->pre_wrld[i];
    }
    delete[] this->wrld;
    delete[] this->pre_wrld;
}

void field::draw(int a,int b) const {
    if(!this->wrld[a][b]){
        std::cout << ". ";
    }else{
        std::cout << "* ";
    }
}


std::ostream& operator<<(std::ostream& os, const field& game){
    std::cout << "  ";
    for (int i = 0; i < FIELD_WIDTH; i++){
        char a = 'A'+i;
        std:: cout << a << " ";
    }
    std::cout << '\n';
    for(int i = 0; i < FIELD_HEIGHT; i++){
        std:: cout << 9-i << " ";
        for(int j = 0; j < FIELD_WIDTH; j++){
            game.draw(i,j);
        }
        std::cout << '\n';
    }


    std::cout << "Step " << game.step_numb;
    return os;
}

void field::set(int height, int width) {
    this->wrld[9 - height][width] = true;
}

void field::clear(int height, int width) {
    this->wrld[9 - height][width] = false;
}


int field::alive_neigh_numb(int height, int width) const {
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

    arr1[0] = this->wrld[h1][w1];
    arr2[0] = this->wrld[height][w1];
    arr3[0] = this->wrld[h2][w1];
    arr1[1] = this->wrld[h1][width];
    arr2[1] = false;
    arr3[1] = this->wrld[h2][width];
    arr1[2] = this->wrld[h1][w2];
    arr2[2] = this->wrld[height][w2];
    arr3[2] = this->wrld[h2][w2];

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

int field::nei_num(int a, int b) const {
    return this->alive_neigh_numb(a, b);
}

int field::pre_alive_neigh_numb(int height, int width) const {
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

    arr1[0] = this->pre_wrld[h1][w1];
    arr2[0] = this->pre_wrld[height][w1];
    arr3[0] = this->pre_wrld[h2][w1];
    arr1[1] = this->pre_wrld[h1][width];
    arr2[1] = false;
    arr3[1] = this->pre_wrld[h2][width];
    arr1[2] = this->pre_wrld[h1][w2];
    arr2[2] = this->pre_wrld[height][w2];
    arr3[2] = this->pre_wrld[h2][w2];

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

void field::update_state(int a, int b) {
    if ((!this->pre_wrld[9-a][b]) && this->pre_alive_neigh_numb(a,b) == 3){
        this->wrld[9-a][b] = true;
    }else if(this->pre_wrld[9-a][b] && ((this->pre_alive_neigh_numb(a,b) >= 2) && (this->pre_alive_neigh_numb(a, b) <= 3))){
        this->wrld[9-a][b] = true;
    }else if(this->pre_wrld[9-a][b] && ((this->pre_alive_neigh_numb(a,b) < 2) || (this->pre_alive_neigh_numb(a,b) > 3))){
        this->wrld[9-a][b] = false;
    }else{
        this->wrld[9-a][b] = false;
    }
}

void field::show_states(int height, int width) {
    height = 9 - height;
    std::cout << "pre-state: " << this->pre_wrld[height][width] << " state: " << this->wrld[height][width];
}



void field::one_step() {

    bool** tmp = this->pre_wrld;
    this->pre_wrld = this->wrld;
    this->wrld = tmp;

    for (int i = 0; i < FIELD_HEIGHT; i++){
        for (int j = 0; j < FIELD_WIDTH; j++){
            update_state(i,j);
        }
    }
    this->step_numb++;
}

void field::back_step() {
    bool** temp;
    temp = new bool*[FIELD_WIDTH];
    for(int i = 0; i < FIELD_WIDTH; i++){
        temp[i] = new bool[FIELD_HEIGHT];
    }

    temp = this->pre_wrld;
    this->pre_wrld = this->wrld;
    this->wrld = temp;
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
            file << this->wrld[i][j] << ' ';
        }
        file << '\n';
    }
    file << std::endl;
    file.close();
}

void field::load(const std::string &path) {
    std::ifstream file(path + ".txt"); // открываем файл для чтения
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++) {
            file >> this->wrld[i][j];
        }
    }
    file.close();
    this->step_numb = 0;
}

// РЕАЛИЗАЦИЯ ИГРЫ

int game_life::check_step(std::string str, int a)const{
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

void game_life::f_command() {

    bool switcher = true;
    while(switcher) {

        std::string input;
        std::cin >> input;


        if (input == "reset") {
            this->game.reset();
        }
        if (input == "set") {
            std::cin >> input;
            this->game.set((input[1] - '0'), (input[0] - 'A'));
        }
        if (input == "clear") {
            std::cin >> input;
            this->game.clear((input[1] - '0'), (input[0] - 'A'));
        }
        if (input == "step") {
            std::cin >> input;
            for (int i = 0; i < check_step(input, input.length()); i++) {
                this->game.one_step();
            }
        }
        if (input == "back") {
            this->game.back_step();
        }
        if (input == "save") {
            std::cin >> input;
            this->game.save(input);
        }
        if (input == "load") {
            std::cin >> input;
            this->game.load(input);
        }
        if (input == "end") {
            switcher = false;
        }
        std:: cout << this->game;
    }
}