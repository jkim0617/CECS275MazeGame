#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include "Player.h"

using namespace std;

struct Pieces
{
  int lMirror;
  int rMirror;
  int hSplitter;
  int vSplitter;
};

enum class Direction
{
  Up = 0,
  Down = 1,
  Left,
  Right
};

class Game
{
private:
  int level;
  int lives;
  bool levelSuccess;
  Pieces pieces;

public:
  Player handleGame(Player player);

  void boardInit(string arr[7][7], int level);

  void generateBoard(string arr[7][7], int menuOption);

  int getLevel() { return level; }
  int getLives() { return lives; }
  void setLevel(int m_level) { level = m_level; }
  void setLives(int m_lives) { lives = m_lives; }

  string controlMenu(int type);
  void handleMenuInput(int menuOption, string arr[7][7]);

  void handleGo(string arr[7][7]);
  void handleRestart(string arr[7][7]);
  void handleMove(int xStart, int yStart, Direction dir, string arr[7][7]);

  string genChar(int x, int y, string arr[7][7]);
  bool checkWin(string arr[7][7]);
  bool hitTarget(string arr[7][7], int tX, int tY);
  int handleInput();
};

#endif