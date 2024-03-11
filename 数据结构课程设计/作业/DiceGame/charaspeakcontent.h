#ifndef CHARASPEAKCONTENT_H
#define CHARASPEAKCONTENT_H

#include <QLabel>

class CharaSpeakContent : public QLabel
{
    Q_OBJECT
public:
    //explicit CharaSpeakContent(QWidget *parent = nullptr);

    //重写构造函数
    CharaSpeakContent(bool side);

    //重写绘图函数
    void paintEvent(QPaintEvent *pev);

    //左还是右
    bool side = true;

signals:

};

#endif // CHARASPEAKCONTENT_H
