#include "playchara.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include <QImage>

//PlayChara::PlayChara(QWidget *parent) : QWidget(parent)
//{

//}

PlayChara::PlayChara(int charaNo, int direction) {
    //设置标签大小
    this->setFixedSize(48, 48);
    //设置标签属性
    this->charaNo = charaNo;
    this->direction = direction;
    //加载标签图片
    QString str = QString(":/chara/chara/chara%1-%2-1.png").arg(charaNo).arg(direction);
    this->setPixmap(QPixmap(str));
}

void PlayChara::backStep() {
    QPropertyAnimation *backAnimation = new QPropertyAnimation(this, "geometry", this);//创建动画对象
    backAnimation->setDuration(1200);//设置动画间隔
    backAnimation->setEasingCurve(QEasingCurve::Linear);//设置缓和曲线
    //设置后退方向
    int dirX;
    int dirY;

    qDebug() << "当前方向为" << this->direction;

    if (this->direction == 1) {
        dirX = 0;
        dirY = -50;
    }
    else if (this->direction == 2) {
        dirX = 50;
        dirY = 0;
    }
    else if (this->direction == 3) {
        dirX = 0;
        dirY = 50;
    }
    else {
        dirX = -50;
        dirY = 0;
    }
    backAnimation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));//设置初始位置
    backAnimation->setEndValue(QRect(this->x() + dirX, this->y() + dirY, this->width(), this->height()));//设置结束位置
    //执行动画
    backAnimation->start();

    //设置脚步动画
    QTimer *stepTimer = new QTimer(this);
    //加载图片
    QPixmap pix;
    QString str = QString(":/chara/chara/chara%1-%2-%3.png").arg(this->charaNo).arg(this->direction).arg(this->stepCount--);
    pix.load(str);
    pix = pix.scaled(48, 48);
    this->setPixmap(pix);
    stepTimer->start(300);
    connect(stepTimer, &QTimer::timeout, [=](){
        //加载图片
        QPixmap pix;
        QString str = QString(":/chara/chara/chara%1-%2-%3.png").arg(this->charaNo).arg(this->direction).arg(this->stepCount--);
        pix.load(str);
        pix = pix.scaled(48, 48);
        this->setPixmap(pix);

        //设置循环
        if (this->stepCount < 1) {
            this->stepCount = 4;
            stepTimer->stop();
        }
    });
}

void PlayChara::jump1() {
    QPropertyAnimation *jumpAnimation = new QPropertyAnimation(this, "geometry", this);//创建动画对象
    jumpAnimation->setDuration(250);//设置动画间隔
    jumpAnimation->setEasingCurve(QEasingCurve::OutBounce);//设置缓和曲线
    jumpAnimation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));//设置初始位置
    jumpAnimation->setEndValue(QRect(this->x(), this->y() - 10, this->width(), this->height()));//设置结束位置
    jumpAnimation->start();//执行动画
}

void PlayChara::jump2() {
    QPropertyAnimation *jumpAnimation = new QPropertyAnimation(this, "geometry", this);//创建动画对象
    jumpAnimation->setDuration(250);//设置动画间隔
    jumpAnimation->setEasingCurve(QEasingCurve::OutBounce);//设置缓和曲线
    jumpAnimation->setStartValue(QRect(this->x(), this->y() - 10, this->width(), this->height()));//设置初始位置
    jumpAnimation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));//设置结束位置
    jumpAnimation->start();//执行动画
}

void PlayChara::speak(QString content, int charaX, int charaY, bool side) {
    //创建测试对话标签
    //画文本框
    this->charaSpeakContent = new CharaSpeakContent(side);
    charaSpeakContent->setParent(this->parentWidget());

    charaSpeakContent->setStyleSheet("background-color: rgba(255, 255, 255, 0);border:0px");
    //绘制文本
    QLabel *textLabel = new QLabel;
    textLabel->setText(content);
    textLabel->setParent(charaSpeakContent);
    QFontMetrics fontMetrics(textLabel->font());
    int textWidth = fontMetrics.width(textLabel->text()) + 10;
    if (textWidth < 40) {
        charaSpeakContent->setFixedWidth(40);
        textLabel->move(15, 4);
    }
    else {
        charaSpeakContent->setFixedWidth(textWidth);
        textLabel->move(5, 4);
    }
    //移动到相应位置
    if (side == true) {
        charaSpeakContent->move(charaX - charaSpeakContent->width() + 40, charaY - 35);
    }
    else {
        charaSpeakContent->move(charaX + 10, charaY - 35);
    }
    //设置为可见
    charaSpeakContent->setVisible(true);
    //1s后关闭
    QTimer::singleShot(1000, this, [=](){
        delete textLabel;
        delete charaSpeakContent;
    });
}

