#ifndef PLAYER_H
#define PLAYER_H


class Player:public Game
{
    public:
        Player();
        void changePiece(char xORo);
        char getPiece();

        void changeScore(int newScore);
        void updateScore();
        int getScore();

        void save(char fileName[100]);
        void load(char fileName[100]);


    private:
        int score;
        char piece;
};

#endif // PLAYER_H
