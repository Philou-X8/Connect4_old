#ifndef FENETREACCEUIL_H
#define FENETREACCEUIL_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "CustomLabel.h" // clickable label


class fenetreAcceuil : public QWidget // refered to as "home"
{
    Q_OBJECT
public:
    fenetreAcceuil();
    ~fenetreAcceuil();

signals:
    void OpenGameSignal(); //signal sent to fenetrePricipale


private:
    QGridLayout *homeLayout; //main layout
    QLabel *homeBackgroundTex; // background texture (Tex)
    QLabel *homeLogoTex; // required logo, the game logo
    QLabel *homeCpuTex;
    QLabel *homeRtxTex;
    LabelButton *NewGameButton; // [Nouvelle Partie]
    QLabel *NewGameHi; // New Game Button's Highlight (Hi)
    LabelButton *QuitButton; // [Quitter]
    QLabel *QuitHi; // Quit Button's Highlight

};

#endif // FENETREACCEUIL_H
