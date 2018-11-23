#include "Game.h"
#include "Player.h"
#include <iostream> //for using cout and cin
#include <fstream>  //for using ifstream and ofstream
#include <cstdlib>  //for using system("cls") and system("pause")
using namespace std;

int main()
{
    Player currentPlayer;

    char newBoard[8][8] = {{'s','s','s','s','s','s','s','s'},
                           {'s','s','s','s','s','s','s','s'},
                           {'s','s','s','s','s','s','s','s'},
                           {'s','s','s','O','X','s','s','s'},
                           {'s','s','s','X','O','s','s','s'},
                           {'s','s','s','s','s','s','s','s'},
                           {'s','s','s','s','s','s','s','s'},
                           {'s','s','s','s','s','s','s','s'}};

    bool menu =  true;
    while(menu)
    {
        Player plyr_1;
        Player plyr_2;

        system("cls");
        currentPlayer.banner();                                     //Game banner
        char menuChoice = currentPlayer.mainMenu();                 //Game menu

        if(menuChoice == '1' || menuChoice == '2')                  //if for new game and load. This is where the game will start or load a new game
        {
            bool newTurn = true;

            if(menuChoice == '1')
            {
                currentPlayer.changeBoard(newBoard);
                currentPlayer.changeSuper1(true);
                currentPlayer.changeSuper2(true);
                plyr_1 = currentPlayer;
                plyr_2 = currentPlayer;

                currentPlayer.changePiece('X');
                plyr_1.changePiece('X');
                plyr_2.changePiece('O');
            }
            else if(menuChoice == '2')
            {
                bool loadMenu = true;
                while(loadMenu)
                {
                    cout << string(50, '\n');
                    cout << "1. Load previous game" << endl;
                    cout << "2. Load different game" << endl;
                    cout << "3. Back to menu" << endl;
                    cout << endl << "Enter number: ";

                    char loadChoice;
                    cin >> loadChoice;


                    if(loadChoice == '1')
                    {
                        cin.ignore();
                        char prevGame[13] = "PrevGame.txt";
                        currentPlayer.load(prevGame);
                        currentPlayer.changeSuper1(true);
                        currentPlayer.changeSuper2(true);

                        plyr_1 = currentPlayer;
                        plyr_2 = currentPlayer;

                        plyr_1.changePiece(currentPlayer.getPiece());
                        if(plyr_1.getPiece() == 'X')
                            plyr_2.changePiece('O');
                        else
                            plyr_2.changePiece('X');

                        plyr_1.updateScore();
                        plyr_2.updateScore();

                        loadMenu = false;
                    }
                    else if(loadChoice == '2')
                    {
                        cin.ignore();
                        cout << endl;
                        char fileName[100];
                        cout << "Enter file name(ends with .txt): ";
                        cin.getline(fileName, sizeof(fileName));
                        ifstream fin(fileName);
                        if(!fin)
                        {
                            cout << "File does not exist!" << endl;
                            system("pause");
                        }
                        else
                        {
                            currentPlayer.load(fileName);
                            currentPlayer.changeSuper1(true);
                            currentPlayer.changeSuper2(true);

                            plyr_1 = currentPlayer;
                            plyr_2 = currentPlayer;

                            plyr_1.changePiece(currentPlayer.getPiece());
                            if(plyr_1.getPiece() == 'X')
                                plyr_2.changePiece('O');
                            else
                                plyr_2.changePiece('X');

                            plyr_1.updateScore();
                            plyr_2.updateScore();

                            loadMenu = false;
                        }
                    }
                    else if(loadChoice == '3')
                    {
                        cin.ignore();
                        newTurn = false;
                        loadMenu = false;
                    }
                }

            }

            int turnCounter = 1;
            while(newTurn)
            {
                char plyr1Piece = plyr_1.getPiece();
                char plyr2Piece = plyr_2.getPiece();
                char curPiece = currentPlayer.getPiece();

                int plyr1Score = plyr_1.getScore();
                int plyr2Score = plyr_2.getScore();

                char currentBoard[8][8];

                plyr_1.possibleMoveTest(plyr1Piece);
                plyr_2.possibleMoveTest(plyr2Piece);
                bool possibleMoveP1 = plyr_1.getPossibleMove();
                bool possibleMoveP2 = plyr_2.getPossibleMove();
                if(possibleMoveP1||possibleMoveP2)                                  //test if there is any move left for both players to know when the game finishes
                {
                    currentPlayer.possibleMoveTest(currentPlayer.getPiece());
                    bool possibleMoveCur = currentPlayer.getPossibleMove();         //test if there is any move left for current players to determine who moves next
                    if(possibleMoveCur)
                    {
                        for(int row = 0; row < 8; row++)
                        {
                            for(int col = 0; col < 8; col++)
                            {
                                currentBoard[row][col] = currentPlayer.getData(row, col);
                            }
                        }
                        cout << string(20, '\n');
                        currentPlayer.boardPrint(currentBoard, plyr1Score, plyr2Score, curPiece, plyr1Piece, plyr2Piece, (currentPlayer.getSuper1()), (currentPlayer.getSuper2()));         //screen will show game information and then ask for user input

                        char input[100];
                        string command;
                        cout << "Enter move(e.g. f 4 or super1) => ";
                        cin.getline(input, sizeof(input));
                        command = input;

                        if(((command[0] == 'a')||(command[0] == 'b')||(command[0] == 'c')||(command[0] == 'd')||(command[0] == 'e')||(command[0] == 'f')||(command[0] == 'g')||(command[0] == 'h'))                 // If user inputs the coordinates in this format(f 4)
                           && ((command[2] == '1')||(command[2] == '2')||(command[2] == '3')||(command[2] == '4')||(command[2] == '5')||(command[2] == '6')||(command[2] == '7')||(command[2] == '8')))
                        {
                            char input1 = command[0];
                            char input2 = command[2];

                            int rowCoor = currentPlayer.changetoCoor(input2);           //changing the input from the user to coordinates
                            int colCoor = currentPlayer.changetoCoor(input1);

                            currentPlayer.moveTest(curPiece, rowCoor, colCoor);         //test if the input is a valid move

                            bool allowMove = currentPlayer.getInputTest();
                            if(allowMove)                                               //if it is a valid move, game will run 8 tests and flips accordingly
                            {
                                currentPlayer.upTest(curPiece, rowCoor, colCoor);
                                currentPlayer.downTest(curPiece, rowCoor, colCoor);
                                currentPlayer.rightTest(curPiece, rowCoor, colCoor);
                                currentPlayer.leftTest(curPiece, rowCoor, colCoor);
                                currentPlayer.uprightTest(curPiece, rowCoor, colCoor);
                                currentPlayer.upleftTest(curPiece, rowCoor, colCoor);
                                currentPlayer.downrightTest(curPiece, rowCoor, colCoor);
                                currentPlayer.downleftTest(curPiece, rowCoor, colCoor);

                                currentPlayer.changeData(curPiece, rowCoor, colCoor);   //after finish flipping, the game then will insert the player's piece on the coordinates the player gave


                                for(int row = 0; row < 8; row++)
                                {
                                    for(int col = 0; col < 8; col++)
                                    {
                                        currentBoard[row][col] = currentPlayer.getData(row, col);
                                    }
                                }

                                plyr_1.changeBoard(currentBoard);       //updating game data after a successful move
                                plyr_2.changeBoard(currentBoard);

                                plyr_1.updateScore();
                                plyr_2.updateScore();

                                if(turnCounter % 2 != 0)                //change player
                                {
                                    if(curPiece == 'X')
                                        currentPlayer.changePiece('O');
                                    else
                                        currentPlayer.changePiece('X');

                                    currentPlayer.changeSuper1(plyr_2.getSuper1());
                                    currentPlayer.changeSuper2(plyr_2.getSuper2());
                                }
                                else
                                {
                                    if(curPiece == 'X')
                                        currentPlayer.changePiece('O');
                                    else
                                        currentPlayer.changePiece('X');

                                    currentPlayer.changeSuper1(plyr_1.getSuper1());
                                    currentPlayer.changeSuper2(plyr_1.getSuper2());
                                }

                                char prevGame[13] = "PrevGame.txt";     //saves the recent move in PrevGame.txt
                                currentPlayer.save(prevGame);

                                turnCounter++;
                            }
                            else
                            {
                                cout << endl << "Move not possible! Try again." << endl;        //if user inputs something other than coordinates and the in-game commands
                                system("pause");
                            }
                        }
                        else if(((command[0] == 'a')||(command[0] == 'b')||(command[0] == 'c')||(command[0] == 'd')||(command[0] == 'e')||(command[0] == 'f')||(command[0] == 'g')||(command[0] == 'h'))                 // If user inputs the coordinates in this format(f4)
                           && ((command[1] == '1')||(command[1] == '2')||(command[1] == '3')||(command[1] == '4')||(command[1] == '5')||(command[1] == '6')||(command[1] == '7')||(command[1] == '8')))                  // Everything in this else if statement is identical to the one above
                        {
                            char input1 = command[0];
                            char input2 = command[1];

                            int rowCoor = currentPlayer.changetoCoor(input2);
                            int colCoor = currentPlayer.changetoCoor(input1);

                            currentPlayer.moveTest(curPiece, rowCoor, colCoor);

                            bool allowMove = currentPlayer.getInputTest();
                            if(allowMove)
                            {
                                currentPlayer.upTest(curPiece, rowCoor, colCoor);
                                currentPlayer.downTest(curPiece, rowCoor, colCoor);
                                currentPlayer.rightTest(curPiece, rowCoor, colCoor);
                                currentPlayer.leftTest(curPiece, rowCoor, colCoor);
                                currentPlayer.uprightTest(curPiece, rowCoor, colCoor);
                                currentPlayer.upleftTest(curPiece, rowCoor, colCoor);
                                currentPlayer.downrightTest(curPiece, rowCoor, colCoor);
                                currentPlayer.downleftTest(curPiece, rowCoor, colCoor);

                                currentPlayer.changeData(curPiece, rowCoor, colCoor);

                                for(int row = 0; row < 8; row++)
                                {
                                    for(int col = 0; col < 8; col++)
                                    {
                                        currentBoard[row][col] = currentPlayer.getData(row, col);
                                    }
                                }
                                plyr_1.changeBoard(currentBoard);
                                plyr_2.changeBoard(currentBoard);

                                plyr_1.updateScore();
                                plyr_2.updateScore();

                                if(turnCounter % 2 != 0)
                                {
                                    if(curPiece == 'X')
                                        currentPlayer.changePiece('O');
                                    else
                                        currentPlayer.changePiece('X');

                                    currentPlayer.changeSuper1(plyr_2.getSuper1());
                                    currentPlayer.changeSuper2(plyr_2.getSuper2());
                                }
                                else
                                {
                                    if(curPiece == 'X')
                                        currentPlayer.changePiece('O');
                                    else
                                        currentPlayer.changePiece('X');

                                    currentPlayer.changeSuper1(plyr_1.getSuper1());
                                    currentPlayer.changeSuper2(plyr_1.getSuper2());
                                }
                                char prevGame[13] = "PrevGame.txt";
                                currentPlayer.save(prevGame);

                                turnCounter++;
                            }
                            else
                            {
                                cout << endl << "Move not possible! Try again." << endl;
                                system("pause");
                            }
                        }
                        else if(command == "next")              //not shown on help menu because it is one of the super power
                        {
                            if(turnCounter % 2 != 0)
                            {
                                if(curPiece == 'X')
                                    currentPlayer.changePiece('O');
                                else
                                    currentPlayer.changePiece('X');

                                currentPlayer.changeSuper1(plyr_2.getSuper1());
                                currentPlayer.changeSuper2(plyr_2.getSuper2());
                            }
                            else
                            {
                                if(curPiece == 'X')
                                    currentPlayer.changePiece('O');
                                else
                                    currentPlayer.changePiece('X');

                                currentPlayer.changeSuper1(plyr_1.getSuper1());
                                currentPlayer.changeSuper2(plyr_1.getSuper2());
                            }
                            char prevGame[13] = "PrevGame.txt";
                            currentPlayer.save(prevGame);

                            turnCounter++;
                        }
                        else if(command == "save")
                        {
                            char saveFile[100];
                            cout << endl << "Enter file name(ends with .txt) => ";          //ask user to enter a name for the save file
                            cin.getline(saveFile, sizeof(saveFile));
                            currentPlayer.save(saveFile);
                        }
                        else if(command == "menu")                                          //returns back to the menu loop
                        {
                            newTurn = false;
                        }
                        else if(command == "super1")                                        //super1 is the ability to pass a turn which is useful when the current player's only possible move will not benefit the player
                        {
                            if(currentPlayer.getSuper1())
                            {
                                currentPlayer.changeSuper1(false);
                                if(turnCounter % 2 != 0)
                                {
                                    if(curPiece == 'X')
                                        currentPlayer.changePiece('O');
                                    else
                                        currentPlayer.changePiece('X');

                                    plyr_1.changeSuper1(currentPlayer.getSuper1());

                                    currentPlayer.changeSuper1(plyr_2.getSuper1());
                                    currentPlayer.changeSuper2(plyr_2.getSuper2());
                                }
                                else
                                {
                                    if(curPiece == 'X')
                                        currentPlayer.changePiece('O');
                                    else
                                        currentPlayer.changePiece('X');

                                    plyr_2.changeSuper1(currentPlayer.getSuper1());

                                    currentPlayer.changeSuper1(plyr_1.getSuper1());
                                    currentPlayer.changeSuper2(plyr_1.getSuper2());
                                }
                                char prevGame[13] = "PrevGame.txt";
                                currentPlayer.save(prevGame);

                                turnCounter++;
                            }
                            else
                            {
                                cout << "Super power has been used!" << endl;
                                system("pause");
                            }
                        }
                        else if(command == "super2")                        //super2 is the ability to change one of the opponent's piece to your own which is useful when there is an opponent piece blocking your flipping and it is not possible to change it
                        {
                            if(currentPlayer.getSuper2())
                            {
                                char input[100];
                                string command;
                                cout << endl << "Enter super move(e.g. f 4) => ";
                                cin.getline(input, sizeof(input));
                                command = input;

                                if(((command[0] == 'a')||(command[0] == 'b')||(command[0] == 'c')||(command[0] == 'd')||(command[0] == 'e')||(command[0] == 'f')||(command[0] == 'g')||(command[0] == 'h'))                 //super2's instructions is quite same as the normal move's instruction. The difference is instead of testing on all 8 directions, super2 just checks if the piece in the coordinate is the opponent's piece and changes it
                                   && ((command[2] == '1')||(command[2] == '2')||(command[2] == '3')||(command[2] == '4')||(command[2] == '5')||(command[2] == '6')||(command[2] == '7')||(command[2] == '8')))
                                {
                                    char input1 = command[0];
                                    char input2 = command[2];

                                    int rowCoor = currentPlayer.changetoCoor(input2);
                                    int colCoor = currentPlayer.changetoCoor(input1);

                                    if(currentPlayer.super2MoveTest(curPiece, rowCoor, colCoor))
                                    {
                                        currentPlayer.changeData(curPiece, rowCoor, colCoor);

                                        currentPlayer.changeSuper2(false);
                                        if(turnCounter % 2 != 0)
                                        {
                                            if(curPiece == 'X')
                                                currentPlayer.changePiece('O');
                                            else
                                                currentPlayer.changePiece('X');

                                            plyr_1.changeSuper2(currentPlayer.getSuper2());

                                            currentPlayer.changeSuper1(plyr_2.getSuper1());
                                            currentPlayer.changeSuper2(plyr_2.getSuper2());
                                        }
                                        else
                                        {
                                            if(curPiece == 'X')
                                                currentPlayer.changePiece('O');
                                            else
                                                currentPlayer.changePiece('X');

                                            plyr_2.changeSuper2(currentPlayer.getSuper2());

                                            currentPlayer.changeSuper1(plyr_1.getSuper1());
                                            currentPlayer.changeSuper2(plyr_1.getSuper2());
                                        }
                                        char prevGame[13] = "PrevGame.txt";
                                        currentPlayer.save(prevGame);

                                        turnCounter++;
                                    }
                                    else
                                    {
                                        cout << endl << "Move is not possible! Try again." << endl;
                                        system("pause");
                                    }
                                }
                                else if(((command[0] == 'a')||(command[0] == 'b')||(command[0] == 'c')||(command[0] == 'd')||(command[0] == 'e')||(command[0] == 'f')||(command[0] == 'g')||(command[0] == 'h'))                 // If user inputs the coordinates
                                   && ((command[1] == '1')||(command[1] == '2')||(command[1] == '3')||(command[1] == '4')||(command[1] == '5')||(command[1] == '6')||(command[1] == '7')||(command[1] == '8')))
                               {
                                    char input1 = command[0];
                                    char input2 = command[1];

                                    int rowCoor = currentPlayer.changetoCoor(input2);
                                    int colCoor = currentPlayer.changetoCoor(input1);

                                    if(currentPlayer.super2MoveTest(curPiece, rowCoor, colCoor))
                                    {
                                        currentPlayer.changeData(curPiece, rowCoor, colCoor);

                                        currentPlayer.changeSuper2(false);
                                        if(turnCounter % 2 != 0)
                                        {
                                            if(curPiece == 'X')
                                                currentPlayer.changePiece('O');
                                            else
                                                currentPlayer.changePiece('X');

                                            plyr_1.changeSuper2(currentPlayer.getSuper2());

                                            currentPlayer.changeSuper1(plyr_2.getSuper1());
                                            currentPlayer.changeSuper2(plyr_2.getSuper2());
                                        }
                                        else
                                        {
                                            if(curPiece == 'X')
                                                currentPlayer.changePiece('O');
                                            else
                                                currentPlayer.changePiece('X');

                                            plyr_2.changeSuper2(currentPlayer.getSuper2());

                                            currentPlayer.changeSuper1(plyr_1.getSuper1());
                                            currentPlayer.changeSuper2(plyr_1.getSuper2());
                                        }
                                        char prevGame[13] = "PrevGame.txt";
                                        currentPlayer.save(prevGame);

                                        turnCounter++;
                                    }
                                    else
                                    {
                                        cout << endl << "Move is not possible! Try again." << endl;
                                        system("pause");
                                    }
                               }
                               else
                               {
                                   cout << "Invalid input!" << endl;
                                   system("pause");
                               }

                            }
                            else
                            {
                                cout << "Super power has been used!" << endl;
                                system("pause");
                            }
                        }
                        else
                        {
                            cout << endl << "Invalid input!" << endl;
                            system("pause");
                        }
                    }
                    else
                    {
                        char plyr = curPiece;

                        if(turnCounter % 2 != 0)
                        {
                            if(curPiece == 'X')
                            {
                                currentPlayer.changePiece('O');
                            }
                            else
                            {
                                currentPlayer.changePiece('X');
                            }
                        }
                        else
                        {
                            if(curPiece == 'X')
                            {
                                currentPlayer.changePiece('O');
                            }
                            else
                            {
                                currentPlayer.changePiece('X');
                            }
                        }
                        char newPlyr;
                        newPlyr = currentPlayer.getPiece();

                        for(int row = 0; row < 8; row++)
                        {
                            for(int col = 0; col < 8; col++)
                            {
                                currentBoard[row][col] = currentPlayer.getData(row, col);
                            }
                        }
                        cout << string(20, '\n');
                        currentPlayer.boardPrint(currentBoard, plyr1Score, plyr2Score, curPiece, plyr1Piece, plyr2Piece, (currentPlayer.getSuper1()), (currentPlayer.getSuper2()));
                        cout << endl << plyr << " has no more possible move" << endl;
                        cout << newPlyr << " moves again" << endl;
                        system("pause");

                        turnCounter++;
                    }
                }
                else
                {
                    char plyr1Piece = plyr_1.getPiece();
                    char plyr2Piece = plyr_2.getPiece();

                    plyr_1.updateScore();
                    plyr_2.updateScore();
                    int plyr1Score = plyr_1.getScore();
                    int plyr2Score = plyr_2.getScore();

                    for(int row = 0; row < 8; row++)
                    {
                        for(int col = 0; col < 8; col++)
                        {
                            currentBoard[row][col] = currentPlayer.getData(row, col);
                        }
                    }
                    cout << string(20, '\n');
                    currentPlayer.boardPrint(currentBoard, plyr1Score, plyr2Score, curPiece, plyr1Piece, plyr2Piece, (currentPlayer.getSuper1()), (currentPlayer.getSuper2()));

                    if(plyr1Score > plyr2Score)                     //test to check who wins
                    {
                        cout << endl << plyr1Piece << " wins!" << endl;
                        cout << "GGWP!" << endl;
                        system("pause");
                    }
                    else if(plyr1Score < plyr2Score)
                    {
                        cout << endl << plyr2Piece << " wins!" << endl;
                        cout << "GGWP!" << endl;
                        system("pause");
                    }
                    else
                    {
                        cout << endl << "It's a draw!" << endl;
                        system("pause");
                    }
                    newTurn = false;
                }
            }
        }
        else if(menuChoice == '3')          //opens the help
        {
            system("cls");
            currentPlayer.help();
            system("pause");
        }
        else if(menuChoice == '4')          //exit the game
        {
            break;
        }
        else
        {
            cout << "Invalid input!" << endl;
            system("pause");
            cin.ignore();
        }

    }
    currentPlayer.exit();

    return 0;
}
