#include "mycoin.h"
#include <QDebug>

//MyCoin::MyCoin(QWidget *parent) : QWidget(parent)
//{

//}

MyCoin::MyCoin(QString btnImg) {
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if (!ret) {
        qDebug() << "图片加载失败";
        return;
    }
    pix = pix.scaled(75, 75);
    this->setFixedSize(pix.width(), pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(), pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号，并且反转金币
    connect(timer1, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/image/res/Coin000%1").arg(this->min++);
        bool ret = pix.load(str);
        if (!ret) {
            qDebug() << "图片加载失败";
            return;
        }
        pix = pix.scaled(75, 75);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断，如果翻完了，将min重置为1
        if (this->min > this->max) {
            this->min = 1;
            this->isAnimation = false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号，并且反转银币
    connect(timer2, &QTimer::timeout, [=](){
        QPixmap pix;
        QString str = QString(":/image/res/Coin000%1").arg(this->max--);
        bool ret = pix.load(str);
        if (!ret) {
            qDebug() << "图片加载失败";
            return;
        }
        pix = pix.scaled(75, 75);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        //判断，如果翻完了，将min重置为1
        if (this->min > this->max) {
            this->max = 8;
            this->isAnimation = false;
            timer2->stop();
        }
    });
}

//改变正反面标志的方法
void MyCoin::changeFlag() {
    //如果是正面，翻成反面
    if (this->flag) {
        //开始正面翻反面的计时器
        timer1->start(30);
        this->isAnimation = true;
        this->flag = false;
    }
    //如果是反面，翻成正面
    else {
        //开始反面翻正面的计时器
        timer2->start(30);
        this->isAnimation = true;
        this->flag = true;
    }
}
