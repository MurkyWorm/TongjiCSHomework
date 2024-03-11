#include "mylabel.h"
#include <QDebug>

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{

}

void myLabel::enterEvent(QEvent *event) {
    qDebug() << "鼠标进入了";
}

void myLabel::leaveEvent(QEvent *event) {
    qDebug() << "鼠标离开了";
}
