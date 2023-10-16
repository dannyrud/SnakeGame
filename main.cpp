#include <iostream>
#include <list>
#include <ncurses.h>
#include "Game.cpp"
using namespace std;

int main() {
  start:
  bool gameOver = false;
  bool pauseGameVar = false;
  Game * game = new Game();
  game->setup();

//game loop
while(!gameOver) {
  game->input();
  game->updateScreen();
  game->endGame(gameOver);
  game->pauseGame(pauseGameVar);
  if(gameOver) {
    game->playAgainOrQuit(gameOver);
    if(!gameOver) {
      goto start;
    }
  }
  if(pauseGameVar) {
    game->pauseScreen(pauseGameVar);
    if(!pauseGameVar) {
      continue;
    } else {
      gameOver = true;
    }
  }
}
  endwin();
  delete game;
}



