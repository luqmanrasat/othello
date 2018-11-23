#include "Game.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

void Game::banner()
{
    cout << endl << endl<< endl<< endl<< endl << endl << endl;
    cout << "                               Lets Play OTHELLO!" << endl;
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

void Game::help()
{
    cout << "   HOW TO PLAY" << endl << endl;

    cout << " - Game is for two players, 'X' and 'O'." << endl << endl;

    cout << " - Pieces may flank the opponent's pieces in more than 1 direction at the same" << endl << "   time. All flanked pieces are turned over in the same turn, becoming the"
         << endl << "   opponent's property." << endl << endl;

    cout << " - If on your turn you have no legal moves, your turn is forfeited and your" << endl << "   opponent moves again. However, if a move is available to you, you may not"
         << endl << "   forfeit your turn." << endl << endl;

    cout << " - When it is no longer possible for either player to move, the game is over." << endl << "   Pieces are counted and the player with the majority of his or her pieces on"
         << endl << "   the board is the winner." << endl << endl;

    cout << " - Each players have 3 super powers that can only be used once. If not used" << endl << "   and there is no more possible move left, game will proceed to end." << endl << endl;

    cout << "   SUPER POWERS" << endl << endl;

    cout << " ==> super1 (pass turn)" << endl << endl;

    cout << " ==> super2 (change one of the opponent pieces on the board to yours)" << endl << endl;

    cout << "   IN-GAME COMMANDS" << endl << endl;

    cout << " ==> menu (return to the game menu)" << endl << endl;

    cout << " ==> save (save game)" << endl << endl;
}

void Game::exit()
{
    system("cls");
    cout << "Thank you for playing :)" << endl;
}

void Game::boardPrint(char boardData[8][8], int score1, int score2, char curPlyr, char piece1, char piece2, bool curSuper1, bool curSuper2)
{
    int y_axis = 8;

    for(int i = 0; i <= 7; i++)																		// Function prints game board
    {

        for(int j = 0; j <= 16; j++)																// Loop prints "|---+---+---+---+---+---+---+---|" line
        {
            if(j == 0)
            {
                cout << "                         |";
            }

            else if(j == 16)
            {
                cout << "|";
            }

            else if(j % 2 != 0)
            {
                cout << "---";
            }
            else
            {
                cout << "+";
            }

        }
        cout << endl;


        int column = 0;

        for(int j = 0; j < 1; j++)																	// Loop prints the numbers on the left of the board
        {
            cout << "                       " << y_axis << " ";
            y_axis--;
        }


        for(int j = 0; j <= 16; j++)																// Loop prints the "|   |   |   |   |   |   |   |   |" line
        {
            if(j == 0)
            {
                cout << "|";
            }
            else if(j == 16)
            {
                cout << "|";
            }
            else if(j % 2 != 0)
            {
                char out = boardData[i][column];
                if(out == 's')
                    out = ' ';

                cout << " " << out << " ";										                    // This line prints the pieces on the board

            }
            else
            {
                cout << "|";
                column++;
            }
        }
        cout << endl;
    }

    cout << "                         |---+---+---+---+---+---+---+---|" << endl;					// prints the last "|---+---+---+---+---+---+---+---|" line of the board

    cout << "                           a   b   c   d   e   f   g   h" << endl << endl;				// prints the " a   b   c   d   e   f   g   h" line

    cout << "Score:          " << piece1 << " = " << score1 << "     " << piece2 << " = " << score2 << endl;						// prints the score for both players

    cout << "Current Player: " << curPlyr << endl;											// prints the current player

    cout << "                super1[" << curSuper1 << "]    super2[" << curSuper2 << "]" << endl << endl;

}

void Game::changeBoard(char x[8][8])
{
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            data[row][col] = x[row][col];
        }
    }
}

void Game::upTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row - 1][col];

    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        for(int test = row - 1; test >= 0; test--)
        {
            testPiece = data[test][col];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                for(int flip = test + 1; flip < row; flip++)
                {
                    data[flip][col] = curPiece;
                }
                break;
            }
        }
    }
}

void Game::downTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row + 1][col];

    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        for(int test = row + 1; test < 8; test++)
        {
            testPiece = data[test][col];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                for(int flip = test - 1; flip > row; flip--)
                {
                    data[flip][col] = curPiece;
                }
                break;
            }
        }
    }
}

