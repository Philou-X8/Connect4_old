#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QMenu>
#include <QAction>

#include "fenetreAcceuil.h"
#include "fenetreRegles.h"
#include "fenetreAPropos.h"
#include "fenetreJeu.h"
#include "NameWidget.h"


class fenetrePrincipale : public QMainWindow // refered to as "menu"
{
    Q_OBJECT

public:
    fenetrePrincipale();
    ~fenetrePrincipale();

public slots:

	void GameRequest();
	// Called when the user want to start a new game.
	// Manage the interaction between the 3 ways a new game can be launched
	// along with the few popups that come with them or not.

	void requestConfirmed(); // launch the game if the request is confirmed
	void requestCancelled(); // cancel stuff related to the custom input dialog


private:
    QMenu *menuTabPartie;
    QMenu *menuTabAide;
    QAction *menuGame;
    QAction *menuQuit;
    QAction *menuRule;
    QAction *menuInfo;

	fenetreAcceuil *HomeScreen;
    fenetreRegles *RuleScreen;
    fenetreAPropos *InfoScreen;
    fenetreJeu *GameScreen;

	QString *player1; // name of the player 1
	QString *player2; // name of the player 2

	NameWidget *playerNames;
/*  This is a custom input dialog.
 *  I looked into QT's input dialog class (QInputDialog),
 *  however, they can only have one text box.
 *  Since there's 2 names, I either have 2 popups,
 *  or I ask the user to split the names with a comma or something.
 *  And I found neither of these options to be user friendly,
 *  so I made a custom input dialog.
*/

	void requestName(); // calls and manage the NameWidget custom input dialog

};

#endif // FENETREPRINCIPALE_H
