#include "NameWidget.h"
#include <QtDebug>

NameWidget::NameWidget(QString *name1, QString *name2) : QWidget(),
    nameEnterButton(nullptr),
    nameCancelButton(nullptr),
    nameLayout(nullptr),
    nameTitleText(nullptr),
    namePromp1(nullptr),
    namePromp2(nullptr),
    namePlayer1(name1),
    namePlayer2(name2),
    nameBox1(nullptr),
    nameBox2(nullptr)
{

    nameLayout = new QGridLayout(this);


    nameTitleText = new QLabel("Entrez le nom des joueurs", this);
    nameTitleText->setFont(QFont("Comic Sans MS", 16));

    namePromp1 = new QLabel("Nom du joueur 1:", this);
    namePromp2 = new QLabel("Nom du joueur 2:", this);


	// the constructor autofill the text box with the previous names
	// this allows replaying with the same names, as requested in the instructions
	nameBox1 = new QLineEdit(*namePlayer1, this);
    nameBox1->setStyleSheet("border: 1px solid red");
    nameBox2 = new QLineEdit(*namePlayer2, this);
    nameBox2->setStyleSheet("border: 1px solid #fadb2d");


    nameEnterButton = new QPushButton("Confirmer", this);
    QObject::connect(nameEnterButton, SIGNAL(clicked(bool)), this, SLOT(confimName()));

    nameCancelButton = new QPushButton("Annuler", this);
    // the button is connected in the parent widget


    nameLayout->addWidget(nameTitleText, 0, 0, 1, 2);
    nameLayout->addWidget(namePromp1, 1, 0, 1, 2);
    nameLayout->addWidget(nameBox1, 2, 0, 1, 2);
    nameLayout->addWidget(namePromp2, 3, 0, 1, 2);
    nameLayout->addWidget(nameBox2, 4, 0, 1, 2);
    nameLayout->addWidget(nameEnterButton, 5, 0);
    nameLayout->addWidget(nameCancelButton, 5, 1);

    setLayout(nameLayout);
    setWindowTitle("Noms des joueurs");
}

void NameWidget::confimName() {
	*namePlayer1 = nameBox1->text();
    *namePlayer2 = nameBox2->text();
	// "return" the text content of the nameBoxN object to the namePlayerN string
	// This namePlayerN string share the same adress as the playerN string of the menuScreen
	// They are syncronised, so no need to actually [return] anything

}

/*  Note that the user is never forced to actually enter any names.
 *  If a promp box is left empty, an empty string is returned
 *  and passed to the gameSreen's constructor.
 *  It's only then that the gameSreen's constructor fill a new string with a default name.
 *  It could fill it with a default name right away, but that way, when a new game is requested,
 *  the popup auto fill the promp box with the original empty string,
 *  instead of one filled with a default name,
 *  and the user is not forced to enter a name if he doesn't want to.
 *
 *  I think this is a much more modern and natural approach
 *  than forcing the user to enter two names on a local 2 player game
 *  which feels way too much "old style" and outdated.
*/

