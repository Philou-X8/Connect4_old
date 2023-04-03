#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>


class GameBoard : public QWidget // gameBoard

{
    Q_OBJECT
public:
    GameBoard(char startingColor);
    ~GameBoard();

    void gameStarted();
    void addToken(const int column, const char color);


public slots:
    void hoveredDrop(const int column);

signals:
    void gameWon();
    void gameTied();
    void toggleColorSignal();

private:

    QGridLayout *boardLayout;

    QPixmap *redTokenTex; // Tex is for texture
    QPixmap *yellowTokenTex;
    QPixmap *blankTokenTex;

    QLabel *hoveringToken;
    QPixmap *hoveringRedTex;
    QPixmap *hoveringYellowTex;

    QLabel *lastTokenHiTex; // texture // Highlight the latest added token

    QLabel *boardBgTex; // texture

    char gameBoard[7][6]; // store what token are played and where. used to seek a winner.
    // char cause i really dont need more than a byte.
    int columnSize[7] = {0}; // expected amount of token in a given column. for quick navigation of the arrays.
    // used as index in the array, so i'll leave it as an int.

    QLabel *shownBoard[7][6]; // contain the displayed objects. A mirror of the gameBoard[][].


    int turnCount; // number of token added

    bool seekWinner(const int x, const int y, const char color);
    int checkLine(int x, int y, const int varX, const int varY, const char color);

};

#endif // GAMEBOARD_H
