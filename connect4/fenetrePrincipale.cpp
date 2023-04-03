#include "fenetrePrincipale.h"
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>
#include <QDebug>


fenetrePrincipale::fenetrePrincipale() : QMainWindow(),
    menuTabPartie(nullptr),
    menuTabAide(nullptr),
    menuGame(nullptr),
    menuQuit(nullptr),
    menuRule(nullptr),
    menuInfo(nullptr),
    HomeScreen(nullptr),
    RuleScreen(nullptr),
    InfoScreen(nullptr),
    GameScreen(nullptr),
    player1(nullptr),
    player2(nullptr),
    playerNames(nullptr)
{
//----------------------------------------
	// add the "Partie" tab to the menu bar
	menuTabPartie = new QMenu;
    menuTabPartie = menuBar()->addMenu("Partie");

	menuGame = new QAction("Nouvelle Partie");	// sub menu
	menuTabPartie->addAction(menuGame);

	menuQuit = new QAction("Quitter");			// sub menu
	menuTabPartie->addAction(menuQuit);

//----------------------------------------
	// add the "Aide" tab to the menu bar
	menuTabAide = new QMenu;
	menuTabAide = menuBar()->addMenu("Aide");

	menuRule = new QAction("Règlements");		// sub menu
	menuTabAide->addAction(menuRule);

	menuInfo = new QAction("À Propos");			// sub menu
	menuTabAide->addAction(menuInfo);

//----------------------------------------

	HomeScreen = new fenetreAcceuil; // create the home screen
    setCentralWidget(HomeScreen);

//----------------------------------------
	RuleScreen = new fenetreRegles; // create the rule window
    RuleScreen->hide();

	InfoScreen = new fenetreAPropos; // create the info window
    InfoScreen->hide();

/*  I tested around a lot with this and realised
 *  neither the close() nor the [X] button calls the object's destructor.
 *  So, i belive it's much better to create those on startup
 *  then hide() and show() them as needed.
 *  Even if that takes a MB more of RAM, it is much easier and safer than
 *  dynamically allocating it and managing its destructor.
*/
//----------------------------------------

	player1 = new QString; // name of the player 1
	player2 = new QString; // name of the player 2


	// connect the buttons in the menu bar to what they should do
	QObject::connect(menuGame, SIGNAL(triggered()), this, SLOT(GameRequest())); // the 1st way a game can be launched
    QObject::connect(menuQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
	QObject::connect(menuRule, SIGNAL(triggered()), RuleScreen, SLOT(show()));
	QObject::connect(menuInfo, SIGNAL(triggered()), InfoScreen, SLOT(show()));


	QObject::connect(HomeScreen, SIGNAL(OpenGameSignal()), this, SLOT(GameRequest())); // the 2nd way a game can be launched


	// the 3rd way a game can be launched will be in Part 3
}
fenetrePrincipale::~fenetrePrincipale(){

    delete menuTabPartie;
    delete menuTabAide;

    delete menuGame;
    delete menuQuit;
    delete menuRule;
    delete menuInfo;

    if(HomeScreen != nullptr) delete HomeScreen;  // might have already been deleted
    delete RuleScreen;
    delete InfoScreen;
    if(GameScreen != nullptr) delete GameScreen;  // might not have been created yet

    delete player1;
    delete player2;
    if(playerNames != nullptr) delete playerNames;  // might not currently be oppened


}

void fenetrePrincipale::GameRequest(){

	if(GameScreen == nullptr) { // checks if no game have been opened yet

		requestName(); // get the players' names

	} else if(GameScreen->gameState != 1) { // check if the opened game is not ongoing
		// this needs to be in a separated [else it] instead of an [or]/[||] even if they execute the same action
		// otherwise it would try to access an empty pointer and crash the program.

		requestName(); // get the players' names

	} else if( QMessageBox::Yes == QMessageBox( // if the game is ongoing, request confirmation before "leaving" the game.
                   QMessageBox::NoIcon,
                   "Partie en cours",
                   "Partie déjà en cours.\nVoulez-vous continuer?",
                   QMessageBox::Yes|QMessageBox::Cancel).exec()
              ) {

		requestName(); // get the players' names

    }

}

void fenetrePrincipale::requestName(){ // manage the NameWidget custom input dialog

    if(playerNames!=nullptr) delete playerNames;  // delete the previous request if it was closed with the [X]. Prevent memory leak.

	playerNames = new NameWidget(player1, player2); // create the request popup, using the players' name to allow replaying with the same names.
    playerNames->show();
	QObject::connect(playerNames->nameEnterButton, SIGNAL(clicked(bool)), this, SLOT(requestConfirmed())); // by doing this from here, i don't have to relay signals
	QObject::connect(playerNames->nameCancelButton, SIGNAL(clicked(bool)), this, SLOT(requestCancelled())); // by doing this from here, i don't have to relay signals

}

void fenetrePrincipale::requestConfirmed(){ // if the request is completed, start a new game
	delete playerNames; // delete the popup, it's not needed anymore
    playerNames = nullptr;

    if(HomeScreen != nullptr){ // delete the HomeScreen before changing the central widget
        delete HomeScreen;
        HomeScreen = nullptr;
    }

    if(GameScreen != nullptr) delete GameScreen;  // checks if there's a game ongoing and delete it before creating a new one.

    GameScreen = new fenetreJeu(player1, player2); // start the game
    QObject::connect(GameScreen, SIGNAL(OpenGameSignal()), this, SLOT(GameRequest())); // the 3rd way a game can be launched

    setCentralWidget(GameScreen);
    move(QPoint(150, 50));
	// center the window assuming you have a 1080p screen
	// so it doesn't spawn in the bottom left of your screen like QT wants it to.
}

void fenetrePrincipale::requestCancelled(){ // close the name request popup if the user cancel
    delete playerNames; // gotta get that 0.1MB of RAM back
    playerNames = nullptr;
}
