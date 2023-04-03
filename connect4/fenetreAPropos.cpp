#include "fenetreAPropos.h"
#include <QApplication>


fenetreAPropos::fenetreAPropos() : QWidget(),
    infoLayout(nullptr),
    infoLogoTex(nullptr),
    infoGameVersion(nullptr),
    infoDevCode(nullptr),
    infoDevAsset(nullptr),
    infoLogoCodeTex(nullptr),
    infoLogoAssetTex(nullptr),
    infoCloseButton(nullptr)
{

    infoLayout = new QGridLayout(this); // setup the main layout

    // ------------------------------------------------------------ game logo // required
    infoLogoTex = new QLabel(this);
    infoLogoTex->setPixmap(QPixmap("../textures/info_game_logo.png"));
    infoLogoTex->setAlignment(Qt::AlignCenter);
    // ------------------------------------------------------------ game version
    infoGameVersion = new QLabel("connect4.exe | Version 1.0-A | Complete code version", this);
    infoGameVersion->setFont(QFont("Comic Sans MS", 20));
    infoGameVersion->setAlignment(Qt::AlignCenter);
    // ------------------------------------------------------------ info about the code
    infoDevCode = new QLabel
    (
        "\nCode source fait par:\n"
        "Philippe Durette\n\n"
        "Avec l'utilisation de\n"
        "Qt Creator 4.13.1"
    , this);
    infoDevCode->setAlignment(Qt::AlignCenter);
    // ------------------------------------------------------------ info about the assets
    infoDevAsset = new QLabel
    (
        "\nContenu visuel fait par:\n"
        "Philippe Durette\n\n"
        "Avec l'utilisation de\n"
        "Krita 4.1.5"
    , this);
    infoDevAsset->setAlignment(Qt::AlignCenter);
    // ------------------------------------------------------------ code logo
    infoLogoCodeTex = new QLabel(this);
    infoLogoCodeTex->setPixmap(QPixmap("../textures/info_qt.png"));
    infoLogoCodeTex->setAlignment(Qt::AlignCenter);
    // ------------------------------------------------------------ asset logo
    infoLogoAssetTex = new QLabel(this);
    infoLogoAssetTex->setPixmap(QPixmap("../textures/info_krita.png"));
    infoLogoAssetTex->setAlignment(Qt::AlignCenter);
    // ------------------------------------------------------------ close button
    infoCloseButton = new QPushButton("Fermer", this);
    QObject::connect(infoCloseButton, SIGNAL(clicked(bool)), this, SLOT(close())); // make the close button... close
    // ------------------------------------------------------------

    //place the widgets in the layout
    infoLayout->addWidget(infoLogoTex, 0, 0, 1, 2);
    infoLayout->addWidget(infoGameVersion, 1, 0, 1, 2);
    infoLayout->addWidget(infoDevCode, 2, 0);
    infoLayout->addWidget(infoDevAsset, 2, 1);
    infoLayout->addWidget(infoLogoCodeTex, 3, 0);
    infoLayout->addWidget(infoLogoAssetTex, 3, 1);
    infoLayout->addWidget(infoCloseButton, 4, 0, 1, 2);

    setLayout(infoLayout);
    setWindowTitle("À Propos");
}

