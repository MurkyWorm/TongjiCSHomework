#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include "punishcontent.h"

namespace Ui {
class PlayScene;
}

class PlayScene : public QMainWindow
{
    Q_OBJECT

public:
    //explicit PlayScene(QWidget *parent = nullptr);

    //重写构造函数
    PlayScene(int mapChoice, int modeChoice, QStringList charas, QWidget *parent = nullptr);

    //重写绘图函数
    void paintEvent(QPaintEvent *pev);

    ~PlayScene();

    //当前骰子的点数
    int diceNumder = 0;

    //当前角色数的点数
    int countNumber = 1;

    //火焰的动画计数
    int fireCount = 1;

    //当前该操作的角色号
    int charaOperateNo = 1;

    //绕圈时钟
    QTimer *circleTimer;

    //惩罚条
    QLabel *punishs;

    //惩罚条的最后一条
    int finalPunish;

    //生成惩罚条
    void generatePunishs(int initPunish);

    //惩罚信息
    PunishContent *punishContent;

    //游戏模式
    int modeChoice;

    //结果
    QStringList result;

    //结果窗口
    QWidget *resultWidget;

signals:
    void returnStart();

private:
    Ui::PlayScene *ui;
};

#endif // PLAYSCENE_H
