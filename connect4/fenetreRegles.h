#ifndef FENETREREGLES_H
#define FENETREREGLES_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class fenetreRegles : public QWidget // refered to as "rule"
{
    Q_OBJECT
public:
    fenetreRegles();

private:
    QGridLayout *ruleLayout;
    QLabel *ruleBackgroundTex;
    QLabel *ruleGoalTitle;
    QLabel *ruleGoal;
    QLabel *ruleTurnsTitle;
    QLabel *ruleTurns;
    QLabel *ruleWinTitle;
    QLabel *ruleWin;
    QPushButton *ruleCloseButton;

    void setTitleFont(QLabel *text);
    void setTextFont(QLabel *text);


};

#endif // FENETREREGLES_H
