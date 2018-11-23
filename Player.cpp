#include "Game.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

Player::Player()
{
    score = 2;
    Game::changeSuper1(true);
    Game::changeSuper2(true);
}

void Player::changePiece(char xORo)
{
    piece = xORo;
}

void Player::changeScore(int newScore)
{
    score = newScore;
}

void Player::updateScore()
{
    int newScore = 0;
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(data[row][col] == getPiece())
                newScore++;
        }
    }
    Player::changeScore(newScore);
}

void Player::save(char fileName[100])
{
    ofstream fout(fileName);

    fout << "CURRENT PLAYER" << endl;
    fout << Player::getPiece() << endl << endl;

    fout << "BOARD" << endl;
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(col < 7)
                fout << data[row][col] << ", ";
            else
                fout << data[row][col];
        }
        fout << endl;
    }
}

void Player::load(char fileName[100])
{
    ifstream fin(fileName);

    for(int i = 0; i < 14; i++)
    {
        fin.ignore();
    }

    char loadPiece;
    fin >> loadPiece;
    char comma;

    for(int i = 0; i < 7; i++)
    {
        fin.ignore();
    }
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(col < 7)
                fin >> data[row][col] >> comma;
            else
                fin >> data[row][col];
        }
    }

    Player::changePiece(loadPiece);
}

int Player::getScore()
{
    return score;
}


char Player::getPiece()
{
    char x = piece;
    return x;
}



