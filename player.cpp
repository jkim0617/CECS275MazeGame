#include "Player.h"

Player::Player(string playerData)
{
  username = playerData.substr(0, playerData.find(","));
  int firstComma = playerData.find(',');
  int secondComma = playerData.find(',', firstComma + 1);
  int commaIndex = secondComma - firstComma - 1;
  password = playerData.substr(firstComma + 1, commaIndex);
  lives = stoi(playerData.substr(secondComma + 1, 1));
  level = stoi(playerData.substr(secondComma + 3, 1));
}

void Player::displayPlayerData()
{
  cout << username << ", " << password << ", " << lives << ", " << level << endl;
}

void Player::savePlayerData()
{
  // create temp object
  Player temp(*this);

  // check if player user exists
  string playerUsername = this->username;      // this username
  ifstream playerListIn("playerList.txt");     // open text file to read
  ofstream playerListOut("playerListOut.txt"); // open temp text file to rewrite list
  string playerData;                           // create playerData string variable
  bool playerFound;                            // true if player was found in list
  while (playerListIn >> playerData)
  {
    string usernameData = playerData.substr(0, playerData.find(","));
    if (usernameData == playerUsername)
    {
      playerListOut << temp.username << "," << temp.password << "," << temp.lives << "," << temp.level << endl;
      playerFound = true;
    }
    else
    {
      playerListOut << playerData << endl;
    }
  }
  if (!playerFound)
  {
    cout << "New player" << endl;
    playerListOut << temp.username << "," << temp.password << "," << temp.lives << "," << temp.level << endl;
  }
  playerListOut.close();

  // delete "playerList.txt"
  remove("playerList.txt");
  // rename "playerListOut.txt to "playerList.txt"
  rename("playerListOut.txt", "playerList.txt");
}