#ifndef IMAGEBUTTON_H
#define IMAGEBUTTON_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ImageButton: public QLabel {
    Q_OBJECT

public:
    explicit ImageButton(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ImageButton();

signals:
    void clicked();
    void hovered();
    void nothovered();

protected:
    void mousePressEvent(QMouseEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

};
#endif // IMAGEBUTTON_H
