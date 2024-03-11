#ifndef CHARALABEL_H
#define CHARALABEL_H

#include <QWidget>
#include <QTimer>

class CharaLabel : public QWidget
{
    Q_OBJECT
public:
    //explicit CharaLabel(QWidget *parent = nullptr);
    CharaLabel(int charaIndex, QString charaName);

    //动画计数
    int imgCount = 2;

    //动画时钟
    QTimer *animationTimer;

    //标签序号
    int no;

signals:
    void deleteLabel();
};

#endif // CHARALABEL_H
