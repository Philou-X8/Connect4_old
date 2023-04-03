#include "fenetreRegles.h"

fenetreRegles::fenetreRegles() : QWidget(),
    ruleLayout(nullptr),
    ruleBackgroundTex(nullptr),
    ruleGoalTitle(nullptr),
    ruleGoal(nullptr),
    ruleTurnsTitle(nullptr),
    ruleTurns(nullptr),
    ruleWinTitle(nullptr),
    ruleWin(nullptr),
    ruleCloseButton(nullptr)

{
    ruleLayout = new QGridLayout(this); // setup the main layout

//----------------------------------------------------------------- background texture
    ruleBackgroundTex = new QLabel(this);
    ruleBackgroundTex->setPixmap(QPixmap("../textures/rule_bg.png"));
    ruleBackgroundTex->setAlignment(Qt::AlignLeft);
    ruleBackgroundTex->setScaledContents(true);
//----------------------------------------------------------------- section title
    ruleGoalTitle = new QLabel("But du jeu ", this);
    setTitleFont(ruleGoalTitle);
//----------------------------------------------------------------- text
    ruleGoal = new QLabel
    (
    "Le but est de créer une ligne droite de 4 ou plus jetons de sa couleur. "
    "La ligne peut être horizontale, verticale ou diagonale."
    , this);
    setTextFont(ruleGoal);
//----------------------------------------------------------------- section title
    ruleTurnsTitle = new QLabel("Déroulement de la partie ", this);
    setTitleFont(ruleTurnsTitle);
//----------------------------------------------------------------- text
    ruleTurns = new QLabel
    (
    "Pour se faire, 2 joueurs ajoutent à tour de rôle un jeton de leur couleur dans la grille de jeu. "
    "Les jetons sont placés dans le haut d'une colonne et descendent automatiquement vers la case libre la plus basse."
    , this);
    setTextFont(ruleTurns);
//----------------------------------------------------------------- section title
    ruleWinTitle = new QLabel("Fin de la partie ", this);
    setTitleFont(ruleWinTitle);
//----------------------------------------------------------------- text
    ruleWin = new QLabel
    (
    "La partie prend fin quand l'un des deux joueurs complète une ligne et gagne ou quand la grille de jeu est remplie."
    , this);
    setTextFont(ruleWin);
//----------------------------------------------------------------- close button
    ruleCloseButton = new QPushButton("Fermer", this);
    ruleCloseButton->setFont(QFont("Comic Sans MS", 12));
    QObject::connect(ruleCloseButton, SIGNAL(clicked(bool)), this, SLOT(close()));
//-----------------------------------------------------------------

    ruleLayout->addWidget(ruleBackgroundTex, 0, 0, 7, 1);
    ruleLayout->addWidget(ruleGoalTitle, 0, 0);
    ruleLayout->addWidget(ruleGoal, 1, 0);
    ruleLayout->addWidget(ruleTurnsTitle, 2, 0);
    ruleLayout->addWidget(ruleTurns, 3, 0);
    ruleLayout->addWidget(ruleWinTitle, 4, 0);
    ruleLayout->addWidget(ruleWin, 5, 0);
    ruleLayout->addWidget(ruleCloseButton, 6, 0);

    setLayout(ruleLayout);
    setWindowTitle("Règlements");
    setFixedSize(QSize(471, 636));
}

// I have many blocks of text and i can't really put them in a for(){} loop,
// so i just call those fuctions to quickly give them their look.

void fenetreRegles::setTitleFont(QLabel *text)
{
    text->setFont(QFont("Comic Sans MS", 24));  // set the font and size
    text->setAlignment(Qt::AlignVCenter);       // align
    text->setMargin(5);                         // give it a margin so it's not glued to the edge
}

void fenetreRegles::setTextFont(QLabel *text)
{
    text->setFont(QFont("Comic Sans MS", 16));      // set the font and size
    text->setStyleSheet("QLabel {color : white}");  // make the text white
    text->setAlignment(Qt::AlignVCenter);           // align
    text->setMargin(5);                             // give it a margin so it's not glued to the edge
    text->setWordWrap(true);                        // to avoid 2-monitor-long line of text
}

