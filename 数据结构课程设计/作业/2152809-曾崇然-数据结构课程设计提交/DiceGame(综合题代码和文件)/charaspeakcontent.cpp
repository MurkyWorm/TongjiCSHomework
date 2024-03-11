#include "charaspeakcontent.h"
#include <QPolygon>
#include <QRect>
#include <QPainter>

CharaSpeakContent::CharaSpeakContent(bool side)
{
    this->setFixedHeight(35);
    this->side = side;
}

void CharaSpeakContent::paintEvent(QPaintEvent *pev) {
    //创建画家对象
    QPainter painter(this);
    //绘制矩形
    painter.setBrush(QColor(255, 255, 255)); // 设置填充颜色为白色
    QRect rect(0, 0, this->width() - 1, this->height() - 10);
    painter.drawRect(rect);

    if (this->side == true) {
        //绘制三角形
        QPolygon triangle;
        triangle << QPoint(this->width() - 15, this->height()) << QPoint(this->width() - 8, this->height() - 10) << QPoint(this->width() - 22, this->height() - 10);
        painter.drawPolygon(triangle);
        //绘制直线
        painter.setPen(QColor(255, 255, 255));
        painter.drawLine(this->width() - 9, this->height() -10, this->width() - 21, this->height() - 10);
    }
    else {
        //绘制三角形
        QPolygon triangle;
        triangle << QPoint(15, this->height()) << QPoint(8, this->height() - 10) << QPoint(22, this->height() - 10);
        painter.drawPolygon(triangle);
        //绘制直线
        painter.setPen(QColor(255, 255, 255));
        painter.drawLine(9, this->height() -10, 21, this->height() - 10);
    }
}
