#ifndef MENU_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

string menu();
/*
  Creats menu and returns player info based on input
  @return returns string of player data
*/
void displayMainMenu();
/*
  Displays Main menu and handles input
*/
string handleContinue();
/*
  Handles continue case inside displayMainMenu();
  @return string of player data
*/
string handleNewGame();
/*
  Handles new player case inside displayMainMenu();
  @return string of player data
*/
#endif