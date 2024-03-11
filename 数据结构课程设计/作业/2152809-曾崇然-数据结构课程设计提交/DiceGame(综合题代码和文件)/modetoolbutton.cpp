#include "modetoolbutton.h"
#include <QFont>

ModeToolButton::ModeToolButton(QString fileName1, QString fileName2, QString btnName)
{
    //设置字体
    QFont font;
    font.setFamily("宋体");
    font.setBold(true);

    //初始化两张图片
    QPixmap pix;
    pix.load(fileName1);
    this->pix1 = pix.scaled(40, 40);
    pix.load(fileName2);
    this->pix2 = pix.scaled(40, 40);

    //初始化计时器
    this->shakeTimer = new QTimer(this);

    //设置标签和文字
    this->setIcon(QIcon(pix1));
    this->setIconSize(QSize(40, 40));
    this->setText(btnName);
    this->setFont(font);
    this->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    this->setFixedSize(150, 40);

    //关联时钟实现抖动
    connect(this->shakeTimer, &QTimer::timeout, [=](){
        if (this->whichPix) {//是图片1，则改为图片2
            this->setIcon(this->pix2);
            this->whichPix = false;
        }
        else {//是图片2，则改为图片1
            this->setIcon(this->pix1);
            this->whichPix = true;
        }
    });
}

void ModeToolButton::shake() {
    this->shakeTimer->start(300);
}

void ModeToolButton::stopShake() {
    this->shakeTimer->stop();
    this->setIcon(this->pix1);
}

