#include "fenetreJeu.h"
#include <QApplication>
#include <QMessageBox>

//--------------------------------------------------
//          --- Replay Button Display ---
//--------------------------------------------------
optionWidget::optionWidget() : QWidget(),
    optionReplay(nullptr),
    optionQuit(nullptr),
    optionLayout(nullptr),
    optionBackground(nullptr),
    optionReplayHi(nullptr),
    optionQuitHi(nullptr)
{

    optionLayout = new QGridLayout;

    optionBackground = new QLabel;
    optionBackground->setAlignment(Qt::AlignCenter);
    optionBackground->setPixmap(QPixmap("../textures/UI_option.png"));

    optionReplay = new LabelButton(QPixmap("../textures/UI_play.png"));
    optionReplayHi = new QLabel;
    optionReplayHi->setAlignment(Qt::AlignCenter);
    optionReplayHi->setPixmap(QPixmap("../textures/UI_play_hi.png"));
    optionReplayHi->hide();
    QObject::connect(optionReplay, SIGNAL(isHovered()), optionReplayHi, SLOT(show())); // connect the button to it's highlight
    QObject::connect(optionReplay, SIGNAL(notHovered()), optionReplayHi, SLOT(hide()));

    optionQuit = new LabelButton(QPixmap("../textures/UI_quit.png"));
    optionQuitHi = new QLabel;
    optionQuitHi->setAlignment(Qt::AlignCenter);
    optionQuitHi->setPixmap(QPixmap("../textures/UI_quit_hi.png"));
    optionQuitHi->hide();
    QObject::connect(optionQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(optionQuit, SIGNAL(isHovered()), optionQuitHi, SLOT(show())); // connect the button to it's highlight
    QObject::connect(optionQuit, SIGNAL(notHovered()), optionQuitHi, SLOT(hide()));

    optionLayout->addWidget(optionBackground, 0, 0, 4, 1);
    optionLayout->addWidget(optionReplayHi, 1, 0);
    optionLayout->addWidget(optionReplay, 1, 0);
    optionLayout->addWidget(optionQuitHi, 2, 0);
    optionLayout->addWidget(optionQuit, 2, 0);

    optionLayout->setAlignment(Qt::AlignCenter);

    setLayout(optionLayout);

}
optionWidget::~optionWidget(){
    delete optionReplay;
    delete optionQuit;
    delete optionLayout;
    delete optionBackground;
    delete optionReplayHi;
    delete optionQuitHi;

}

//--------------------------------------------------
//          --- Players' Name Display ---
//--------------------------------------------------
playerWidget::playerWidget(const QString *player1, const QString *player2, char *turnColor, int *gameState) : QWidget(),
    playerLayout(nullptr),
    playerBackground(nullptr),
    playerHi(nullptr),
    playerName1(*player1),
    playerName2(*player2),
    playerDisplay1(nullptr),
    playerDisplay2(nullptr),
    playerText(nullptr),
    turnColorPtr(turnColor),
    gameStatePtr(gameState)
{
    playerLayout = new QGridLayout;

    playerBackground = new QLabel;
    playerBackground->setAlignment(Qt::AlignCenter);
    playerBackground->setPixmap(QPixmap("../textures/UI_name.png"));

    playerHi = new QLabel;
    playerHi->setAlignment(Qt::AlignCenter);
    playerHi->setPixmap(QPixmap("../textures/UI_name_hi.png"));

    if(playerName1.size()>12) playerName1.chop(playerName1.size()-12); // to prevent super long name that breaks the UI
    if(playerName1 == "") { playerName1 = "Joueur 1"; } // autofill blank name to "Joueur 1"
    playerDisplay1 = new QLabel(playerName1);
    playerDisplay1->setFont(QFont("Comic Sans MS", 16));
    playerDisplay1->setAlignment(Qt::AlignCenter);

    if(playerName2.size()>12) playerName2.chop(playerName2.size()-12); // to prevent super long name that breaks the UI
    if(playerName2 == "") { playerName2 = "Joueur 2"; } // autofill blank name to "Joueur 2"
    playerDisplay2 = new QLabel(playerName2);
    playerDisplay2->setFont(QFont("Comic Sans MS", 16));
    playerDisplay2->setAlignment(Qt::AlignCenter);

    playerText = new QLabel("");
    playerText->setAlignment(Qt::AlignCenter);

    playerLayout->addWidget(playerBackground, 0, 0, 6, 1);
    playerLayout->addWidget(playerHi, 1, 0);
    playerLayout->addWidget(playerDisplay1, 1, 0);
    playerLayout->addWidget(playerDisplay2, 2, 0);
    playerLayout->addWidget(playerText, 3, 0, 2, 1);

    playerLayout->setAlignment(Qt::AlignCenter);
    setLayout(playerLayout);
}

playerWidget::~playerWidget(){
    delete playerLayout;
    delete playerBackground;
    delete playerHi;
    delete playerDisplay1;
    delete playerDisplay2;
    delete playerText;
    turnColorPtr = nullptr;
    gameStatePtr = nullptr;

}

void playerWidget::updatePlayerTurn(){ // update the message below the players' name

    QString newText;
    if (*gameStatePtr == 3){ // could have used a switch case here. worth it?
        newText += "Égalité:\n" "La grille est pleine";
    } else if (*gameStatePtr == 2 ){
        newText += "Le gangnant est:\n";
        newText += getName();
    } else {
        newText += "Au tour de:\n";
        newText += getName();
    }

    playerText->setText(newText);
}

void playerWidget::updatePlayerHi(){ // update the highlight texture under the players' name
    if(*turnColorPtr == 'r'){
        playerLayout->addWidget(playerHi, 1, 0);
    } else {
        playerLayout->addWidget(playerHi, 2, 0);
    }
}

QString playerWidget::getName() const {
    if(*turnColorPtr == 'r') {
        return playerName1 + "\n(rouge)";
    } else {
        return playerName2 + "\n(jaune)";
    }
}




//--------------------------------------------------
//           --- Game's Main Class ---
//--------------------------------------------------
fenetreJeu::fenetreJeu(QString *player1, QString *player2) : QWidget(),
    gameState(0),

    gameLayout(nullptr),
    gameBoard(nullptr),
    dropButtonLayout(nullptr),
    optionDisplay(nullptr),
    playerDisplay(nullptr),

    dropButtonTex(nullptr),
    dropSignalMapClicked(nullptr),
    dropSignalMapHovered(nullptr),

    gameUiBackground(nullptr),
    gameUiGrid(nullptr)

{


//------------------------------------------------------------ Main Layouts
    gameLayout = new QGridLayout; // main layout

//------------------------------------------------------------ Starting player
    qsrand(reinterpret_cast<uintptr_t>(gameLayout)); // just use an unrelated dynamic pointer's adress as the seed. This is legit.
    if((qrand()%2) == 0){
        turnColor = 'r';
    } else {
        turnColor = 'y';
    }
//------------------------------------------------------------ Grid
    gameBoard = new GameBoard(turnColor); // game board widget
    QObject::connect(gameBoard, SIGNAL(gameWon()), this, SLOT(DoOnWin()));
    QObject::connect(gameBoard, SIGNAL(gameTied()), this, SLOT(DoOnTie()));
    QObject::connect(gameBoard, SIGNAL(toggleColorSignal()), this, SLOT(toggleColor()));

//------------------------------------------------------------ Option Display
    optionDisplay = new optionWidget;
    QObject::connect(optionDisplay->optionReplay, SIGNAL(clicked()), SIGNAL(OpenGameSignal())); // recieve clicked signal and emit OpenGame to the main window

//------------------------------------------------------------ Name Display
    playerDisplay = new playerWidget(player1, player2, &turnColor, &gameState);
    playerDisplay->updatePlayerTurn();
    playerDisplay->updatePlayerHi();

//------------------------------------------------------------ Drop Buttons
    dropButtonLayout = new QGridLayout; // drop button layout

    dropSignalMapClicked = new QSignalMapper; // clicked
    dropSignalMapHovered = new QSignalMapper; // hovered
    dropButtonTex = new QPixmap("../textures/UI_drop_button.png");

    for(int i(0); i<7; i++)
    {
        dropButton[i] = new LabelButton(*dropButtonTex);
        dropButton[i]->setScaledContents(true);
        dropButtonLayout->addWidget(dropButton[i], 0, i, 4, 1);

        QObject::connect(dropButton[i], SIGNAL(clicked()), dropSignalMapClicked, SLOT(map()));
        dropSignalMapClicked->setMapping(dropButton[i], i);
        QObject::connect(dropButton[i], SIGNAL(isHovered()), dropSignalMapHovered, SLOT(map()));
        dropSignalMapHovered->setMapping(dropButton[i], i);
    }
    QObject::connect(dropSignalMapClicked, SIGNAL(mapped(int)), this, SLOT(clickedDrop(int)));
    QObject::connect(dropSignalMapHovered, SIGNAL(mapped(int)), gameBoard, SLOT(hoveredDrop(int)));

    delete dropButtonTex;
    // The texture was opened in RAMs to be copied to the drop buttons.
    // Faster to copy it from the RAMs than to open new ones from the disk every time.
    // Now that it has been copied, the original is not used anymore and can be deleted.

//------------------------------------------------------------ Other Visual Setups
    gameUiBackground = new QLabel;
    gameUiBackground->setAlignment(Qt::AlignCenter);
    gameUiBackground->setScaledContents(true);
    gameUiBackground->setPixmap(QPixmap("../textures/UI_bg.png"));

    gameUiGrid = new QLabel;
    gameUiGrid->setAlignment(Qt::AlignCenter);
    gameUiGrid->setPixmap(QPixmap("../textures/UI_grid.png"));



    gameLayout->addWidget(gameUiBackground, 0, 0, 2, 3); // full size
    gameLayout->addWidget(gameBoard, 0, 0, 2, 3);
    gameLayout->addWidget(gameUiGrid, 0, 0, 2, 3);
    gameLayout->addWidget(playerDisplay, 0, 0);
    gameLayout->addWidget(optionDisplay, 0, 2);
    gameLayout->addLayout(dropButtonLayout, 0, 1, 2, 1);
    setLayout(gameLayout);
}
fenetreJeu::~fenetreJeu(){

    for (int i(0); i<7; i++) {
        delete dropButton[i];
    }
    delete dropSignalMapClicked;
    delete dropSignalMapHovered;

    delete dropButtonLayout; // dropButton[i] must be deleted first

    delete gameUiBackground;
    delete gameUiGrid;

    delete gameBoard;
    delete optionDisplay;
    delete playerDisplay;
    delete gameLayout;

}


void fenetreJeu::clickedDrop(const int column){

    if(gameState == 0){
        gameBoard->gameStarted();
        gameState=1;
    }
    if (gameState < 2) { // prevent players form continuing to play after the game is over
    gameBoard->addToken(column, turnColor); // adding token is managed by the GameBoard class
    playerDisplay->updatePlayerTurn();
    }
}

void fenetreJeu::DoOnWin() {

    gameState = 2;
    playerDisplay->updatePlayerTurn();

    QString messageTextWin("Le gagnant est\n");
    messageTextWin += playerDisplay->getName() += "\n";
    messageTextWin += "Voulez-vous lancer une nouvelle partie?";

    if (QMessageBox::Yes == QMessageBox(QMessageBox::NoIcon, "Partie terminée", messageTextWin, QMessageBox::Yes|QMessageBox::No).exec())
    {
        emit OpenGameSignal();
    }

}

void fenetreJeu::DoOnTie() {
    gameState = 3;
    playerDisplay->updatePlayerTurn();

    QString messageTextTie("Égalité:\n"
                       "La grille est pleine\n"
                       "Voulez-vous lancer une nouvelle partie?");

    if (QMessageBox::Yes == QMessageBox(QMessageBox::NoIcon, "Partie terminée", messageTextTie, QMessageBox::Yes|QMessageBox::No).exec())
    {
        emit OpenGameSignal();
    }
}

void fenetreJeu::toggleColor(){
    if(turnColor == 'r'){
        turnColor = 'y';
    }
    else {
        turnColor = 'r';
    }
    playerDisplay->updatePlayerHi();
}









