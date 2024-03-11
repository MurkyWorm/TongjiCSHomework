#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum) {
    QString str = QString("进入了第 %1 关").arg(levelNum);
    qDebug() << str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(480, 882);

    //设置图标
    this->setWindowIcon(QIcon(":/image/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("游戏场景");

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

    //添加音效资源
    //返回音效
    QSound *backSound = new QSound(":/sound/res/BackButtonSound.wav", this);
    //翻金币音效
    QSound *flipSound = new QSound(":/sound/res/ConFlipSound.wav", this);
    //返回音效
    QSound *winSound = new QSound(":/sound/res/LevelWinSound.wav", this);

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/image/res/BackButton.png", ":/image/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());

    //点击返回
    connect(backBtn, &MyPushButton::clicked, [=](){
        //qDebug() << "翻金币场景中，点击了返回按钮";

        //播放返回按钮音效
        backSound->play();

        //告诉主场景点击了返回，主场景监听了ChooseLevelScene的返回按钮
        //延时返回
        QTimer::singleShot(200, this, [=](){
            emit this->chooseSceneBack();
        });
    });

    //显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(21);
    QString levelString = QString("Level: %1").arg(levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(levelString);
    label->setGeometry(45, this->height() - 75, 180, 75);

    //初始化每个关卡的二维数组
    dataConfig config;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel *winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":image/res/LevelCompletedDialogBg.png");
    tmpPix = tmpPix.scaled(tmpPix.width() * 1.5, tmpPix.height() * 1.5);
    winLabel->setGeometry(0, 0, tmpPix.width(), tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5, - tmpPix.height());

    //显示金币的背景图片
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //绘制背景图片
            QLabel * label = new QLabel;
            label->setGeometry(0, 0, 75, 75);
            label->setPixmap(QPixmap(":/image/res/BoardNode(1).png").scaled(label->width(), label->height()));
            label->setParent(this);
            label->move(95 + i * 75, 300 + j * 75);

            //创建钱币
            QString pathString;
            if (this->gameArray[i][j] == 1) {
                //显示金币
                pathString = ":/image/res/Coin0001.png";
            }
            else {
                //显示银币
                pathString = ":/image/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(pathString);
            coin->setParent(this);
            coin->move(95 + i * 75, 300 + j * 75);

            //给钱币的属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];//1正面，0反面

            //将金币放入到金币的二维数组中，以便于后期的维护
            coinBtn[i][j] = coin;

            //点击金币进行反转
            connect(coin, &MyCoin::clicked, [=](){
                //播放翻金币音效
                flipSound->play();

                coin->changeFlag();
                this->gameArray[i][j] = this->gameArray[i][j] == 0 ? 1 : 0;

                //提前进入动画状态，防止点击
                if (coin->posX + 1 < 4) {
                    coinBtn[coin->posX + 1][coin->posY]->isAnimation = true;
                }
                if (coin->posX - 1 >= 0) {
                    coinBtn[coin->posX - 1][coin->posY]->isAnimation = true;
                }
                if (coin->posY - 1 >= 0) {
                    coinBtn[coin->posX][coin->posY - 1]->isAnimation = true;
                }
                if (coin->posY + 1 < 4) {
                    coinBtn[coin->posX][coin->posY + 1]->isAnimation = true;
                }
                //翻转周围钱币，延时翻转
                QTimer::singleShot(300, this, [=](){
                    if (coin->posX + 1 < 4) {//右侧钱币翻转条件
                        coinBtn[coin->posX + 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX + 1][coin->posY] = this->gameArray[coin->posX + 1][coin->posY] == 0 ? 1 : 0;
                    }
                    if (coin->posX - 1 >= 0) {//左侧钱币翻转条件
                        coinBtn[coin->posX - 1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX - 1][coin->posY] = this->gameArray[coin->posX - 1][coin->posY] == 0 ? 1 : 0;
                    }
                    if (coin->posY - 1 >= 0) {//上侧钱币翻转条件
                        coinBtn[coin->posX][coin->posY - 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY - 1] = this->gameArray[coin->posX][coin->posY - 1] == 0 ? 1 : 0;
                    }
                    if (coin->posY + 1 < 4) {//下侧钱币翻转条件
                        coinBtn[coin->posX][coin->posY + 1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY + 1] = this->gameArray[coin->posX][coin->posY + 1] == 0 ? 1 : 0;
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (coinBtn[i][j]->flag == false) {//只要有一个反面就算失败
                                this->isWin = false;
                                break;
                            }
                        }
                        if (this->isWin == false) {
                            break;
                        }
                    }
                    if (this->isWin == true) {
                        //播放胜利音效
                        winSound->play();

                        //胜利了
                        qDebug() << "游戏胜利！";
                        //将所有按钮的胜利标志改为true,如果再次点击按钮，不做响应
                        for (int i = 0; i < 4; i++) {
                            for (int j = 0; j < 4; j++) {
                                this->coinBtn[i][j]->isWin = true;
                            }
                        }

                        //将胜利的图片移动下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel, "geometry");
                        //设置事件间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(), winLabel->y(), winLabel->width(), winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(), winLabel->y() + 280, winLabel->width(), winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }
                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *pev) {
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);

    //画背景上的图标
    pix.load(":/image/res/Title.png");
    pix = pix.scaled(pix.width() * 1.1, pix.height() * 1.1);
    painter.drawPixmap(15, 40, pix);
}
