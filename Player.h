#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

class Player
{
private:
  string username; // player username
  string password; // player password
  int lives;       // player lives
  int level;       // player level

public:
  // default constructor
  Player()
  {
    username = "player";
    password = "123456";
    lives = 3;
    level = 1;
  }
  // overload constructor
  Player(string playerData);

  string getUsername() const { return username; }
  /*
    returns player username
    @return player username
  */
  string getPassword() const { return password; }
  /*
   returns player password
   @return player password
  */
  int getLives() const { return lives; }
  /*
    returns player lives
    @return player lives
   */
  int getLevel() const { return level; }
  /*
    returns player level
    @return player level
   */
  void setUsername(string m_username) { username = m_username; }
  /*
    sets username
    @param m_username new username
  */
  void setPassword(string m_password) { password = m_password; }
  /*
    sets password
    @param m_password new password
  */
  void setLives(int m_lives) { lives = m_lives; }
  /*
     sets lives
     @param m_lives new lives
   */
  void setLevel(int m_level) { level = m_level; }
  /*
    sets lives
    @param m_lives new lives
  */
  void displayPlayerData();
  /*
    displays player data in username, password, lives, level format
  */
  void savePlayerData();
  /*
    saves player data to database txt file
  */
};

#endif