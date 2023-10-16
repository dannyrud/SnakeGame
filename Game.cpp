#include <iostream>
#include <list>
#include <ncurses.h>
#include <list>
#include "Snake.cpp"
#include "Fruit.cpp"
#include <time.h>
using namespace std;
enum Direction {
  UP = 2,
  DOWN = -2,
  RIGHT = 1,
  LEFT = -1,
};
class Game {
private:
int score;
bool gameEnd = false;
bool gamePause = false;
bool pause = false;
Direction dir;
int fruitX;
int fruitY;
int snakeHeadX;
int snakeHeadY;
Fruit currentFruit;
list<Snake> currentSnake;
int height = 30;
int width = 60;
int start_y = 10;
int start_x = 10;
WINDOW * win;

public:
Game() {};
void setup() {
  initscr();
  noecho();
  curs_set(0);
  win = newwin(height, width, start_y, start_x);
  score = 0;
  fruitX = 0;
  fruitY = 0;
  currentSnake.clear();
  snakeHeadX = 0;
  snakeHeadY = 0;
  box(win, 0, 0);
  mvwprintw(win, 0, 25, "SCORE:");
  mvwprintw(win, 0, 31, (to_string(score).c_str()));
  srand(time(NULL));
  currentSnake.push_front(Snake(3,3));
  currentSnake.push_front(Snake(3,4));
  currentSnake.push_front(Snake(3,5));
  currentSnake.push_front(Snake(4,5));
  snakeHeadX = currentSnake.front().getX();
  snakeHeadY = currentSnake.front().getY();
  // loop to add all snake pieces
  for(auto it = currentSnake.begin(); it != currentSnake.end(); ++it) {
    add(*it);
  }
  getEmptyCoordinates(fruitY,fruitX);
  currentFruit = Fruit(fruitY,fruitX);
  add(currentFruit);
  curs_set(0);
  wgetch(win);
}
void getEmptyCoordinates(int &y, int &x) {
  while(mvwinch(win, y = rand() % height, x = rand() % width) != ' ');
}

void input() {
  keypad(win,true);
  int ch = 0;
  halfdelay(1);
  ch = wgetch(win);
  /*for each if, move snake and see if it hits fruit or wall, then
   either will grow die or continue moving, this is just to see if keys work*/
  switch(ch) {
    case KEY_UP:
      if(dir != DOWN) {
        dir = UP;
      }
      break;
    case KEY_DOWN:
    if(dir != UP) {
        dir = DOWN;
      }
      break;
    case KEY_LEFT:
      if(dir != RIGHT) {
        dir = LEFT;
      }
      break;
    case KEY_RIGHT:
      if(dir != LEFT) {
        dir = RIGHT;
      }
      break;

      case 'p':
      pause = true;
      break;

    default:
      break;
  }
}
void updateScreen() {
  if(pause == true) {
      gamePause = pause;
      pause = false;
    }
  switch(dir) {
    case LEFT:
    --snakeHeadX;
    //eat apple case
    if(snakeHeadX == currentFruit.getX() && snakeHeadY == currentFruit.getY()) {
      eatApple();
    }
    //border case
    else if(snakeHeadX > width - 2 || snakeHeadY > height - 2 || snakeHeadX < 1 || snakeHeadY < 1) {
        gameEnd = true;
      }   
    else {
      for(auto it = ++currentSnake.begin(); it != currentSnake.end(); ++it) {
      if(it->getX() == snakeHeadX && it->getY() == snakeHeadY) {
        gameEnd = true;
      }
     }
      moveSnake(snakeHeadX,snakeHeadY);
    }
    break;

    case RIGHT:
    ++snakeHeadX;
    //eat apple case
    if(snakeHeadX == currentFruit.getX() && snakeHeadY == currentFruit.getY()) {
      eatApple();
    }
    //border case
    else if(snakeHeadX > width - 2 || snakeHeadY > height - 2 || snakeHeadX < 1 || snakeHeadY < 1) {
        gameEnd = true;
      }
    else {
      for(auto it = ++currentSnake.begin(); it != currentSnake.end(); ++it) {
      if(it->getX() == snakeHeadX && it->getY() == snakeHeadY) {
        gameEnd = true;
      }
     }
      moveSnake(snakeHeadX,snakeHeadY);
    }
    break;

    case UP:
    --snakeHeadY;
    //eat apple case
    if(snakeHeadX == currentFruit.getX() && snakeHeadY == currentFruit.getY()) {
      eatApple();
    }
    //border case
     else if(snakeHeadX > width - 2 || snakeHeadY > height - 2 || snakeHeadX < 1 || snakeHeadY < 1) {
        gameEnd = true;
      }
    else {
      for(auto it = ++currentSnake.begin(); it != currentSnake.end(); ++it) {
      if(it->getX() == snakeHeadX && it->getY() == snakeHeadY) {
        gameEnd = true;
      }
     }
      moveSnake(snakeHeadX,snakeHeadY);
    }
    break;

    case DOWN:
    ++snakeHeadY;
    //eat apple case
    if(snakeHeadX == currentFruit.getX() && snakeHeadY == currentFruit.getY()) {
      eatApple();
    }
    else if(snakeHeadX > width - 2 || snakeHeadY > height - 2|| snakeHeadX < 1 || snakeHeadY < 1) {
        gameEnd = true;
      }
    else {
      for(auto it = ++currentSnake.begin(); it != currentSnake.end(); ++it) {
      if(it->getX() == snakeHeadX && it->getY() == snakeHeadY) {
        gameEnd = true;
      }
     }
      moveSnake(snakeHeadX,snakeHeadY);
    }
    break;

    default:
    break;
  }
  
}
void moveSnake(int x,int y) {
  currentSnake.pop_back();
  currentSnake.push_front(Snake(y,x));
  werase(win);
  box(win, 0, 0);
  mvwprintw(win, 0, 25, "SCORE:");
  mvwprintw(win, 0, 31, (to_string(score).c_str()));
  for(auto it = currentSnake.begin(); it != currentSnake.end(); ++it) {
    add(*it);
  }
  add(currentFruit);

}
void eatApple() {
  currentSnake.push_front(Snake(fruitY,fruitX));
  getEmptyCoordinates(fruitY,fruitX);
  currentFruit = Fruit(fruitY,fruitX);
  werase(win);
  box(win, 0, 0);
  ++score;
  mvwprintw(win, 0, 25, "SCORE:");
  mvwprintw(win, 0, 31, (to_string(score).c_str()));
  for(auto it = currentSnake.begin(); it != currentSnake.end(); ++it) {
    add(*it);
  }
  add(currentFruit);
}
void endGame(bool &gameOver) {
  gameOver = gameEnd;
  return;
}
void pauseGame(bool &pauseGameVar) {
  pauseGameVar = gamePause;
  return;
}

void playAgainOrQuit(bool &gameOver) {
  werase(win);
  box(win, 0, 0);
  mvwprintw(win, height/2, width/2 - 9, "GAME OVER");
  mvwprintw(win, height/2 - 2, width/2 - 9, "SCORE:");
  mvwprintw(win, height/2 - 2, width/2 - 1, (to_string(score).c_str()));
  mvwprintw(win, height/2 - 4, width/2 - 9, "Press p to play again");
  mvwprintw(win, height/2 - 5, width/2 - 9, "Press q to quit");
  
  while(1){
  int ch = 0;
  ch = wgetch(win); 

  switch(ch) {
    case 'p':
      gameEnd = false;
      gameOver = gameEnd;
      break;
    case 'q':
      break;
  }
   if (ch == 'p' || ch == 'q') {
        break;
    }
}
} 
void pauseScreen(bool &pauseGameVar) {
  werase(win);
  box(win, 0, 0);
  mvwprintw(win, height/2, width/2 - 9, "PAUSED");
  mvwprintw(win, height/2 - 2, width/2 - 9, "SCORE:");
  mvwprintw(win, height/2 - 2, width/2 - 1, (to_string(score).c_str()));
  mvwprintw(win, height/2 - 4, width/2 - 9, "Press p to resume game");
  mvwprintw(win, height/2 - 5, width/2 - 9, "Press q to quit");
  
  while(1){
  int ch = 0;
  ch = wgetch(win); 

  switch(ch) {
    case 'p':
      gamePause = false;
      pauseGameVar = gamePause;
      break;

    case 'q':
      break;
  }
   if (ch == 'p' || ch == 'q') {
        break;
    }
}
}

void add(Drawing drawing) {
  mvwaddch(win,drawing.getY(),drawing.getX(),drawing.getSymbol());
}

};
