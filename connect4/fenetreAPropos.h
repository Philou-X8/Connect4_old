#ifndef FENETREAPROPOS_H
#define FENETREAPROPOS_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class fenetreAPropos : public QWidget // refered to as "info"
{
    Q_OBJECT
public:
    fenetreAPropos();

private:
    QGridLayout *infoLayout;
    QLabel *infoLogoTex;
    QLabel *infoGameVersion;
    QLabel *infoDevCode;
    QLabel *infoDevAsset;
    QLabel *infoLogoCodeTex;
    QLabel *infoLogoAssetTex;
    QPushButton *infoCloseButton;
};

#endif // FENETREAPROPOS_H
