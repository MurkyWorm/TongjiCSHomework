#include "startscene.h"
#include "ui_startscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QLabel>
#include <QTimer>
#include <QFont>
#include <QDebug>

StartScene::StartScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartScene)
{
    ui->setupUi(this);

    //设置固定大小
    this->setFixedSize(720, 1140);

    //设置图标
    this->setWindowIcon(QIcon(":/cover/cover/Pikachu.png"));

    //设置标题
    this->setWindowTitle("开始场景");

    //设置标题标签
    QLabel * titleLabel = new QLabel;
    titleLabel->setText("DiceGame");
    titleLabel->setParent(this);
    QFont titleFont;
    titleFont.setFamily("华文新魏");
    titleFont.setPointSize(21);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->move(70, -60);

    //新游戏按钮
    MyPushButton * newBtn = new MyPushButton(":/cover/cover/CoverButton.png", "", 2, 1.5);
    newBtn->setParent(this);
    newBtn->move(this->width() * 0.5 - newBtn->width() * 0.5, this->height() * 0.3);

    //新游戏标签
    QLabel * newLabel = new QLabel;
    newLabel->setParent(this);
    QFont font;
    font.setFamily("宋体");
    font.setPointSize(15);
    font.setBold(true);
    newLabel->setFixedSize(newBtn->width(), newBtn->height());
    newLabel->setFont(font);
    newLabel->setText("开始游戏");
    newLabel->setStyleSheet("color:white");
    newLabel->move(this->width() * 0.5 - newBtn->width() * 0.5, this->height() * 0.3);
    //设置label上的文字对齐方式
    newLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //设置让鼠标进行穿透
    newLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    //退出游戏按钮
    MyPushButton * exitBtn = new MyPushButton(":/cover/cover/CoverButton.png", "", 2, 1.5);
    exitBtn->setParent(this);
    exitBtn->move(this->width() * 0.5 - newBtn->width() * 0.5, this->height() * 0.45);

    //退出游戏标签
    QLabel * exitLabel = new QLabel;
    exitLabel->setParent(this);
    exitLabel->setFixedSize(newBtn->width(), newBtn->height());
    exitLabel->setFont(font);
    exitLabel->setText("退出游戏");
    exitLabel->setStyleSheet("color:white");
    exitLabel->move(this->width() * 0.5 - newBtn->width() * 0.5, this->height() * 0.45);
    //设置label上的文字对齐方式
    exitLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //设置让鼠标进行穿透
    exitLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

    //设置菜单退出功能
    connect(ui->actionExit, &QAction::triggered, this, [=](){
        this->close();
    });

    connect(newBtn, &MyPushButton::clicked, this, [=](){
        //设置按钮弹跳效果
        newBtn->zoom1();
        newBtn->zoom2();

        //延时打开创建游戏场景
        QTimer::singleShot(400, this, [=](){
            //实例化创建游戏的场景
            createScene = new CreateScene();

            //隐藏自身
            this->hide();

            //设置游戏创建场景的位置
            createScene->setGeometry(this->geometry());

            //显示创建游戏的场景
            createScene->show();

            //处理回退信号
            connect(createScene, &CreateScene::createSceneBack, [=](){
                //设置开始场景的位置
                this->setGeometry(createScene->geometry());

                qDebug() << "设置位置成功啦";

                createScene->close();
                QTimer::singleShot(200, this, [=](){
                    delete createScene;
                });
                this->show();
            });
        });
    });

    connect(exitBtn, &MyPushButton::clicked, this, [=](){
        //设置按钮弹跳效果
        exitBtn->zoom1();
        exitBtn->zoom2();

        //延时退出
        QTimer::singleShot(400, this, [=](){
            this->close();
        });
    });

}

void StartScene::paintEvent(QPaintEvent *pev) {
    //声明画家
    QPainter coverPainter(this);

    //画背景图片
    QPixmap coverPix;
    coverPix.load(":/cover/cover/CoverBg.png");
    coverPainter.drawPixmap(0, 0, this->width(), this->height(), coverPix);

    //画皮卡丘
    coverPix.load(":/cover/cover/Pikachu.png");
    coverPix = coverPix.scaled(coverPix.width() * 3, coverPix.height() * 3);
    coverPainter.drawPixmap(this->width() - coverPix.width(), this->height() - coverPix.height() - 72, coverPix);


}

StartScene::~StartScene()
{
    delete ui;
}