void PlayChara::disappear() {
    //创建消失动画
    QString str = QString(":/chara/chara/chara%1-%2-1.png").arg(this->charaNo).arg(this->direction);
    QImage img;
    img.load(str);

    QTimer::singleShot(200, this, [=](){
        QImage tmpImg(48, 48, QImage::Format_ARGB32);
        for (int i = 0; i < 48; ++i) {
            for (int j = 0; j < 48; ++j) {
                QRgb pixelColor = img.pixel(i, j);
                int r = qRed(pixelColor);
                int g = qGreen(pixelColor);
                int b = qBlue(pixelColor);
                int alpha = qAlpha(pixelColor);
                if (alpha == 0) {
                    tmpImg.setPixel(i, j, qRgba(r, g, b, 0));
                }
                else {
                    tmpImg.setPixel(i, j, qRgba(r, g, b, 204));
                }
            }
        }
        QPixmap pixmap = QPixmap::fromImage(tmpImg);
        this->setPixmap(pixmap);
        QTimer::singleShot(200, this, [=](){
            QImage tmpImg(48, 48, QImage::Format_ARGB32);
            for (int i = 0; i < 48; ++i) {
                for (int j = 0; j < 48; ++j) {
                    QRgb pixelColor = img.pixel(i, j);
                    int r = qRed(pixelColor);
                    int g = qGreen(pixelColor);
                    int b = qBlue(pixelColor);
                    int alpha = qAlpha(pixelColor);
                    if (alpha == 0) {
                        tmpImg.setPixel(i, j, qRgba(r, g, b, 0));
                    }
                    else {
                        tmpImg.setPixel(i, j, qRgba(r, g, b, 153));
                    }
                }
            }
            QPixmap pixmap = QPixmap::fromImage(tmpImg);
            this->setPixmap(pixmap);
            QTimer::singleShot(200, this, [=](){
                QImage tmpImg(48, 48, QImage::Format_ARGB32);
                for (int i = 0; i < 48; ++i) {
                    for (int j = 0; j < 48; ++j) {
                        QRgb pixelColor = img.pixel(i, j);
                        int r = qRed(pixelColor);
                        int g = qGreen(pixelColor);
                        int b = qBlue(pixelColor);
                        int alpha = qAlpha(pixelColor);
                        if (alpha == 0) {
                            tmpImg.setPixel(i, j, qRgba(r, g, b, 0));
                        }
                        else {
                            tmpImg.setPixel(i, j, qRgba(r, g, b, 102));
                        }
                    }
                }
                QPixmap pixmap = QPixmap::fromImage(tmpImg);
                this->setPixmap(pixmap);
                QTimer::singleShot(200, this, [=](){
                    QImage tmpImg(48, 48, QImage::Format_ARGB32);
                    for (int i = 0; i < 48; ++i) {
                        for (int j = 0; j < 48; ++j) {
                            QRgb pixelColor = img.pixel(i, j);
                            int r = qRed(pixelColor);
                            int g = qGreen(pixelColor);
                            int b = qBlue(pixelColor);
                            int alpha = qAlpha(pixelColor);
                            if (alpha == 0) {
                                tmpImg.setPixel(i, j, qRgba(r, g, b, 0));
                            }
                            else {
                                tmpImg.setPixel(i, j, qRgba(r, g, b, 51));
                            }
                        }
                    }
                    QPixmap pixmap = QPixmap::fromImage(tmpImg);
                    this->setPixmap(pixmap);
                    QTimer::singleShot(200, this, [=](){
                        QImage tmpImg(48, 48, QImage::Format_ARGB32);
                        for (int i = 0; i < 48; ++i) {
                            for (int j = 0; j < 48; ++j) {
                                QRgb pixelColor = img.pixel(i, j);
                                int r = qRed(pixelColor);
                                int g = qGreen(pixelColor);
                                int b = qBlue(pixelColor);
                                int alpha = qAlpha(pixelColor);
                                if (alpha == 0) {
                                    tmpImg.setPixel(i, j, qRgba(r, g, b, 0));
                                }
                                else {
                                    tmpImg.setPixel(i, j, qRgba(r, g, b, 0));
                                }
                            }
                        }
                        QPixmap pixmap = QPixmap::fromImage(tmpImg);
                        this->setPixmap(pixmap);
                    });
                });
            });
        });
    });
}