void Game::rightTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row][col + 1];

    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        for(int test = col + 1; test < 8; test++)
        {
            testPiece = data[row][test];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                for(int flip = test - 1; flip > col; flip--)
                {
                    data[row][flip] = curPiece;
                }
                break;
            }
        }
    }
}

void Game::leftTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row][col - 1];

    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        for(int test = col - 1; test >= 0; test--)
        {
            testPiece = data[row][test];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                for(int flip = test + 1; flip < col; flip++)
                {
                    data[row][flip] = curPiece;
                }
                break;
            }
        }
    }
}

void Game::uprightTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row - 1][col + 1];
    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        int testRow = row - 1;
        int testCol = col + 1;
        while(testRow >= 0 && testCol < 8)
        {
            testPiece = data[testRow][testCol];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                int flipRow = testRow + 1;
                int flipCol = testCol - 1;
                while(flipRow < row && flipCol > col)
                {
                    data[flipRow][flipCol] = curPiece;
                    flipRow++;
                    flipCol--;
                }
                break;
            }
            testRow--;
            testCol++;
        }
    }

}

void Game::upleftTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row - 1][col - 1];
    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        int testRow = row - 1;
        int testCol = col - 1;
        while(testRow >= 0 && testCol >= 0)
        {
            testPiece = data[testRow][testCol];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                int flipRow = testRow + 1;
                int flipCol = testCol + 1;
                while(flipRow < row && flipCol < col)
                {
                    data[flipRow][flipCol] = curPiece;
                    flipRow++;
                    flipCol++;
                }
                break;
            }
            testRow--;
            testCol--;
        }
    }
}

void Game::downrightTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row + 1][col + 1];
    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        int testRow = row + 1;
        int testCol = col + 1;
        while(testRow < 8 && testCol < 8)
        {
            testPiece = data[testRow][testCol];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                int flipRow = testRow - 1;
                int flipCol = testCol - 1;
                while(flipRow > row && flipCol > col)
                {
                    data[flipRow][flipCol] = curPiece;
                    flipRow--;
                    flipCol--;
                }
                break;
            }
            testRow++;
            testCol++;
        }
    }
}

void Game::downleftTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row + 1][col - 1];
    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        int testRow = row + 1;
        int testCol = col - 1;
        while(testRow < 8 && testCol >= 0)
        {
            testPiece = data[testRow][testCol];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                int flipRow = testRow - 1;
                int flipCol = testCol + 1;
                while(flipRow > row && flipCol < col)
                {
                    data[flipRow][flipCol] = curPiece;
                    flipRow--;
                    flipCol++;
                }
                break;
            }
            testRow++;
            testCol--;
        }
    }
}

void Game::changeData(char x, int row, int col)
{
    data[row][col] = x;
}

void Game::changeSuper1(bool x)
{
    super1 = x;
}

void Game::changeSuper2(bool x)
{
    super2 = x;
}

char Game::mainMenu()
{

    char userInput;

    cout << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load a Game" << endl;
    cout << "3. Help" << endl;
    cout << "4. Quit" << endl << endl;
    cout << "Enter number: ";
    cin >> userInput;
    cin.ignore();

    return userInput;

}

int Game::changetoCoor(char x)
{
    int coordinate;

    if(x == 'a')
        coordinate = 0;
    else if(x == 'b')
        coordinate = 1;
    else if(x == 'c')
        coordinate = 2;
    else if(x == 'd')
        coordinate = 3;
    else if(x == 'e')
        coordinate = 4;
    else if(x == 'f')
        coordinate = 5;
    else if(x == 'g')
        coordinate = 6;
    else if(x == 'h')
        coordinate = 7;
    else if(x == '8')
        coordinate = 0;
    else if(x == '7')
        coordinate = 1;
    else if(x == '6')
        coordinate = 2;
    else if(x == '5')
        coordinate = 3;
    else if(x == '4')
        coordinate = 4;
    else if(x == '3')
        coordinate = 5;
    else if(x == '2')
        coordinate = 6;
    else if(x == '1')
        coordinate = 7;

    return coordinate;

}


bool Game::getInputTest()
{
    return inputTest;
}

bool Game::getPossibleMove()
{
    return possibleMove;
}

bool Game::getSuper1()
{
    return super1;
}

