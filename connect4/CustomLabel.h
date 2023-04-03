#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H


#include <QLabel>
#include <QWidget>
#include <QPixmap>
#include <Qt>

//---------------------------------------------------------------------------------- LabelButton
class LabelButton: public QLabel {
    Q_OBJECT

public:
    explicit LabelButton(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    explicit LabelButton(
            QPixmap texture,
            QWidget* parent = Q_NULLPTR,
            Qt::WindowFlags f = Qt::WindowFlags());

    ~LabelButton();

signals:
    void clicked();
    void isHovered();
    void notHovered();

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);


};

#endif // CUSTOMLABEL_H
