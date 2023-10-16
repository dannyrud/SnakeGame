#include <iostream>
#include <list>
#include <ncurses.h>
#include "Drawing.cpp"
using namespace std;
class Fruit : public Drawing {
private:

public:
Fruit() {
this->y = 0;
this->x = 0;
this->symbol = 'F';
}
Fruit(int y, int x){
this->y = y;
this->x = x;
this->symbol = 'F';
}

};