#include "Game.h"

Player Game::handleGame(Player player) // handles the entire game
{
  // setup player things
  levelSuccess = false; // check if level success
  lives = player.getLives();
  level = player.getLevel();
  string board[7][7];       // set up board array
  boardInit(board, level);  // initialize the board to the level
  generateBoard(board, -1); // display board with default menu option default
  int menuInput = -1;       // sets first menu input to default
  while (!levelSuccess)
  {
    menuInput = handleInput(); // input to change the menu
    handleMenuInput(menuInput, board);
    generateBoard(board, -1); // display
    player.setLives(lives);   // update lives
    if (lives == 0)
    {
      generateBoard(board, 2); // display gameover menu
      return player;
    }
    if (menuInput == 7) // display winner
    {
      return player;
    }
  }
  if (player.getLevel() < 6) // while the level is within 1-6
  {
    generateBoard(board, 1); // display win menu
    menuInput = handleInput();
    // update level
    int lvl = player.getLevel();
    lvl++;
    player.setLevel(lvl);
    // menu after level completed
    while (menuInput == 1 || menuInput == 2)
    {
      switch (menuInput)
      {
      case 1:
        handleGame(player);
        return player;
        break;
      case 2:
        break;
      default:
        cout << "INVALID INPUT" << endl;
        break;
      }
    }
  }
  else
  {
    // winner handler
    generateBoard(board, 99);
    menuInput = handleInput();
    player.setLevel(100);
  }
  return player;
}

void Game::handleMenuInput(int menuOption, string arr[7][7])
{
  switch (menuOption)
  {
  case 1:
    if (pieces.lMirror == 0)
    {
      cout << "NO MORE PIECES" << endl;
      return;
    }
    break;
  case 2:
    if (pieces.rMirror == 0)
    {
      cout << "NO MORE PIECES" << endl;
      return;
    }
    break;
  case 3:
    if (pieces.hSplitter == 0)
    {
      cout << "NO MORE PIECES" << endl;
      return;
    }
    break;
  case 4:
    if (pieces.vSplitter == 0)
    {
      cout << "NO MORE PIECES" << endl;
      return;
    }
    break;
  default:
    break;
  }
  int col, row;
  if (menuOption < 5)
  {
    generateBoard(arr, 101);
    row = handleInput() - 1;
    generateBoard(arr, 102);
    col = handleInput() - 1;
    if (arr[col][row] != ".")
    {
      cout << "PIECE BLOCKED" << endl; // FIX ME: maybe change to display errors on board?
      return;
    }
  }
  switch (menuOption)
  {
  case 1:
    arr[col][row] = "\\";
    pieces.lMirror--;
    break;
  case 2:
    arr[col][row] = "/";
    pieces.rMirror--;
    break;
  case 3:
    arr[col][row] = "_";
    pieces.hSplitter--;
    break;
  case 4:
    arr[col][row] = "|";
    pieces.vSplitter--;
    break;
  case 5:
    handleGo(arr);
    break;
  case 6:
    handleRestart(arr);
    break;
  case 7:
    break;
  default:
    cout << "INVALID INPUT" << endl;
    return;
    break;
  }
}

void Game::handleGo(string arr[7][7])
{
  int beamX, beamY;
  for (int y = 0; y < 7; y++)
  {
    for (int x = 0; x < 7; x++)
    {
      if (arr[y][x] == "b")
      {
        beamX = x;
        beamY = y;
      }
    }
  }
  handleMove(beamX, beamY, Direction::Up, arr);    // upward laser
  handleMove(beamX, beamY, Direction::Down, arr);  // downward laser
  handleMove(beamX, beamY, Direction::Left, arr);  // left laser
  handleMove(beamX, beamY, Direction::Right, arr); // right laser
  if (checkWin(arr))                               // update whether level is completed
  {
    levelSuccess = true;
  }
  generateBoard(arr, -1);
}

bool Game::checkWin(string arr[7][7])
{
  // loop through board array and find target position
  for (int y = 0; y < 7; y++)
  {
    for (int x = 0; x < 7; x++)
    {
      if (arr[y][x] == "o")
      {
        int tX = x;
        int tY = y;
        if (!hitTarget(arr, tX, tY))
        {
          lives--;
          return false;
        }
      }
    }
  }
  return true;
}

