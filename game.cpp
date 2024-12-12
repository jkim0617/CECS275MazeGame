#include "Game.h"

void Game::handleGame()
{
  int level = 1;            // temporary level set
  string board[7][7];       // set up board array
  boardInit(board, 1);      // initialize the board to the level
  generateBoard(board, -1); // display board with default menu option default
  while (1)
  {
    int menuInput = handleInput();   // input to change the menu
    generateBoard(board, menuInput); // change the menu to proper menu option
    handleMenuInput(menuInput, board);
    /*
      menuinput = 1;
      menu: left mirror or right mirror, prompt user to choose 1 or 2
      insert function here to handle different cases
    */
    /*
      Order of game:
      get level and player lives (FIX ME:implement after the rest of logic is finished)
      initialize game
        initialize array (DONE)
        fill array with boardinit function(DONE)
        display board and first menu with generate board function (DONE)
      loop while game is on
        take a menu input (DONE)
        regen board with updated menu input, prompt for change
        once change set, regen board with changes
        set menu option back to 1
    */
    generateBoard(board, -1);
  }
}

void Game::handleMenuInput(int menuOption, string arr[7][7])
{
  switch (menuOption)
  {
  case 1:
    handleMirrors(arr);
    break;
  case 2:
    // handle splitters
    break;
  case 3:
    // handle go
    break;
  case 4:
    // handle restart
    break;
  default:
    // handle improper input
    break;
  }
}

void Game::handleMirrors(string arr[7][7])
{
  int input;
  input = handleInput();
  generateBoard(arr, 101);
  int row = handleInput();
  generateBoard(arr, 102);
  int col = handleInput();
  switch (input)
  {
  case 1:
    arr[col][row] = "\\";
    break;
  case 2:
    arr[col][row] = "/";
    break;
  }
}

int Game::handleInput()
{
  cout << "Entry: ";
  int choice;
  cin >> choice;
  return choice;
}

void Game::boardInit(string arr[7][7], int level) // fills the array with config from txt file
{
  ifstream lvlTemplate; // initialize input file stream
  string input;
  int iter;
  int xPos;
  int yPos;
  string lvlFile = "level" + to_string(level) + ".txt"; // convert level into file format
  lvlTemplate.open(lvlFile);                            // open file

  // fill empty space
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      arr[i][j] = ".";
    }
  }

  // set laser pos
  getline(lvlTemplate, input);
  xPos = stoi(input.substr(0, 1));
  yPos = stoi(input.substr(2, 1));
  arr[yPos][xPos] = "b";

  // set target pos
  getline(lvlTemplate, input);
  iter = stoi(input);
  for (int i = 0; i < iter; i++)
  {
    getline(lvlTemplate, input);
    xPos = stoi(input.substr(0, 1));
    yPos = stoi(input.substr(2, 1));
    arr[yPos][xPos] = "o";
  }

  // set blocker pos
  getline(lvlTemplate, input);
  iter = stoi(input);
  for (int i = 0; i < iter; i++)
  {
    getline(lvlTemplate, input);
    xPos = stoi(input.substr(0, 1));
    yPos = stoi(input.substr(2, 1));
    arr[yPos][xPos] = "#";
  }

  // set # of tokens
  getline(lvlTemplate, input); // left mirror
  pieces.lMirror = stoi(input);
  getline(lvlTemplate, input); // right mirror
  pieces.rMirror = stoi(input);
  getline(lvlTemplate, input); // horiz splitter
  pieces.hSplitter = stoi(input);
  getline(lvlTemplate, input); // vert splitter
  pieces.vSplitter = stoi(input);

  lvlTemplate.close();
}

void Game::generateBoard(string arr[7][7], int menuOption) // displays to text file dependent on array
{
  ofstream gameBoard;

  gameBoard.open("game.txt");
  for (int y = 0; y < 9; y++)
  {
    for (int x = 1; x < 18; x += 2)
    {
      gameBoard << genChar(x / 2, y, arr);
      gameBoard << " ";
    }
    gameBoard << endl;
  }
  gameBoard << "\n\n"
            << controlMenu(menuOption);
  gameBoard.close();
}

string Game::controlMenu(int type)
{
  switch (type)
  {
  case 1:
    return ("Controls:\n1. Left Mirror (\\)\n2. Right Mirror (/)\n3. Exit");
    break;
  case 101:
    return ("Controls:\nEnter a row (1-6)");
    break;
  case 102:
    return ("Controls:\nEnter a column (1-6)");
    break;
  default:
    return ("Controls:\n1. (\\): " + to_string(pieces.lMirror) + "\n2. (/): " + to_string(pieces.rMirror) + "\n3. (_): " + to_string(pieces.hSplitter) + "\n4. (|): " + to_string(pieces.vSplitter) + "\n5. Go\n6. Reset\n");
    break;
  }
}

string Game::genChar(int x, int y, string arr[7][7])
{
  // walls
  if (y == 0 || y == 8)
  {
    return "#";
  }
  else if (x == 0 || x == 8)
  {
    return "#";
  }
  // game
  else
  {
    return arr[y - 1][x - 1];
  }
}