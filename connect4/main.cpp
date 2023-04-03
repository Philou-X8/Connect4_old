#include<QApplication>
#include "fenetrePrincipale.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setFont(QFont("Comic Sans MS", 12));

	fenetrePrincipale menuScreen;
	menuScreen.show();


    return app.exec();
}
