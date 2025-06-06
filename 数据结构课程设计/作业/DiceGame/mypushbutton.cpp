#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}

MyPushButton::MyPushButton(QString normalImg, QString pressImg, double w, double h) {
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    if (!ret) {
        qDebug() << "图片加载失败";
        return;
    }

    //设置图片固定大小
    this->setFixedSize(pix.width() * w, pix.height() * h);

    //设置不规则图片的样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //重置图标大小
    pix = pix.scaled(pix.width() * w, pix.height() * h);

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
}


void MyPushButton::zoom1() {
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //设置动画的时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(), this->y() + 5, this->width(), this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyPushButton::zoom2() {
    //创建动画对象
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //设置动画的时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(), this->y() + 5, this->width(), this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));

    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //执行动画
    animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *e) {
    if (this->pressImgPath != "") {//传入的按下图片不为空，说明需要有按下状态，切换图片
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if (!ret) {
            qDebug() << "图片加载失败";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());

        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //重置图标大小
        pix = pix.scaled(pix.width(), pix.height());

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    //让父类执行其它内容
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e) {
    if (this->pressImgPath != "") {//传入的按下图片不为空，说明需要有按下状态，切换初始图片
        QPixmap pix;
        bool ret = pix.load(normalImgPath);
        if (!ret) {
            qDebug() << "图片加载失败";
            return;
        }

        //设置图片固定大小
        this->setFixedSize(pix.width(), pix.height());

        //设置不规则图片的样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //重置图标大小
        pix = pix.scaled(pix.width(), pix.height());

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize(pix.width(), pix.height()));
    }

    //让父类执行其它内容
    return QPushButton::mouseReleaseEvent(e);
}
