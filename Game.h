#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include "Player.h"

using namespace std;

struct Pieces // struct for each token piece
{
  int lMirror;
  int rMirror;
  int hSplitter;
  int vSplitter;
};

enum class Direction // enum class for direction
{
  Up = 0,
  Down = 1,
  Left,
  Right
};

class Game
{
private:
  int level;         // current player lives
  int lives;         // current player level
  bool levelSuccess; // true if level is success
  Pieces pieces;     // pieces object

public:
  Player handleGame(Player player);
  /*
    function that handles all game functions
    @param player player object
    @return updated player object
  */

  void boardInit(string arr[7][7], int level);
  /*
    function that initializes board with level parameters
    @param arr 2d array with game board
    @param level int of what level player is on
  */

  void generateBoard(string arr[7][7], int menuOption);
  /*
    handles displaying board onto game.txt
    @param arr 2d array with game board
    @param menuOption input of what menu to display
  */

  int getLevel() { return level; }
  /*
    returns player level
    @return level player level
  */
  int getLives() { return lives; }
  /*
    returns player lives
    @return lives player lives
  */
  void setLevel(int m_level) { level = m_level; }
  /*
    sets player level
    @param m_level player level input
  */
  void setLives(int m_lives) { lives = m_lives; }
  /*
    sets player lives
    @param m_lives player lives input
  */

  string controlMenu(int type);
  /*
    function that handles menu display
    @param type type of level to return
    @return returns string of desired menu
  */
  void handleMenuInput(int menuOption, string arr[7][7]);
  /*
    handles the input of the menu
    @param menuOption which menu to display
    @param arr 2d array of board
  */

  void handleGo(string arr[7][7]);
  /*
    function that handles the "go" control option
    @param arr 2d array of board
  */
  void handleRestart(string arr[7][7]);
  /*
    function that handles the "restart" control option
    @param arr 2d array of board
  */
  void handleMove(int xStart, int yStart, Direction dir, string arr[7][7]);
  /*
    function that handles the movement of the laser
    @param xStart the starting x position of movement
    @param yStart the starting y position of movement
    @param dir direction of movement
    @param arr 2d array of board
  */

  string genChar(int x, int y, string arr[7][7]);
  /*
    function that handles which character to display
    @param x x position of return
    @param y y position of return
    @param arr 2d array of board
    @return character to display based off x and y
  */
  bool checkWin(string arr[7][7]);
  /*
    function that checks whether the level was completed successfully
    @param arr 2d array of board
    @return bool of whether the board was compeleted successfully or not
  */
  bool hitTarget(string arr[7][7], int tX, int tY);
  /*
    function within checkWin that checks if a target was hit
    @param arr 2d array of board
    @param tX x position of target
    @param tY y position of target
    @return bool if target was hit
  */
  int handleInput();
  /*
    helper function that takes in an input and returns the input value
    @return int of input
  */
};

#endif