#include "CustomLabel.h"
#include <QtDebug>

//---------------------------------------------------------------------------------- LabelButton
LabelButton::LabelButton(QWidget* parent, Qt::WindowFlags f) : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
}

LabelButton::LabelButton(QPixmap texture, QWidget* parent, Qt::WindowFlags f) : QLabel(parent)
{
    setPixmap(texture);
    setAlignment(Qt::AlignCenter);
}

LabelButton::~LabelButton(){}


void LabelButton::mousePressEvent(QMouseEvent* event) {
    emit clicked();
}
void LabelButton::enterEvent(QEvent* event){
    emit isHovered();
}
void LabelButton::leaveEvent(QEvent* event){
    emit notHovered();
}

