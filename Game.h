#ifndef GAME_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

struct Pieces
{
  int lMirror;
  int rMirror;
  int hSplitter;
  int vSplitter;
};

class Game
{
public:
  string controlMenu(int type);
  void handleGame();
  void generateBoard(string arr[7][7], int menuOption);
  string genChar(int x, int y, string arr[7][7]);
  void boardInit(string arr[7][7], int level);
  int handleInput();
  void handleMenuInput(int menuOption, string arr[7][7]);
  void handleMirrors(string arr[7][7]);
  void handleSplitters(string arr[7][7]);
  void handleGo(string arr[7][7]);
  void handleRestart(string arr[7][7]);
  Pieces pieces;
};

#endif