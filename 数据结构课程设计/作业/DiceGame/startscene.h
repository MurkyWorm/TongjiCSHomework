#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include "createscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class StartScene; }
QT_END_NAMESPACE

class StartScene : public QMainWindow
{
    Q_OBJECT

public:
    StartScene(QWidget *parent = nullptr);
    ~StartScene();

    //重写paintEvent事件，画背景图
    void paintEvent(QPaintEvent *pev);

    //创建游戏的场景
    CreateScene * createScene = NULL;

private:
    Ui::StartScene *ui;
};
#endif // STARTSCENE_H
