#include <iostream>
#include <list>
#include <ncurses.h>
#pragma once
class Drawing {
protected:
int x;
int y;
char symbol;

public:
Drawing() {
    y = 0;
    x = 0;
    symbol = ' ';
}

Drawing(int y, int x, char symbol){
this->y = y;
this->x = x;
this->symbol = symbol;
}
int getY() {
    return y;
}
int getX() {
    return x;
}
char getSymbol() {
    return symbol;
}

};