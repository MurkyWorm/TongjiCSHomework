#include "charalabel.h"
#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QFont>
#include "mypushbutton.h"

CharaLabel::CharaLabel(int charaIndex, QString charaName)
{
    //设置控件大小
    this->setFixedSize(50, 150);
    //设置控件边框
    this->setStyleSheet("border:1px solid black");

    //动画时钟
    this->animationTimer = new QTimer;

    //图像标签
    QLabel *img = new QLabel;
    img->setParent(this);
    img->setFixedSize(48, 48);

    //文字标签
    QLabel *text = new QLabel;
    text->setParent(this);
    text->setFixedSize(48, 64);
    text->move(0, 47);
    text->setAlignment(Qt::AlignTop | Qt::AlignHCenter);//设置文字对齐方式
    text->setWordWrap(true);
    QFont font;
    font.setBold(true);
    font.setPointSize(8);
    text->setFont(font);
    QString str = charaName;
    text->setText(str.split("", QString::SkipEmptyParts).join('\n'));

    //设置删除按钮
    MyPushButton *btn = new MyPushButton(":/create/create/charaDelete1.png", ":/create/create/charaDelete2.png");
    btn->setFixedSize(48, 30);
    btn->setParent(this);
    btn->setStyleSheet("border:1px solid black");
    btn->move(0, 110);

    //设置初始图像
    QPixmap initPix;
    QString initStr = QString(":/chara/chara/chara%1-1-1.png").arg(charaIndex);
    initPix.load(initStr);
    initPix = initPix.scaled(48, 48);
    img->setPixmap(initPix);

    //让图像动起来
    animationTimer->start(300);
    connect(animationTimer, &QTimer::timeout, [=](){
        QString str = QString(":/chara/chara/chara%1-1-%2.png").arg(charaIndex).arg(this->imgCount++);
        QPixmap pix;
        pix.load(str);
        pix = pix.scaled(48, 48);
        img->setPixmap(pix);
        //循环
        if (this->imgCount > 4) {
            this->imgCount = 1;
        }
    });

    //激发删除信号
    connect(btn, &MyPushButton::clicked, [=](){
        emit this->deleteLabel();
    });
}
