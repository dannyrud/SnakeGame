#include <iostream>
#include <list>
#include <ncurses.h>
#include "Drawing.cpp"

using namespace std;
class Snake : public Drawing {
private:

public:
Snake() {
this->y = 0;
this->x = 0;
this->symbol = 'O';
}

Snake(int y, int x){
this->y = y;
this->x = x;
this->symbol = 'O';
}

};