bool Game::getSuper2()
{
    return super2;
}

bool Game::upMove(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row - 1][col];

    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        for(int test = row - 1; test >= 0; test--)
        {
            testPiece = data[test][col];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                return true;
            }
        }
    }
    return false;
}
bool Game::downMove(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row + 1][col];

    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        for(int test = row + 1; test < 8; test++)
        {
            testPiece = data[test][col];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                return true;
            }
        }
    }
    return false;
}

bool Game::rightMove(char curPiece,int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row][col + 1];

    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        for(int test = col + 1; test < 8; test++)
        {
            testPiece = data[row][test];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                return true;
            }
        }
    }
    return false;
}

bool Game::leftMove(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row][col - 1];

    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        for(int test = col - 1; test >= 0; test--)
        {
            testPiece = data[row][test];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                return true;
            }
        }
    }
    return false;
}

bool Game::uprightMove(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row - 1][col + 1];
    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        int testRow = row - 1;
        int testCol = col + 1;
        while(testRow >= 0 && testCol < 8)
        {
            testPiece = data[testRow][testCol];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                return true;
            }
            testRow--;
            testCol++;
        }
    }
    return false;
}

bool Game::upleftMove(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row - 1][col - 1];
    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        int testRow = row - 1;
        int testCol = col - 1;
        while(testRow >= 0 && testCol >= 0)
        {
            testPiece = data[testRow][testCol];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                return true;
            }
            testRow--;
            testCol--;
        }
    }
    return false;
}

bool Game::downrightMove(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row + 1][col + 1];
    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        int testRow = row + 1;
        int testCol = col + 1;
        while(testRow < 8 && testCol < 8)
        {
            testPiece = data[testRow][testCol];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                return true;
            }
            testRow++;
            testCol++;
        }
    }
    return false;
}

bool Game::downleftMove(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    char nextPiece = data[row + 1][col - 1];
    if(testPiece == 's' && nextPiece != curPiece && nextPiece != 's')
    {
        int testRow = row + 1;
        int testCol = col - 1;
        while(testRow < 8 && testCol >= 0)
        {
            testPiece = data[testRow][testCol];
            if(testPiece == 's')
                break;

            else if(testPiece == curPiece)
            {
                return true;
            }
            testRow++;
            testCol--;
        }
    }
    return false;
}

bool Game::super2MoveTest(char curPiece, int row, int col)
{
    char testPiece = data[row][col];
    if(testPiece != curPiece && testPiece != 's')
    {
        return true;
    }
    return false;
}

void Game::moveTest(char curPiece, int row, int col)
{
    bool test1 = Game::upMove(curPiece, row, col);
    bool test2 = Game::downMove(curPiece, row, col);
    bool test3 = Game::rightMove(curPiece, row, col);
    bool test4 = Game::leftMove(curPiece, row, col);
    bool test5 = Game::uprightMove(curPiece,row, col);
    bool test6 = Game::upleftMove(curPiece, row, col);
    bool test7 = Game::downrightMove(curPiece, row, col);
    bool test8 = Game::downleftMove(curPiece, row, col);

    if(test1||test2||test3||test4||test5||test6||test7||test8)
        Game::inputTest = true;
    else
        Game::inputTest = false;
}

void Game::possibleMoveTest(char currentPiece)
{
    char testPiece = currentPiece;
    bool test;
    bool nextTest;

    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(testPiece == 'X' || testPiece == 'O')
            {

                bool test1 = Game::upMove(testPiece, row, col);
                bool test2 = Game::downMove(testPiece, row, col);
                bool test3 = Game::rightMove(testPiece, row, col);
                bool test4 = Game::leftMove(testPiece, row, col);
                bool test5 = Game::uprightMove(testPiece,row, col);
                bool test6 = Game::upleftMove(testPiece, row, col);
                bool test7 = Game::downrightMove(testPiece, row, col);
                bool test8 = Game::downleftMove(testPiece, row, col);

                if(test1||test2||test3||test4||test5||test6||test7||test8)
                    nextTest = true;
                else
                    nextTest = false;
            }
            if(test||nextTest)
                test = true;
            else
                test = false;
        }
        Game::possibleMove = test;
    }
}


char Game::getData(int row, int col)
{
    char x = data[row][col];
    return x;
}


