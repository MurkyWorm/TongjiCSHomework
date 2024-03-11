#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QSound>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡场景
    this->setFixedSize(480, 882);

    //设置图标
    this->setWindowIcon(QPixmap(":/image/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出，实现退出游戏
    connect(quitAction, &QAction::triggered, [=](){
        this->close();
    });

    //选择关卡音效
    QSound *chooseSound = new QSound(":/sound/res/TapButtonSound.wav");

    //返回按钮音效
    QSound *backSound = new QSound(":/sound/res/BackButtonSound.wav");

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/image/res/BackButton.png", ":/image/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //点击返回
    connect(backBtn, &MyPushButton::clicked, [=](){
        //告诉主场景点击了返回，主场景监听了ChooseLevelScene的返回按钮

        //播放延时返回音效
        backSound->play();

        //延时返回
        QTimer::singleShot(200, this, [=](){
            emit this->chooseSceneBack();
        });
    });

    //创建选择关卡的按钮
    for (int i = 0; i < 20; i++) {
        MyPushButton * menuBtn = new MyPushButton(":/image/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(36 + i % 4 * 105, 205 + i / 4 * 120);

        //监听每个按钮的点击事件
        connect(menuBtn, &MyPushButton::clicked, [=](){
            //播放选择关卡音效
            chooseSound->play();

            QString str = QString("您选择的是第 %1 关").arg(i + 1);
            qDebug() << str;

            //进入到游戏场景
            this->hide();//将选关场景隐藏掉
            play = new PlayScene(i + 1);//创建游戏场景
            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());
            play->show();//显示游戏场景

            connect(play, &PlayScene::chooseSceneBack, [=](){
                //设置选择场景的位置
                this->setGeometry(play->geometry());

                delete play;
                play = NULL;
                this->show();
            });
        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(), menuBtn->height());
        label->setText(QString::number(i + 1));
        label->move(36 + i % 4 * 105, 205 + i / 4 * 120);

        //设置label上的文字对齐方式
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void ChooseLevelScene::paintEvent(QPaintEvent *pev) {
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/res/OtherSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //加载标题
    pix.load(":/image/res/Title.png");
    pix = pix.scaled(pix.width() * 1.1, pix.height() * 1.1);
    painter.drawPixmap((this->width() - pix.width() * 1.4) * 0.5, 40, pix.width() * 1.4, pix.height() * 1.4, pix);
}
