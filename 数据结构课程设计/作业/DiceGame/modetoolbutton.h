#ifndef MODETOOLBUTTON_H
#define MODETOOLBUTTON_H

#include <QToolButton>
#include <QPixmap>
#include <QTimer>

class ModeToolButton : public QToolButton
{
    Q_OBJECT
public:
    //explicit ModeToolButton(QWidget *parent = nullptr);

    //重写构造函数
    ModeToolButton(QString fileName1, QString fileName2, QString btnName);

    //两张图标
    QPixmap pix1;
    QPixmap pix2;

    //当前图标
    bool whichPix = true;

    //抖动动画
    void shake();

    //停止抖动
    void stopShake();

    //抖动计时器
    QTimer *shakeTimer;
signals:

};

#endif // MODETOOLBUTTON_H
