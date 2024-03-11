#ifndef CREATESCENE_H
#define CREATESCENE_H

#include <QMainWindow>
#include <QTimer>
#include "charalabel.h"
#include "playscene.h"
//#include "startscene.h"

namespace Ui {
class CreateScene;
}

class CreateScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit CreateScene(QWidget *parent = nullptr);

    //重写构造函数
    //CreateScene(StartScene *startScene);

    ~CreateScene();

    //重写paintEvent事件，画背景图
    void paintEvent(QPaintEvent *pev);

    //选择的场景
    int mapChoice = -1;

    //选择的模式
    int modeChoice = -1;

    //选择的角色
    QStringList charas;

    //选择的角色人数
    int charaNum = 0;

    //是否正在添加角色
    bool isAdd = false;

    //当前正在添加的角色编号
    int currentCharaIndex = -1;

    //角色选择页面的动画时钟
    QTimer *charaChooseTimer;

    //角色选择页面的动画进度
    int imgIndex = 2;

    //当前角色名字输入框内容
    QString currentLineText = "";

    //开始场景
    //StartScene *startScene;

    //游玩场景
    PlayScene *playscene;

private:
    Ui::CreateScene *ui;

signals:
    //自定义的返回信号
    void createSceneBack();
};

#endif // CREATESCENE_H
