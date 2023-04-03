#ifndef NAMEWIDGET_H
#define NAMEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>

class NameWidget : public QWidget
{
    Q_OBJECT
public:
    NameWidget(QString *name1, QString *name2);

	QPushButton *nameEnterButton;
    QPushButton *nameCancelButton;
	// public so that it can be connected in the parent widget
	// without having to make a relay signal

private slots:
    void confimName();

private:
	QGridLayout *nameLayout; // main layout

	QLabel *nameTitleText; // just some visual stuff
	QLabel *namePromp1; // just some visual stuff
	QLabel *namePromp2; // just some visual stuff

	// name of the players
	QString *namePlayer1;
	QString *namePlayer2;

	// boxes where the names are entered
	QLineEdit *nameBox1;
    QLineEdit *nameBox2;


};

#endif // NAMEWIDGET_H
