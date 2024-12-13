#include "Menu.h"

string menu()
{
  int menuInput;
  string playerData;
  while (1)
  {
    displayMainMenu();
    cin >> menuInput;
    switch (menuInput)
    {
    case 1:
      playerData = handleContinue();
      if (playerData != "")
      {
        return playerData;
      }
      break;
    case 2:
      playerData = handleNewGame();
      if (playerData != "")
      {
        return playerData;
      }
      break;
    case 3:
      return "EXITCODE";
      break;
    default:
      cout << "Invalid Input" << endl;
      break;
    }
  }
  throw;
}

void displayMainMenu()
{
  ofstream gameBoard;
  gameBoard.open("game.txt");
  gameBoard << "*-------------------*" << endl;
  gameBoard << "*     Main Menu     *" << endl;
  gameBoard << "*  1. Continue      *" << endl;
  gameBoard << "*  2. New Game      *" << endl;
  gameBoard << "*  3. Exit          *" << endl;
  gameBoard << "*-------------------*" << endl;
  gameBoard.close();
  cout << "Entry: ";
}

string handleContinue()
{
  // setup variables
  ifstream dataList("playerList.txt"); // read file
  ofstream gameBoard("game.txt");      // display file
  string playerData;                   // write file
  string username;                     // username string
  string password;                     // password string
  bool usernameFound = false;          // returns true if username exists

  gameBoard << "*-------------------*" << endl;
  gameBoard << "*                   *" << endl;
  gameBoard << "*    Enter your     *" << endl;
  gameBoard << "*    username       *" << endl;
  gameBoard << "*                   *" << endl;
  gameBoard << "*-------------------*" << endl;
  gameBoard.close();
  cout << "Entry: ";
  cin >> username;
  while (dataList >> playerData)
  {
    string usernameData = playerData.substr(0, playerData.find(","));
    if (usernameData == username)
    {
      usernameFound = true;
      break;
    }
  }

  dataList.clear();
  dataList.seekg(0);
  dataList.close();
  if (!usernameFound)
  {
    cout << "USERNAME NOT FOUND" << endl;
    menu();
  }
  while (1)
  {
    ofstream gameBoard("game.txt"); // display file
    gameBoard << "*-------------------*" << endl;
    gameBoard << "*                   *" << endl;
    gameBoard << "*    Enter your     *" << endl;
    gameBoard << "*    password       *" << endl;
    gameBoard << "*                   *" << endl;
    gameBoard << "*-------------------*" << endl;
    gameBoard.close();
    cout << "Entry: ";
    cin >> password;
    int firstComma = playerData.find(',');
    int secondComma = playerData.find(',', firstComma + 1);
    string passwordData = playerData.substr(firstComma + 1, secondComma - firstComma - 1);
    if (passwordData == password)
    {
      cout << "Login Success" << endl;
      return playerData;
    }
    cout << "Incorrect Password" << endl;
  }
}

string handleNewGame()
{
  // variables
  ifstream dataList("playerList.txt");
  string username;
  string password;
  string playerData;
  bool validUsername = false;

  // loop that exits if username does not exist
  while (!validUsername)
  {
    validUsername = true;
    cout << "Enter a username: ";
    cin >> username;
    cout << "entered a username" << endl;
    while (dataList >> playerData) // parce through text file
    {
      string usernameData = playerData.substr(0, playerData.find(",")); // isolate player name
      if (usernameData == username)
      {
        cout << "username taken, try again" << endl;
        validUsername = false;
        break;
      }
    }
    // cout << "is valid username" << endl;
    // validUsername = true;
    dataList.clear();
    dataList.seekg(0);
  }
  cout << "Enter a password: ";
  cin >> password;
  dataList.clear();
  dataList.seekg(0);
  dataList.close();
  string dataSend = username + "," + password + "," + "3,1";
  return dataSend;
}