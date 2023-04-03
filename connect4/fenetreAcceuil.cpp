#include "fenetreAcceuil.h"
#include <QApplication>

fenetreAcceuil::fenetreAcceuil() : QWidget(),
    homeLayout(nullptr),
    homeBackgroundTex(nullptr),
    homeLogoTex(nullptr),
    homeCpuTex(nullptr),
    homeRtxTex(nullptr),
    NewGameButton(nullptr),
    NewGameHi(nullptr),
    QuitButton(nullptr),
    QuitHi(nullptr)
{

    homeLayout = new QGridLayout(this); // setup the main layout
    /*  By adding (this), QT link the objet to it's parenting system
     *  This makes the deletion of all dynamic pointer automatic.
     *  Meaning you do not have to make a destructor, the compiler does it for you.
     *
     *  You can watch your memory usage go up and down in task magager.
     *  It works. And the quantity (in MB) are the same
     *  whether you use (this) or a ~destructor().
     */

    homeBackgroundTex = new QLabel(this);
    homeBackgroundTex->setPixmap(QPixmap("../textures/acceuil_bg.png"));
    homeBackgroundTex->setAlignment(Qt::AlignCenter);
    homeBackgroundTex->setScaledContents(true); // stretch the background to the window size
    homeBackgroundTex->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored); // make the window ignore the minimum size of this picture

    homeLogoTex = new QLabel(this);
    homeLogoTex->setPixmap(QPixmap("../textures/acceuil_logo.png"));
    homeLogoTex->setAlignment(Qt::AlignCenter);

    homeCpuTex = new QLabel(this);
    homeCpuTex->setPixmap(QPixmap("../textures/acceuil_cpu.png")); // small cpu graphic logo in the bottom right
    homeCpuTex->setAlignment(Qt::AlignRight);

    homeRtxTex = new QLabel(this);
    homeRtxTex->setPixmap(QPixmap("../textures/acceuil_rtx.png")); // small rtx off logo in the bottom left
    homeRtxTex->setAlignment(Qt::AlignLeft);

    //-------------------------------------- Boutton Nouvelle Partie ---------------------------------------
    // --- highlight
    NewGameHi = new QLabel(this);
    NewGameHi->setPixmap(QPixmap("../textures/acceuil_button_hi.png"));
    NewGameHi->hide();
    NewGameHi->setAlignment(Qt::AlignCenter);
    // --- button
    NewGameButton = new LabelButton(QPixmap("../textures/acceuil_start.png"));
    QObject::connect(NewGameButton, SIGNAL(clicked()), SIGNAL(OpenGameSignal())); // recieve clicked signal and emit OpenGame to the main window
    QObject::connect(NewGameButton, SIGNAL(isHovered()), NewGameHi, SLOT(show())); // connect the button to it's highlight
    QObject::connect(NewGameButton, SIGNAL(notHovered()), NewGameHi, SLOT(hide())); // connect the button to it's highlight
    //-------------------------------------- Boutton Quitter -----------------------------------------------
    // --- highlight
    QuitHi = new QLabel(this);
    QuitHi->setPixmap(QPixmap("../textures/acceuil_button_hi.png"));
    QuitHi->hide();
    QuitHi->setAlignment(Qt::AlignCenter);
    // --- button
    QuitButton = new LabelButton(QPixmap("../textures/acceuil_quit.png"));
    QObject::connect(QuitButton, SIGNAL(clicked()), qApp, SLOT(quit())); // receive clicked signal and quit app
    QObject::connect(QuitButton, SIGNAL(isHovered()), QuitHi, SLOT(show())); // connect the button to it's highlight
    QObject::connect(QuitButton, SIGNAL(notHovered()), QuitHi, SLOT(hide())); // connect the button to it's highlight
    //------------------------------------------------------------------------------------------------------

    homeLayout->addWidget(homeBackgroundTex, 0, 0, 5, 3); // 5 rows make the stretch prettier
    homeLayout->addWidget(homeLogoTex, 0, 0, 1, 3);
    homeLayout->addWidget(homeCpuTex, 4, 2, 1, 1);
    homeLayout->addWidget(homeRtxTex, 4, 0, 1, 1);
    homeLayout->addWidget(NewGameHi, 1, 1, 1, 1);
    homeLayout->addWidget(NewGameButton, 1, 1, 1, 1);
    homeLayout->addWidget(QuitHi, 2, 1, 1, 1);
    homeLayout->addWidget(QuitButton, 2, 1, 1, 1);

    setLayout(homeLayout);
    setWindowTitle("Acceuil Connect 4");
}

fenetreAcceuil::~fenetreAcceuil(){
    delete NewGameButton;
    delete QuitButton;

}

