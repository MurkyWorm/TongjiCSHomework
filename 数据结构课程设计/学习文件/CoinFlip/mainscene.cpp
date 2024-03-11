#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QSound>//多媒体模块下的音效

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(480, 882);

    //设置图标
    setWindowIcon(QIcon(":/image/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币主场景");

    //退出按钮实现
    connect(ui->actionquit, &QAction::triggered, [=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound * startSound = new QSound(":/sound/res/TapButtonSound.wav");

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/image/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width() * 0.5 - startBtn->width() * 0.5, this->height() * 0.7);

    //实例化选择关卡场景
    chooseScene = new ChooseLevelScene;

    //监听选择关卡的返回按钮的信号
    connect(chooseScene, &ChooseLevelScene::chooseSceneBack, [=](){
        this->setGeometry(chooseScene->geometry());

        chooseScene->hide();//将选择关卡隐藏掉
        this->show();//重新显示主场景
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
        //播放开始音效资源
        startSound->play();

        //做弹起特效
        startBtn->zoom1();
        startBtn->zoom2();

        //延时进入到选择关卡场景中
        QTimer::singleShot(400, this, [=](){
            //设置chooseScene场景的位置
            chooseScene->setGeometry(this->geometry());

            //自身隐藏
            this->hide();
            //显示选择关卡场景
            chooseScene->show();
        });
    });
}

void MainScene::paintEvent(QPaintEvent *pev) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上的图标
    pix.load(":/image/res/Title.png");
    pix = pix.scaled(pix.width() * 1.1, pix.height() * 1.1);
    painter.drawPixmap(15, 40, pix);
}

MainScene::~MainScene()
{
    delete ui;
}

