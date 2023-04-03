#include "GameBoard.h"

GameBoard::GameBoard(char startingColor) : QWidget(),
    boardLayout(nullptr),

    redTokenTex(nullptr),
    yellowTokenTex(nullptr),
    blankTokenTex(nullptr),

    hoveringToken(nullptr),
    hoveringRedTex(nullptr),
    hoveringYellowTex(nullptr),

    lastTokenHiTex(nullptr),
    boardBgTex(nullptr),
    turnCount(0)

{
    boardLayout = new QGridLayout;
    boardLayout->setSpacing(0);

    redTokenTex = new QPixmap("../textures/board_red.png");
    yellowTokenTex = new QPixmap("../textures/board_yellow.png");
    blankTokenTex = new QPixmap("../textures/board_blank.png");

    boardBgTex = new QLabel;
    boardBgTex->setPixmap(QPixmap("../textures/board_bg.png"));
    boardBgTex->setAlignment(Qt::AlignCenter);
    boardBgTex->setScaledContents(true); // -------------------------

    boardLayout->addWidget(boardBgTex, 0, 0, 6, 7);

    lastTokenHiTex = new QLabel;
    lastTokenHiTex->setPixmap(QPixmap("../textures/board_last_token.png"));
    lastTokenHiTex->setAlignment(Qt::AlignCenter);
    lastTokenHiTex->hide();
    lastTokenHiTex->setScaledContents(true); // ------------------------------
    boardLayout->addWidget(lastTokenHiTex, 0, 0);

    hoveringRedTex = new QPixmap("../textures/UI_red.png");
    hoveringYellowTex = new QPixmap("../textures/UI_yellow.png");

    hoveringToken = new QLabel;
    if(startingColor == 'r'){
        hoveringToken->setPixmap(*hoveringRedTex);
    }
    else {
        hoveringToken->setPixmap(*hoveringYellowTex);
    }
    hoveringToken->setAlignment(Qt::AlignCenter);
    hoveringToken->hide();
    boardLayout->addWidget(hoveringToken, 5, 3);

    // fill the board with blank tokens
    for(int x(0); x<7; x++){
        for(int y(0); y<6; y++){
            gameBoard[x][y] = 0; // mark the board as "empty"
            shownBoard[x][y] = new QLabel;
            shownBoard[x][y]->setPixmap(*blankTokenTex);
            shownBoard[x][y]->setAlignment(Qt::AlignCenter);
            boardLayout->addWidget(shownBoard[x][y], 5-y, x);
        }
    }
    delete blankTokenTex;

    boardLayout->setAlignment(Qt::AlignCenter);
    setLayout(boardLayout);
}
GameBoard::~GameBoard(){
    delete boardLayout;
    delete redTokenTex;
    delete yellowTokenTex;
    delete lastTokenHiTex;
    delete boardBgTex;
    delete hoveringToken;
    delete hoveringRedTex;
    delete hoveringYellowTex;
    for(int x(0); x<7; x++){
        for(int y(0); y<6; y++){
            delete shownBoard[x][y];
        }
    }

}


void GameBoard::gameStarted(){
    lastTokenHiTex->show();
}

void GameBoard::addToken(const int x, const char color){

    if(columnSize[x] < 6){
        int y = columnSize[x]; // columnSize is 1 unit bigger, but you want to offset Y by 1, so no +- modifier.

        boardLayout->addWidget(lastTokenHiTex, 5-y, x);
        gameBoard[x][y] = color;

        // switch colour
        if(color == 'r'){
            shownBoard[x][y]->setPixmap(*redTokenTex);
            hoveringToken->setPixmap(*hoveringYellowTex);
        }
        else {
            shownBoard[x][y]->setPixmap(*yellowTokenTex);
            hoveringToken->setPixmap(*hoveringRedTex);
        }

        if(seekWinner(x, y, color)){ // check for a winner
            emit gameWon();
        } else if(turnCount>=41){ // check if the grid is full
            emit gameTied();
        } else {
            emit toggleColorSignal();
        }

        columnSize[x]++;
        turnCount++;
        hoveredDrop(x);
    }

}

void GameBoard::hoveredDrop(const int column){
    if( columnSize[column] < 6){
        boardLayout->addWidget(hoveringToken, 5 - columnSize[column], column);
        if(hoveringToken->isHidden()){
            hoveringToken->show();
        }
    } else {
        hoveringToken->hide();
    }
}

bool GameBoard::seekWinner(const int x, const int y, const char color){

    for(int dY = -1; dY <= 1; dY++){
        int combo(1);
        combo += checkLine(x, y, 1, dY, color);
        combo += checkLine(x, y, -1, -dY, color);

        if(combo >= 4) return true; // a winner was found
    }
    if (checkLine(x, y, 0, -1, color) >= 3) return true; // a winner was found
    return false; // no winner was found
}

int GameBoard::checkLine(int x, int y, const int varX, const int varY, const char color){
    int combo(-1);
    while(0<=x && x<=6 && 0<=y && y<=5 && gameBoard[x][y]==color){
        combo++;
        x += varX;
        y += varY;
    } // increase "combo" as long as the next cell is the same color

    return combo;
}




