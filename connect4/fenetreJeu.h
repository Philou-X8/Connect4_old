#ifndef FENETREJEU_H
#define FENETREJEU_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QSignalMapper>
#include <QString>

#include "CustomLabel.h"
#include "GameBoard.h"
//--------------------------------------------------
//          --- Replay Button Display ---
//--------------------------------------------------
class optionWidget : public QWidget // optionDisplay
{
    Q_OBJECT
public:
    optionWidget();
    ~optionWidget();

    LabelButton *optionReplay;
    LabelButton *optionQuit;

private:
    QGridLayout *optionLayout;
    QLabel *optionBackground;
    QLabel *optionReplayHi;
    QLabel *optionQuitHi;

};
//--------------------------------------------------
//          --- Players' Name Display ---
//--------------------------------------------------
class playerWidget : public QWidget // playerDisplay
{

public:
    playerWidget(const QString *player1,
                 const QString *player2,
                 char *turnColor,
                 int *gameState);
    ~playerWidget();

    void updatePlayerTurn();
    void updatePlayerHi();
    QString getName() const;

private:
    QGridLayout *playerLayout;
    QLabel *playerBackground;
    QLabel *playerHi;
    QString playerName1;
    QString playerName2;
    QLabel *playerDisplay1;
    QLabel *playerDisplay2;
    QLabel *playerText;

    char *turnColorPtr;
    int *gameStatePtr;

};
//--------------------------------------------------
//           --- Game's Main Class ---
//--------------------------------------------------
class fenetreJeu : public QWidget // GameScreen
{
    Q_OBJECT
public:
    fenetreJeu(QString *player1, QString *player2);
    ~fenetreJeu();

    int gameState;
    // 0 = game has not started yet
    // 1 = game is ongoing
    // 2 = game is over - won
    // 3 = game is over - tied

signals:
    void OpenGameSignal();

public slots:
    void clickedDrop(const int column);
    void DoOnWin();
    void DoOnTie();
    void toggleColor();


private:
    // --- UI Layouts ---
    QGridLayout *gameLayout; // main layout

    GameBoard *gameBoard; //QWidget // grid with the tokens
    QGridLayout *dropButtonLayout; // button over each columns
    optionWidget *optionDisplay;
    playerWidget *playerDisplay;


    // --- Drop Button ---
    LabelButton *dropButton[7];
    QPixmap *dropButtonTex;
    QSignalMapper *dropSignalMapClicked;
    QSignalMapper *dropSignalMapHovered;


    // --- Generic ---
    QLabel *gameUiBackground;
    QLabel *gameUiGrid;
    char turnColor;

};



#endif // FENETREJEU_H





