#include <iostream>
#include "Player.h"
#include "Menu.h"
#include "Game.h"

int main()
{
  // Player player(menu());
  // player.displayPlayerData();
  // player.savePlayerData();
  Game game;
  game.handleGame();
  return 0;
}

/*
  I. menu creation (using classes)
    display the menu
    create a new player data if new user
    or
    retrieve player data from text file if returning user
  II. player data
    store and retrieve player data
  III. display game (easiest, file manipulation, using fstream)
    generate the 6 levels on text file
    display levels individually
      copy the game level onto new textfile
    setting up the input menu
    displaying objects depending on menu
    game control/menu
      1. place object
        a. select object
        b. select location
      2. test formation (will be for game logic person)
      3. reset
  IV. game logic (using fstream, based on marble drop)
    tbd
*/