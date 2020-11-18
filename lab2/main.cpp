#include <iostream>
#include <random>
#include <stdio.h>
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 10





class point{
public:
    unsigned char is_live;
    point& operator=(unsigned char a){
        this->is_live = a;
        return *this;
    }
};

class field{
private:
    point world[FIELD_WIDTH][FIELD_HEIGHT];


    enum width_coef{
        A, B, C, D, E, F, G, H, J
    };

    width_coef static f_char_to_wc(unsigned char a){
        int tmp = a - 'A';
        return (width_coef)tmp;
    }
public:

    void init_wrld(){



        int start_point_amount;
        std:: cin >> start_point_amount;

        for (int i = 0; i < FIELD_HEIGHT; i++){
            for (int j = 0; j < FIELD_WIDTH; j++)
        }

        for (int i = 0; i<start_point_amount; i++){
            unsigned char width;
            unsigned int y;
            std:: cin >> width >> y;
            width_coef x = f_char_to_wc(width);
            this->world[x][y] = '*';
        }



    }


};







int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
