#ifndef PLAYCHARA_H
#define PLAYCHARA_H

#include <QLabel>
#include "charaspeakcontent.h"

class PlayChara : public QLabel
{
    Q_OBJECT
public:
    //explicit PlayChara(QWidget *parent = nullptr);
    PlayChara(int charaNo, int direction);

    //角色编号
    int charaNo;

    //角色名字
    QString name;

    //角色方向
    int direction;

    //向后退
    void backStep();

    //跳跃
    void jump1();
    void jump2();

    //说话
    void speak(QString content, int charaX, int charaY, bool side);

    //消失
    void disappear();

    //脚步计数
    int stepCount = 4;

    //对话框
    CharaSpeakContent *charaSpeakContent;

    //是否败北
    bool isFailed = false;

signals:

};

#endif // PLAYCHARA_H
