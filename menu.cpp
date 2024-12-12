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
        cout << "succes" << endl;
        return playerData;
      }
      break;
    case 2:
      playerData = handleNewGame();
      if (playerData != "")
      {
        cout << "succes" << endl;
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
  cout << "*-------------------*" << endl;
  cout << "*     Main Menu     *" << endl;
  cout << "*  1. Continue      *" << endl;
  cout << "*  2. New Game      *" << endl;
  cout << "*  3. Exit          *" << endl;
  cout << "*-------------------*" << endl;
}

string handleContinue()
{
  // setup variables
  ifstream dataList("playerList.txt"); // read file
  string playerData;                   // write file
  string username;                     // username string
  string password;                     // password string
  bool usernameFound = false;          // returns true if username exists

  cout << "Enter your username: ";
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
    cout << "Username not found" << endl;
    throw;
  }
  while (1)
  {
    cout << "Enter your password: ";
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