bool Game::hitTarget(string arr[7][7], int tX, int tY)
{
  if (tY > 0 && arr[tY - 1][tX] == "V")
  {
    return true;
  }
  else if (tY < 7 && arr[tY + 1][tX] == "^")
  {
    return true;
  }
  else if (tX > 0 && arr[tY][tX - 1] == ">")
  {
    return true;
  }
  else if (tX < 7 && arr[tY][tX + 1] == "<")
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Game::handleMove(int xStart, int yStart, Direction dir, string arr[7][7])
{
  int nextX = xStart;
  int nextY = yStart;
  Direction direction = dir;
  while (1)
  {
    switch (direction)
    {
    case Direction::Up:
      --nextY;
      break;
    case Direction::Down:
      ++nextY;
      break;
    case Direction::Left:
      --nextX;
      break;
    case Direction::Right:
      ++nextX;
      break;
    }
    string nextTile = arr[nextY][nextX];
    if (nextTile == "#" || nextTile == "o" || nextX < 0 || nextX > 6 || nextY < 0 || nextY > 6) // hit wall
    {
      break;
    }
    else if (nextTile == "/")
    {
      direction = (direction == Direction::Up)     ? Direction::Right
                  : (direction == Direction::Down) ? Direction::Left
                  : (direction == Direction::Left) ? Direction::Down
                                                   : Direction::Up;
    }
    else if (nextTile == "\\")
    {
      direction = (direction == Direction::Up)     ? Direction::Left
                  : (direction == Direction::Down) ? Direction::Right
                  : (direction == Direction::Left) ? Direction::Up
                                                   : Direction::Down;
    }
    else if (nextTile == "_")
    {
      if (direction == Direction::Up || direction == Direction::Down)
      {
        handleMove(nextX, nextY, Direction::Left, arr);
        handleMove(nextX, nextY, Direction::Right, arr);
      }
      break;
    }
    else if (nextTile == "|")
    {
      if (direction == Direction::Left || direction == Direction::Right)
      {
        handleMove(nextX, nextY, Direction::Up, arr);
        handleMove(nextX, nextY, Direction::Down, arr);
      }
      break;
    }
    else
    {
      arr[nextY][nextX] = (direction == Direction::Up)     ? "^"
                          : (direction == Direction::Down) ? "V"
                          : (direction == Direction::Left) ? "<"
                                                           : ">";
    }
  }
}

void Game::handleRestart(string arr[7][7])
{
  boardInit(arr, level);
  generateBoard(arr, -1);
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
  string lvlFile = "levels/level" + to_string(level) + ".txt"; // convert level into file format
  lvlTemplate.open(lvlFile);                                   // open file

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
  xPos = stoi(input.substr(0, 1)) - 1;
  yPos = stoi(input.substr(2, 1)) - 1;
  arr[yPos][xPos] = "b";

  // set target pos
  getline(lvlTemplate, input);
  iter = stoi(input);
  for (int i = 0; i < iter; i++)
  {
    getline(lvlTemplate, input);
    xPos = stoi(input.substr(0, 1)) - 1;
    yPos = stoi(input.substr(2, 1)) - 1;
    arr[yPos][xPos] = "o";
  }

  // set blocker pos
  getline(lvlTemplate, input);
  iter = stoi(input);
  for (int i = 0; i < iter; i++)
  {
    getline(lvlTemplate, input);
    xPos = stoi(input.substr(0, 1)) - 1;
    yPos = stoi(input.substr(2, 1)) - 1;
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
  gameBoard << "LEVEL: " << level << endl;
  for (int y = 0; y < 10; y++)
  {
    for (int x = 0; x < 20; x += 2)
    {
      gameBoard << genChar(x / 2, y, arr);
      gameBoard << " ";
    }
    gameBoard << endl;
  }
  gameBoard << "\n\nLives: ";
  for (int i = 0; i < lives - 1; i++)
  {
    gameBoard << "O ";
  }
  gameBoard << "\n\n"
            << controlMenu(menuOption);
  gameBoard.close();
}

string Game::controlMenu(int type)
{
  switch (type)
  {
  case 101:
    return ("Controls:\nEnter a row (1-6)");
    break;
  case 102:
    return ("Controls:\nEnter a column (1-6)");
    break;
  case 1:
    return ("YOU WIN:\n1. Next Level\n2. Exit\n");
    break;
  case 2:
    return ("OUT OF LIVES\nGAME OVER");
    break;
  case 99:
    return ("WINNER WINNER CHICKEN DINNER\nEnter any key to exit");
    break;
  default:
    return ("Controls:\n1. (\\): " + to_string(pieces.lMirror) + "\n2. (/): " + to_string(pieces.rMirror) + "\n3. (_): " + to_string(pieces.hSplitter) + "\n4. (|): " + to_string(pieces.vSplitter) + "\n5. Go\n6. Restart\n7. Exit\n");
    break;
  }
}

string Game::genChar(int x, int y, string arr[7][7])
{
  // coor display
  if (y == 0)
  {
    return ((x > 1 && x < 9) ? to_string(x - 1) : " ");
  }
  else if (x == 0)
  {
    return ((y > 1 && y < 9) ? to_string(y - 1) : " ");
  }
  // walls
  else if (y == 1 || y == 9)
  {
    return "#";
  }
  else if (x == 1 || x == 9)
  {
    return "#";
  }
  // game
  else
  {
    return arr[y - 2][x - 2];
  }
}