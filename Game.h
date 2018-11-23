#ifndef GAME_H
#define GAME_H

class Game
{
    public:
        void banner();
        char mainMenu();
        void help();
        void exit();
        void boardPrint(char boardData[8][8], int score1, int score2, char curPlyr, char piece1, char piece2, bool curSuper1, bool curSuper2);
        void changeBoard(char x[8][8]);
        void changeData(char x, int row, int col);
        int changetoCoor(char x);
        char getData(int row, int col);

        void upTest(char curPiece, int row, int col);                   //function for flip test
        void downTest(char curPiece, int row, int col);
        void rightTest(char curPiece, int row, int col);
        void leftTest(char curPiece, int row, int col);
        void uprightTest(char curPiece, int row, int col);
        void upleftTest(char curPiece, int row, int col);
        void downrightTest(char curPiece, int row, int col);
        void downleftTest(char curPiece, int row, int col);

        void moveTest(char curPiece,int row, int col);
        void possibleMoveTest(char currentPiece);
        bool getInputTest();
        bool getPossibleMove();

        bool upMove(char x,int row, int col);                           //function for possible move test
        bool downMove(char x,int row, int col);
        bool rightMove(char x,int row, int col);
        bool leftMove(char x, int row, int col);
        bool uprightMove(char x, int row, int col);
        bool upleftMove(char x, int row, int col);
        bool downrightMove(char x, int row, int col);
        bool downleftMove(char x, int row, int col);

        bool super2MoveTest(char x, int row, int col);                  //function for super2 flip test

        void changeSuper1(bool x);
        void changeSuper2(bool x);
        bool getSuper1();
        bool getSuper2();

    protected:
        char data[8][8];

    private:
        bool inputTest;
        bool possibleMove;
        bool super1;
        bool super2;
};

#endif // GAME_H
