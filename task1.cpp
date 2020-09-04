#include <iostream>


int get_rnk_block(char rnk, int number){
    for(int i = 4-number; i > 0; i--){
        rnk = rnk >> 2;
    }
    return rnk & 0x03;
}


int main() {
    char rnk = 0x3B;
    int a;
    std:: cin >> a;
    get_rnk_block(rnk, a);
    std::cout << get_rnk_block(rnk, a);
    return 0;
}
