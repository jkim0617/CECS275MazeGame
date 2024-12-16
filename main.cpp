#include <iostream>
#include "Player.h"
#include "Menu.h"
#include "Game.h"

int main()
{
  Player player(menu());            // create player from menu input
  Game game;                        // create game object
  player = game.handleGame(player); // start game, update player when finished
  if (player.getLives() == 0)       // out of lives, dead player
  {
    player.setPassword("DEADPLAYER" + player.getUsername() + player.getPassword());
  }
  if (player.getLevel() == 100) // player wins
  {
    player.setPassword("WINNERWINNERCHICKENDINNER" + player.getUsername() + player.getPassword());
  }
  player.savePlayerData(); // save to database
  return 0;
}